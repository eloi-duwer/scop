/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 00:59:54 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/03 20:22:19 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	render_obj(t_context *ctx, t_object *obj);
static void	render_skybox(t_context *ctx, t_object *skybox);

gboolean	render(GtkGLArea *area, GdkGLContext *context, t_context *ctx)
{
	glClearColor(0.99, 0.95, 0.80, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if ((int)floor(ctx->display_current) != ctx->display_target)
	{
		ctx->display_current += 0.0125f;
		if (ctx->display_current >= (float)NB_DISPLAY_MODES)
			ctx->display_current = 0;
	}
	for (int i = 0; i < ctx->nb_objects; i++)
		render_obj(ctx, &ctx->objects[i]);
	render_skybox(ctx, &ctx->skybox);
	return (TRUE);
}

static void	render_obj(t_context *ctx, t_object *obj)
{
	print_opengl_error("before render_obj");
	if (ctx->rotating)
		rotation_matrix_y(&obj->rotation_matrix, 0.003);
	glUseProgram(ctx->prog_object);
	glBindVertexArray(obj->vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->vertex_buffers[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->texture);
	glDepthFunc(GL_LESS);
	glUniform3f(ctx->min_pos_handle, obj->min_coords.x, obj->min_coords.y, obj->min_coords.z);
	glUniform3f(ctx->max_pos_handle, obj->max_coords.x, obj->max_coords.y, obj->max_coords.z);
	glUniform1i(ctx->has_uv_coords, GL_FALSE);
	glUniform1ui(ctx->frames, gdk_frame_clock_get_frame_counter(ctx->clock));
	glUniform1f(ctx->display_mode_handle, ctx->display_current);
	construct_model_matrix(ctx, obj, 0);
	mat4x4_mult(&obj->model_matrix, &ctx->cam.view_matrix, &obj->mvp_matrix);
	mat4x4_mult(&obj->mvp_matrix, &ctx->cam.projection_matrix, &obj->mvp_matrix);
	glUniformMatrix4fv(obj->mvp_handle, 1, GL_TRUE, &obj->mvp_matrix.mat[0][0]);
	print_opengl_error("before drawElements object");
	glDrawElements(GL_TRIANGLES, obj->nb_faces * 3, GL_UNSIGNED_INT, (void *)0);
	glBindVertexArray(0);
	print_opengl_error("after drawElements object");
}

static void	render_skybox(t_context *ctx, t_object *skybox)
{
	print_opengl_error("Before rendering skybox");
	glUseProgram(ctx->prog_skybox);
	glBindVertexArray(skybox->vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, skybox->vertex_buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skybox->vertex_buffers[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ctx->skybox.texture);
	glDepthFunc(GL_LEQUAL);
	construct_model_matrix(ctx, skybox, 1);
	mat4x4_mult(&skybox->model_matrix, &ctx->cam.view_matrix, &skybox->mvp_matrix);
	mat4x4_mult(&skybox->mvp_matrix, &ctx->cam.projection_matrix, &skybox->mvp_matrix);
	glUniformMatrix4fv(skybox->mvp_handle, 1, GL_TRUE, &skybox->mvp_matrix.mat[0][0]);
	print_opengl_error("before drawElements skybox");
	glDrawElements(GL_TRIANGLES, skybox->nb_faces * 3, GL_UNSIGNED_INT, (void *)0);
	glBindVertexArray(0);
	print_opengl_error("After rendering skybox");
}