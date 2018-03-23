/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl_opengl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:49:51 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 16:35:47 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	init_sdl_opengl(t_infos *infos)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_LoadLibrary(NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, \
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	infos->window = SDL_CreateWindow("Test scope", SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_OPENGL);
	infos->glcontext = SDL_GL_CreateContext(infos->window);
#ifdef WIN32
	gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	SDL_SetRelativeMouseMode(1);
	create_program(infos);
}

void	setup_objects(t_infos *infos)
{
	GLfloat cube_colors[][3] = {
	{1.0, 1.0, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 1.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 0.0}};

	glGenVertexArrays(1, &(infos->vertex_array_id));
	glBindVertexArray(infos->vertex_array_id);
	glGenBuffers(2, infos->vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, infos->nb_vertices * sizeof(t_f_point)/*sizeof(cube)*/, /*cube*/infos->vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	GLuint indexes;
	glGenBuffers(1, &indexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, infos->nb_indexes * sizeof(GLuint)/*sizeof(cube_indices)*/, /*cube_indices*/infos->indexes, GL_STATIC_DRAW);
}
