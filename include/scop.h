/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:49:30 by eduwer            #+#    #+#             */
/*   Updated: 2020/01/31 12:38:41 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# define GL_SILENCE_DEPRECATION
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
# include <math.h>
# define BUFFER_SIZE 500

# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK 0xff000000;
#  define GMASK 0x00ff0000;
#  define BMASK 0x0000ff00;
#  define AMASK 0x000000ff;
# else
#  define RMASK 0x000000ff;
#  define GMASK 0x0000ff00;
#  define BMASK 0x00ff0000;
#  define AMASK 0xff000000;
# endif

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
	SDL_Surface		*texture;
	GLuint			tex_id;
	GLuint			fragment_shader;
	GLuint			vertex_shader;
	GLuint			program;
	GLuint			mat_proj_id;
	GLuint			mat_rot_id;
	GLuint			deplacement_id;
	GLuint			comp_id;
	GLuint			scale_id;
	GLuint			color_id;
	GLuint			text_cord_id;
	t_projection	proj;
	t_f_point		*vertices;
	int				vertices_size;
	int				nb_vertices;
	GLuint			*indexes;
	int				indexes_size;
	int				nb_indexes;
	float			*textures;
	int				textures_size;
	int				nb_textures;
	t_f_point		min_point;
	t_f_point		max_point;
	t_f_point		middle_obj_pos;
	float			scale;
	bool			mouse_control;
	float			obj_distance;
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
void				test_event(t_infos *infos);
void				init_struct(t_infos *infos);

#endif
