/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:27 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/04 23:03:21 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ctx->nb_objects = 1;
	ctx->display_current = 0.0f;
	ctx->display_target = 0;
	init_projection_matrix(ctx->cam.screen_height, ctx->cam.screen_width, \
		&ctx->cam.projection_matrix);
	init_view_matrix(&ctx->cam.pos, &ctx->cam.look_at, &ctx->cam.up_vec, \
		&ctx->cam.view_matrix);
	ctx->rotating = 1;
}

void	init_opengl(t_context *ctx)
{
	print_opengl_error("Before loading progs");
	ctx->prog_object = create_program(ctx, "./shaders/object_fragment.glsl", "./shaders/object_vertex.glsl");
	ctx->prog_skybox = create_program(ctx, "./shaders/skybox_fragment.glsl", "./shaders/skybox_vertex.glsl");
	print_opengl_error("After loading progs");
	ctx->frames = glGetUniformLocation(ctx->prog_object, "frames");
	ctx->has_uv_coords = glGetUniformLocation(ctx->prog_object, "has_uv_coords");
	ctx->display_mode_handle = glGetUniformLocation(ctx->prog_object, "display_percent");
	ctx->min_pos_handle = glGetUniformLocation(ctx->prog_object, "min_coord");
	ctx->max_pos_handle = glGetUniformLocation(ctx->prog_object, "max_coord");
	glEnable(GL_DEPTH_TEST);
	print_opengl_error("Before loading file");
	glUseProgram(ctx->prog_object);
	load_object_from_file(ctx->objects, ctx, ctx->filename, ctx->text_name);
	load_skybox_into_opengl(ctx);
	ctx->skybox.mvp_handle = glGetUniformLocation(ctx->prog_skybox, "view_projection_mat");
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

void	check_size_buff_tri(t_context *ctx, t_buff_tri *buff_tri)
{
	t_triangle *new_triangles;

	if (buff_tri->nbel == buff_tri->size)
	{
		if (!(new_triangles = (t_triangle *)realloc(buff_tri->b, \
			sizeof(t_triangle) * (buff_tri->nbel + BUFF_SIZE))))
			print_error(ctx, "Realloc returned NULL\n");
		buff_tri->b = new_triangles;
		buff_tri->size += BUFF_SIZE;
	}
}

void	check_size_buff_vec2(t_context *ctx, t_buff_vec2 *buff_vec2)
{
	t_vec2 *new_vec2;

	if (buff_vec2->nbel == buff_vec2->size)
	{
		if (!(new_vec2 = (t_vec2 *)realloc(buff_vec2->b, \
			sizeof(t_vec2) * (buff_vec2->nbel + BUFF_SIZE))))
			print_error(ctx, "Realloc returned NULL\n");
		buff_vec2->b = new_vec2;
		buff_vec2->size += BUFF_SIZE;
	}
}

void	check_size_buff_vec3(t_context *ctx, t_buff_vec3 *buff_vec3)
{
	t_vec3 *new_vec3;

	if (buff_vec3->nbel == buff_vec3->size)
	{
		if (!(new_vec3 = (t_vec3 *)realloc(buff_vec3->b, \
			sizeof(t_vec3) * (buff_vec3->nbel + BUFF_SIZE))))
			print_error(ctx, "Realloc returned NULL\n");
		buff_vec3->b = new_vec3;
		buff_vec3->size += BUFF_SIZE;
	}
}
