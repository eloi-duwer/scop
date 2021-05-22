/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:37:24 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:29:06 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GL_INIT_H__
# define __GL_INIT_H__

# define GL_FALSE					0
# define GL_TRUE					1

# define GL_NO_ERROR				0

# define GL_UNSIGNED_BYTE			0x1401
# define GL_UNSIGNED_INT			0x1405
# define GL_FLOAT					0x1406

# define GL_DEPTH_BUFFER_BIT		0x00000100
# define GL_COLOR_BUFFER_BIT		0x00004000

# define GL_TEXTURE_2D				0x0DE1

# define GL_DEPTH_TEST				0x0B71

# define GL_TRIANGLES				0x0004

# define GL_LESS					0x0201

# define GL_LINEAR					0x2601

# define GL_RGB						0x1907
# define GL_BGR						0x80E0

# define GL_TEXTURE_MAG_FILTER		0x2800
# define GL_TEXTURE_MIN_FILTER		0x2801
# define GL_TEXTURE_WRAP_S			0x2802
# define GL_TEXTURE_WRAP_T			0x2803
# define GL_REPEAT					0x2901

# define GL_ARRAY_BUFFER			0x8892
# define GL_ELEMENT_ARRAY_BUFFER	0x8893
# define GL_STATIC_DRAW				0x88E4

# define GL_FRAGMENT_SHADER			0x8B30
# define GL_VERTEX_SHADER			0x8B31
# define GL_COMPILE_STATUS			0x8B81
# define GL_LINK_STATUS				0x8B82
# define GL_INFO_LOG_LENGTH			0x8B84

typedef unsigned char	GLboolean;
typedef char			GLchar;
typedef unsigned int	GLenum;
typedef unsigned int	GLuint;
typedef int				GLint;
typedef int				GLsizei;
typedef float			GLfloat;
typedef float			GLclampf;
typedef unsigned int	GLbitfield;
typedef void			GLvoid;
typedef signed long int	GLsizeiptr;


/*
** This is an X macro: https://en.wikipedia.org/wiki/X_Macro
** (Inspired from https://apoorvaj.io/loading-opengl-without-glew/)
** Used to declare all the openGL functions used
** And load them in the file gl_init.c
** Used to avoid to repeat all the declarations
*/

# define OPENGL_FUNCS \
GLFUNC(void, EnableVertexAttribArray, GLuint index) \
GLFUNC(void, BindBuffer, GLenum targer, GLuint buffer) \
GLFUNC(void, VertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) \
GLFUNC(void, ClearColor, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) \
GLFUNC(void, Clear, GLbitfield mask) \
GLFUNC(GLint, GetUniformLocation, GLuint program, const GLchar *name) \
GLFUNC(void, Uniform1f, GLint location, GLfloat v0) \
GLFUNC(void, Uniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) \
GLFUNC(void, UniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) \
GLFUNC(void, Uniform1ui, GLint location, GLuint v0) \
GLFUNC(void, Uniform1i, GLint location, GLint v0) \
GLFUNC(void, DrawElements, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) \
GLFUNC(void, DisableVertexAttribArray, GLuint index) \
GLFUNC(void, Enable, GLenum cap) \
GLFUNC(void, DepthFunc, GLenum mask) \
GLFUNC(GLenum, GetError, void) \
GLFUNC(void, GetShaderiv, GLuint shader, GLenum pname, GLint *params) \
GLFUNC(void, GetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) \
GLFUNC(void, GetProgramiv, GLuint program, GLenum pname, GLint *params) \
GLFUNC(void, GetProgramInfoLog, GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) \
GLFUNC(GLuint, CreateShader, GLenum type) \
GLFUNC(void, ShaderSource, GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) \
GLFUNC(void, CompileShader, GLuint shader) \
GLFUNC(void, AttachShader, GLuint program, GLuint shader) \
GLFUNC(GLuint, CreateProgram, void) \
GLFUNC(void, LinkProgram, GLuint program) \
GLFUNC(void, UseProgram, GLuint program) \
GLFUNC(void, GenVertexArrays, GLsizei n, GLuint *arrays) \
GLFUNC(void, BindVertexArray, GLuint array) \
GLFUNC(void, DeleteVertexArrays, GLsizei n, const GLuint *arrays) \
GLFUNC(void, GenBuffers, GLsizei n, GLuint *buffers) \
GLFUNC(void, BufferData, GLenum target, GLsizeiptr size, const void *data, GLenum usage) \
GLFUNC(void, DeleteBuffers, GLsizei n, const GLuint *buffers) \
GLFUNC(void, GenTextures, GLsizei n, GLuint *textures) \
GLFUNC(void, BindTexture, GLenum target, GLuint texture) \
GLFUNC(void, TexImage2D, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) \
GLFUNC(void, TexParameteri, GLenum target, GLenum pname, GLint param) \
GLFUNC(void, GenerateMipmap, GLenum target) \

/*
** Declare the functions as extern
** So that we have only one definition of them
*/

# define GLFUNC(ret, name, ...) typedef ret name##Proc(__VA_ARGS__); extern name##Proc *gl##name;
OPENGL_FUNCS
# undef GLFUNC

/*
** Declare all the functions,
** The define GLFUNC_IMPL must be present in only one file (in load_opengl_funcs.c)
*/

# ifdef GLFUNC_IMPL
#  define GLFUNC(ret, name, ...) typedef ret name##Proc(__VA_ARGS__); name##Proc *gl##name;
OPENGL_FUNCS
#  undef GLFUNC
# endif

int		load_opengl_funcs(void);

#endif