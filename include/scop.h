#ifndef __SCOP_H__
#define __SCOP_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <glad/glad.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct		s_infos {
	SDL_Window		*window;
	SDL_Event		event;
	SDL_GLContext	glcontext;
	GLuint			vertex_array_id;
	GLuint			vertexbuffers[2];
	GLuint			fragment_shader;
	GLuint			vertex_shader;
	GLuint			program;
}					t_infos;

typedef struct		s_projection {
	float			top;
	float			left;
	float			down;
	float			right;
	float			near_clip;
	float			far_clip;
	float			angle_of_view;
	float			screen_ratio;
	float			projection_matrix[16];
}					t_projection;

void	handlekeyboarddown(t_infos *infos);
void	quit_prog(t_infos *infos);
void	print_error(t_infos *infos, char *str);
void	init_sdl_opengl(t_infos *infos);
void	create_program(t_infos *infos);
void	setup_objects(t_infos *infos);
void	rotation_matrix_X(float *mat, float angle);
void	rotation_matrix_Y(float *mat, float angle);
void	rotation_matrix_Z(float *mat, float angle);
void	init_identity_matrix(float *mat);
void	multMatrix(float *mat1, float *mat2, float *res);
void	setProjectionMatrix(float fov, float near_plan, float far_plan, \
			float *matrix);
void	init_projection_infos(t_infos *infos, t_projection *projection);

#endif
