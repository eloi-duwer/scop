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
	create_program(infos);

	//TEST DU LOAD DES TEXTURES AVEC SDL
	infos->texture = SDL_LoadBMP("./textures/uvtemplate.bmp");
	glGenTextures(1, &infos->tex_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, infos->tex_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    SDL_PixelFormat format = *(infos->texture->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = RMASK;
    format.Gmask = GMASK;
    format.Bmask = BMASK;
    format.Amask = AMASK;
    SDL_Surface *converted = SDL_ConvertSurface(infos->texture, &format, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, converted->w, converted->h, 0, \
		GL_RGBA, GL_UNSIGNED_BYTE, converted->pixels);
	printf("%d\n", glGetError());
	SDL_FreeSurface(converted);
}

void	setup_objects(t_infos *infos)
{
	GLuint	vertexbuffers[2];
	GLuint	vertex_array;

	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	glGenBuffers(2, vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, infos->nb_vertices * sizeof(t_f_point), infos->vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, infos->nb_indexes * sizeof(GLuint), infos->indexes, GL_STATIC_DRAW);

	//test textures
	glGenBuffers(1, &infos->text_cord_id);
	glBindBuffer(GL_ARRAY_BUFFER, infos->text_cord_id);
	glBufferData(GL_ARRAY_BUFFER, infos->nb_textures * sizeof(*infos->textures) * 2, infos->textures, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void	init_struct(t_infos *infos)
{
	infos->window = NULL;
	infos->vertices = NULL;
	infos->indexes = NULL;
	if (!(infos->vertices = \
		(t_f_point *)malloc(BUFFER_SIZE * sizeof(t_f_point))))
		print_error(infos, "Malloc returned null");
	infos->vertices_size = BUFFER_SIZE;
	infos->nb_vertices = 0;
	if (!(infos->indexes = (GLuint *)malloc(BUFFER_SIZE * sizeof(GLuint))))
		print_error(infos, "Malloc returned null");
	infos->indexes_size = BUFFER_SIZE;
	infos->nb_indexes = 0;
	if (!(infos->textures = (float *)malloc(BUFFER_SIZE * sizeof(float))))
		print_error(infos, "Malloc returned null");
	infos->textures_size = BUFFER_SIZE;
	infos->nb_textures = 0;
	ft_bzero(&infos->middle_obj_pos, sizeof(t_f_point));
	infos->min_point.x = 4242424242.0;
	infos->min_point.y = 4242424242.0;
	infos->min_point.z = 4242424242.0;
	infos->max_point.x = -4242424242.0;
	infos->max_point.y = -4242424242.0;
	infos->max_point.z = -4242424242.0;
	init_identity_matrix(infos->proj.rotation_matrix);
	infos->mouse_control = false;
	infos->obj_distance = -7.0;
}
