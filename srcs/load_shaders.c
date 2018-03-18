#include <scop.h>

void	verif_gl_shader_error(t_infos *infos, GLuint shader)
{
	GLint	result;
	char	*str;
	GLint	size;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_TRUE)
		return;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
	if ((str = (char *)malloc(sizeof(char) * size)) != NULL)
	{
		glGetShaderInfoLog(shader, size, &size, str);
		printf("Shader compilation error: %s\n", str);
		free(str);
	}
	else
		printf("Shader compilation error: No error(log length=%d)\n", result);
	quit_prog(infos);
}

void	verif_gl_program_error(t_infos *infos, GLuint program)
{
	GLint	result;
	char	*str;
	GLint	size;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_TRUE)
		return;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
	if ((str = (char *)malloc(sizeof(char) * size)) != NULL)
	{
		glGetProgramInfoLog(program, size, &size, str);
		printf("Program compilation error: %s\n", str);
		free(str);
	}
	else
		printf("Program compilation error: No error(log length=%d)\n", result);
	quit_prog(infos);
}

char	*read_shader(t_infos *infos, char *file_name)
{
	FILE	*file;
	char	*src;
	long	size;

	if ((file = fopen(file_name, "r")) == NULL)
	{
		printf("shader file %s not found\n", file_name);
		quit_prog(infos);
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	if ((src = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		print_error(infos, "Malloc error");
	src[size] = '\0';
	rewind(file);
	fread(src, sizeof(char), size, file);
	fclose(file);
	return(src);
}

void	create_program(t_infos *infos)
{
	char	*src;

	infos->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	printf("%s\n", (glIsShader(infos->fragment_shader) == GL_TRUE ? "Is a shader" : "Not a shader"));
	src = read_shader(infos, "./shaders/fragment_shader.glsl");
	glShaderSource(infos->fragment_shader, 1, (const GLchar **)&src, NULL);
	free(src);
	glCompileShader(infos->fragment_shader);
	verif_gl_shader_error(infos, infos->fragment_shader);
	infos->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	src = read_shader(infos, "./shaders/vertex_shader.glsl");
	glShaderSource(infos->vertex_shader, 1, (const GLchar **)&src, NULL);
	free(src);
	glCompileShader(infos->vertex_shader);
	verif_gl_shader_error(infos, infos->vertex_shader);
	infos->program = glCreateProgram();
	glAttachShader(infos->program, infos->fragment_shader);
	glAttachShader(infos->program, infos->vertex_shader);
	glLinkProgram(infos->program);
	verif_gl_program_error(infos, infos->program);
	glUseProgram(infos->program);
}
