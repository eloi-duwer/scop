#include <scop.h>

void	init_ctx(t_context *ctx)
{
	ctx->cam.pos = (t_vec3) {0.0f, 0.0f, -4.0f};
	ctx->cam.norm_vec = (t_vec3) { 1.0f, 0.0f, 0.0f };
	ctx->cam.look_at = (t_vec3) {0.0f, 0.0f, 0.0f};
	ctx->cam.up_vec = (t_vec3) {0.0f, 1.0f, 0.0f};
	ctx->cam.total_angle = 0.0f;
	ctx->cam.screen_width = 1280;
	ctx->cam.screen_height = 720;
	init_projection_matrix(ctx->cam.screen_height, ctx->cam.screen_width, \
		&ctx->cam.projection_matrix);
	init_view_matrix(&ctx->cam.pos, &ctx->cam.look_at, &ctx->cam.up_vec, \
		&ctx->cam.view_matrix);
	ctx->rotating = 1;
	ctx->prev_pos_x = -G_MAXDOUBLE;
	ctx->prev_pos_y = -G_MAXDOUBLE;
}

void	init_opengl(t_context *ctx)
{
	int	fd;

	glewExperimental = GL_TRUE;
	glewInit();
	create_program(ctx);
	ctx->mvp = glGetUniformLocation(ctx->prog, "model_view_projection_mat");
	ctx->frames = glGetUniformLocation(ctx->prog, "frames");
	ctx->center = glGetUniformLocation(ctx->prog, "center");
	ctx->has_uv_coords = glGetUniformLocation(ctx->prog, "has_uv_coords");
	ctx->display_mode_handle = glGetUniformLocation(ctx->prog, "display_percent");
	ctx->display_mode = DISPLAY_FACES;
	ctx->display_percent = 0.0f;
	glUniform1i(ctx->has_uv_coords, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glFrontFace(GL_BACK);
	if (ctx->filename)
		fd = open(ctx->filename, O_RDONLY);
	else
		fd = open("./models/42.obj", O_RDONLY);
	if (fd == -1)
		print_error(ctx, "File %s can't be opened\n", ctx->filename);
	print_opengl_error("avant load file");
	load_file(ctx, fd);
	close(fd);
}

void	quit_prog(t_context *ctx)
{
	g_application_quit(G_APPLICATION(ctx->app));
}

void	print_error(t_context *ctx, const char *str, ...)
{
	va_list lst;

	va_start(lst, str);
	vprintf(str, lst);
	va_end(lst);
	exit(1);
}

void	free_string_tab(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	print_opengl_error(const char *str)
{
	int error;

	while ((error = glGetError()) != GL_NO_ERROR)
	{
		printf("OpenGL Error (%s): %x\n", str, error);
	}
}

double	to_deg(double rad)
{
	return (rad * 180) / M_PI;
}
