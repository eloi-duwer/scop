#ifndef __SCOP_H__
# define __SCOP_H__
# include <gtk/gtk.h>
# include <stdio.h>
# include <gl_init.h>
# include <libftprintf.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# define BUFF_SIZE 1000
# define NB_DISPLAY_MODES 4

typedef struct	s_mat4x4 {
	float		mat[4][4];
}				t_mat4x4;

typedef struct	s_vec3 {
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec2 {
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_triangle {
	uint32_t	points[3];
}				t_triangle;

typedef struct	s_object {
	uint64_t	nb_faces;
	uint64_t	size_faces;
	t_triangle	*faces;
	uint64_t	nb_vertexes;
	uint64_t	size_vertexes;
	t_vec3		*vertexes;
	uint64_t	nb_tex_coords;
	uint64_t	size_tex_coords;
	t_vec2		*tex_coords;
	t_vec3		center;
	t_vec3		world_position;
	t_vec3		dimensions;
	t_vec3		min_coords;
	t_vec3		max_coords;
	t_mat4x4	rotation_matrix;
	t_mat4x4	model_matrix;
	t_mat4x4	mvp_matrix;
	GLuint		mvp_handle;
	GLuint		texture;
	GLuint		vertex_array;
	GLuint		vertex_buffers[2];
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
	GdkWindow		*window;
	GdkSeat			seat;
	int				nb_objects;
	t_object		objects[1];
	t_camera		cam;
	t_object		skybox;
	GLuint			prog_object;
	GLuint			prog_skybox;
	GLuint			frames;
	GLuint			has_uv_coords;
	GLuint			min_pos_handle;
	GLuint			max_pos_handle;
	GLuint			tex_skybox;
	char			*filename;
	char			*text_name;
	gdouble			screen_cursor_x;
	gdouble			screen_cursor_y;
	gdouble			window_cursor_x;
	gdouble			window_cursor_y;
	char			rotating;
	int				display_target;
	float			display_current;
	GLuint			display_mode_handle;
}				t_context;

typedef struct	s_bmp_ctx {
	int				fd;
	int32_t			data_offset;
	int32_t			img_width;
	int32_t			img_height;
	uint32_t		size;
	unsigned char	*data;
}				t_bmp_ctx;

void		print_vec(t_vec3 *point);
void		print_mat4x4(t_mat4x4 *mat);
void		print_fps(GdkFrameClock *clock);
void		quit_prog(t_context *ctx);
void		print_error(t_context *ctx, const char *str, ...);
gboolean	render(GtkGLArea *area, GdkGLContext *context, t_context *ctx);
void		init_ctx(t_context *ctx);
void		init_opengl(t_context *ctx);
void		init_identity_matrix(t_mat4x4 *mat);
void		init_projection_matrix(int height, int width, t_mat4x4 *mat);
void		init_view_matrix(t_vec3 *pos, t_vec3 *center, t_vec3 *up, t_mat4x4 *ret);
void		construct_model_matrix(t_context *ctx, t_object *obj, int center_around_camera);
GLuint		create_program(t_context *ctx, const char *fragment_shader, const char *vertex_shader);
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
void		load_object_from_file(t_object *obj_ret, t_context *ctx, const char *filename);
void		parse_line(t_context *ctx, t_object *obj, char *line, int line_nb);
void		free_string_tab(char **str);
void		print_face_indexes(t_triangle *faces, int nb_faces);
void		print_face_coords(t_object *obj);
void		print_opengl_error(const char *str);
double		to_deg(double rad);
void		load_bmp(t_context *ctx, t_bmp_ctx *bmp, const char *filename);
void		free_mbp(t_bmp_ctx *bmp);
void		load_bmp_into_opengl(t_context *ctx, char *filename);
void		load_skybox_into_opengl(t_context *ctx);
gboolean	key_press(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	scroll(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	button_press(GtkWidget *widget, GdkEvent *event, t_context *ctx);
gboolean	mouse_motion(GtkWidget *widget, GdkEvent *event, t_context *ctx);

#endif
