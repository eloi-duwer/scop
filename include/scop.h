#ifndef __SCOP_H__
# define __SCOP_H__
# include <gtk/gtk.h>
# define GL3_PROTOTYPES 1
# include <GL/glew.h>
# include <stdio.h>
#define _USE_MATH_DEFINES
# include <math.h>
# include <libftprintf.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# define BUFF_SIZE 1000
# define DISPLAY_FACES 0
# define DISPLAY_TEXTURES 1

typedef struct	s_mat4x4 {
	float		mat[4][4];
}				t_mat4x4;

typedef struct	s_vec3 {
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_triangle {
	unsigned int	points[3];
}				t_triangle;

typedef struct	s_object {
	int			nb_faces;
	int			size_faces;
	t_triangle	*faces;
	int			nb_vertexes;
	int			size_vertexes;
	t_vec3		*vertexes;
	t_vec3		center;
	t_vec3		world_position;
	t_vec3		dimensions;
	t_vec3		min_coords;
	t_vec3		max_coords;
	t_mat4x4	rotation_matrix;
	t_mat4x4	model_matrix;
	GLuint		texture;
}				t_object;

typedef struct	s_camera {
	t_vec3		norm_vec;
	t_vec3		pos;
	t_vec3		look_at;
	t_vec3		up_vec;
	int			screen_height;
	int			screen_width;
	t_mat4x4	view_matrix;
	t_mat4x4	projection_matrix;
	double		fov;
	double		total_angle;
}				t_camera;


typedef struct	s_context {
	GtkApplication	*app;
	GdkFrameClock	*clock;
	int				nb_objects;
	t_object		*objects;
	t_camera		cam;
	t_mat4x4		mvp_matrix;
	GLuint			prog;
	GLuint			mvp;
	GLuint			frames;
	GLuint			center;
	GLuint			has_uv_coords;
	char			*filename;
	gdouble			prev_pos_x;
	gdouble			prev_pos_y;
	char			rotating;
	GLuint			vertex_array;
	GLuint			vertex_buffers[2];
	char			display_mode;
	float			display_percent;
	GLuint			display_mode_handle;
}				t_context;

typedef struct	s_bmp_ctx {
	int				fd;
	unsigned char	header[54];
	int				data_offset;
	int				img_width;
	int				img_height;
	unsigned int	size;
	unsigned char	*data;
}				t_bmp_ctx;

void		print_vec(t_vec3 *point);
void		print_mat4x4(t_mat4x4 *mat);
void		print_fps(GdkFrameClock *clock);
void		quit_prog(t_context *ctx);
void		print_error(t_context *ctx, const char *str, ...);
void		init_ctx(t_context *ctx);
void		init_opengl(t_context *ctx);
void		init_identity_matrix(t_mat4x4 *mat);
void		init_projection_matrix(int height, int width, t_mat4x4 *mat);
void		init_view_matrix(t_vec3 *pos, t_vec3 *center, t_vec3 *up, t_mat4x4 *ret);
void		construct_model_matrix(t_object *obj);
void		create_program(t_context *ctx);
void		vec3_sub(t_vec3 *one, t_vec3 *two, t_vec3 *out);
void		vec3_add(t_vec3 *one, t_vec3 *two, t_vec3 *out);
void		vec3_normalize(t_vec3 *in, t_vec3 *out);
void		vec3_cross(t_vec3 *one, t_vec3 *two, t_vec3 *out);
float		vec3_dot(t_vec3 *one, t_vec3 *two);
void		mat4x4_mult(t_mat4x4 *one, t_mat4x4 *two, t_mat4x4 *out);
void		mat4x4_displace(t_mat4x4 *inout, float x, float y, float z);
void		rotation_matrix_x(t_mat4x4 *mat, float angle);
void		rotation_matrix_y(t_mat4x4 *mat, float angle);
void		rotation_matrix_z(t_mat4x4 *mat, float angle);
void		rotation_vec_y(t_vec3 *vec, float angle);
void		rotation_around_axis(t_mat4x4 *mat, t_vec3 *a, double angle);
void		rotation_around_axis_vec(t_vec3 *inout, t_vec3 *a, double angle);
void		open_file_chooser(t_context *ctx);
void		load_file(t_context *ctx, int fd);
void		free_string_tab(char **str);
void		print_face_indexes(t_triangle *faces, int nb_faces);
void		print_face_coords(t_object *obj);
void		print_opengl_error(const char *str);
double		to_deg(double rad);
void		load_bmp_into_opengl(t_context *ctx, char *filename);
gboolean	key_press(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	scroll(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	button_press(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	mouse_motion(GtkWidget *widget, GdkEvent *event, t_context *ctx);

#endif
