/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:41 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/26 01:48:03 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void verif_gl_shader_error(t_context *ctx, GLuint id, const char *file)
{
	GLint	res;
	char	*str;
	GLint	size;

	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_TRUE)
		return ;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &size);
	if ((str = (char *)malloc(sizeof(char) * size)) != NULL)
	{
		glGetShaderInfoLog(id, size, &size, str);
		printf("Shader compilation error (file %s):\n%s\n", file, str);
		free(str);
	}
	else
		printf("Shader error: Can't log error (log length=%d\n", size);
	quit_prog(ctx);
}

static void 	verif_gl_program_error(t_context *ctx, GLuint prog)
{
	GLint	res;
	char	*str;
	GLint	size;

	glGetProgramiv(prog, GL_LINK_STATUS, &res);
	if (res == GL_TRUE)
		return ;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &size);
	if ((str = (char *)malloc(sizeof(char) * size)) != NULL)
	{
		glGetProgramInfoLog(prog, size, &size, str);
		printf("Program compilation error: %s\n", str);
		free(str);
	}
	else
		printf("Program error: Can't log error (log length=%d\n", size);
	quit_prog(ctx);
}

static char		*read_shader(t_context *ctx, const char *file_name)
{
	FILE	*file;
	char	*src;
	long	size;

	if ((file = fopen(file_name, "r")) == NULL)
	{
		printf("Shader file %s not found\n", file_name);
		exit(1);
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	if ((src = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
	{
		printf("Error while reading shader (malloc)\n");
		exit(1);
	}
	src[size] = '\0';
	rewind(file);
	fread(src, sizeof(char), size, file);
	fclose(file);
	return (src);
}

static GLuint	make_shader(t_context *ctx, GLuint prog, \
	GLenum shaderType, const char *src_name)
{
	GLuint	id;
	char	*src;

	id = glCreateShader(shaderType);
	src = read_shader(ctx, src_name);
	glShaderSource(id, 1, (const GLchar **)&src, NULL);
	free(src);
	glCompileShader(id);
	verif_gl_shader_error(ctx, id, src_name);
	glAttachShader(prog, id);
	return id;
}

GLuint			create_program(t_context *ctx, \
	const char *fragment_shader, const char *vertex_shader)
{
	GLuint prog;

	prog = glCreateProgram();
	make_shader(ctx, prog, GL_FRAGMENT_SHADER, fragment_shader);
	make_shader(ctx, prog, GL_VERTEX_SHADER, vertex_shader);
	glLinkProgram(prog);
	verif_gl_program_error(ctx, prog);
	return (prog);
}
