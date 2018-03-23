/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:49:30 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 16:12:40 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# ifdef WIN32
#  include <glad/glad.h>
#  include <SDL2/SDL.h>
# else
#  include <SDL.h>
#  define GL3_PROTOTYPES 1
#  include <OpenGL/gl3.h>
# endif
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# define BUFFER_SIZE 200

typedef struct		s_f_point {
	float			x;
	float			y;
	float			z;
}					t_f_point;

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
	float			rotation_matrix[16];
}					t_projection;

typedef struct		s_infos {
	SDL_Window		*window;
	SDL_Event		event;
	SDL_GLContext	glcontext;
	GLuint			vertex_array_id;
	GLuint			vertexbuffers[2];
	GLuint			fragment_shader;
	GLuint			vertex_shader;
	GLuint			program;
	GLuint			mat_proj_id;
	GLuint			mat_rot_id;
	GLuint			deplacement_id;
	t_projection	proj;
	t_f_point		*vertices;
	int				vertices_size;
	int				nb_vertices;
	GLuint			*indexes;
	int				indexes_size;
	int				nb_indexes;
}					t_infos;

void				handlekeyboarddown(t_infos *infos);
void				quit_prog(t_infos *infos);
void				print_error(t_infos *infos, char *str);
void				init_sdl_opengl(t_infos *infos);
void				create_program(t_infos *infos);
void				setup_objects(t_infos *infos);
void				rotation_matrix_x(float *mat, float angle);
void				rotation_matrix_y(float *mat, float angle);
void				rotation_matrix_z(float *mat, float angle);
void				init_identity_matrix(float *mat);
void				mult_matrix(float *mat1, float *mat2, float *res);
void				set_projection_matrix(float fov, float near_plan, \
						float far_plan, float *matrix);
void				init_projection_infos(t_infos *infos, \
						t_projection *projection);
void				translation_matrix(float *mat, float x, float y, float z);
void				parse_file(t_infos *infos, int ac, char **arg);
void				free_string_tab(char **str);

#endif
