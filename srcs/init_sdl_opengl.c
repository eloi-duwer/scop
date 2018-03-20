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
	GLfloat square[][3] = {
	{-1.0, 1.0, -1.0}, /* Back */
	{1.0, 1.0, -1.0},
	{-1.0, -1.0, -1.0},
	{1.0, -1.0, -1.0},
	{-1.0, 1.0, -1.0}, /* Left */
	{-1.0, -1.0, -1.0},
	{-1.0, 1.0, 1.0},
	{-1.0, -1.0, 1.0},
	{1.0, 1.0, 1.0}, /* Top */
	{-1.0, 1.0, 1.0},
	{1.0, 1.0, -1.0},
	{-1.0, 1.0, -1.0},
	{1.0, -1.0, 1.0}, /* Bottom */
	{-1.0, -1.0, 1.0},
	{1.0, -1.0, -1.0},
	{-1.0, -1.0, -1.0},
	{1.0, 1.0, 1.0}, /* Right */
	{1.0, -1.0, 1.0},
	{1.0, 1.0, -1.0},
	{1.0, -1.0, -1.0},
	{1.0, 1.0, 1.0}, /* Front */
	{-1.0, 1.0, 1.0},
	{1.0, -1.0, 1.0},
	{-1.0, -1.0, 1.0}};
	GLfloat colors[][3] = {
	{1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{1.0, 1.0, 0.0},
	{1.0, 1.0, 0.0},
	{1.0, 1.0, 0.0},
	{1.0, 1.0, 0.0},
	{0.0, 1.0, 1.0},
	{0.0, 1.0, 1.0},
	{0.0, 1.0, 1.0},
	{0.0, 1.0, 1.0},
	{1.0, 0.0, 1.0},
	{1.0, 0.0, 1.0},
	{1.0, 0.0, 1.0},
	{1.0, 0.0, 1.0}};

	glGenVertexArrays(1, &(infos->vertex_array_id));
	glBindVertexArray(infos->vertex_array_id);
	glGenBuffers(2, infos->vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), \
		square, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, infos->vertexbuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
