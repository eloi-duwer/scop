#ifndef __SCOP_H__
#define __SCOP_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <glad/glad.h>
#include <stdbool.h>
#include <stdlib.h>

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

void	handlekeyboarddown(t_infos *infos);
void	quit_prog(t_infos *infos);
void	print_error(t_infos *infos, char *str);
void	init_sdl_opengl(t_infos *infos);
void	create_program(t_infos *infos);
void	setup_objects(t_infos *infos);

#endif
