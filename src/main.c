/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:15 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/23 13:05:49 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static gboolean render(GtkGLArea *area, GdkGLContext *context, t_context *ctx)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, ctx->vertex_buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->vertex_buffers[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	print_opengl_error("before draw");
	glClearColor(0.99, 0.95, 0.80, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (ctx->rotating)
		rotation_matrix_y(&ctx->objects[0].rotation_matrix, 0.003);
	if (ctx->display_mode == DISPLAY_FACES && ctx->display_percent > 0.0f)
		ctx->display_percent -= 0.0125f;
	else if (ctx->display_mode == DISPLAY_TEXTURES && ctx->display_percent < 1.0f)
		ctx->display_percent += 0.0125f;
	glUniform1f(ctx->display_mode_handle, ctx->display_percent);
	construct_model_matrix(&ctx->objects[0]);
	mat4x4_mult(&ctx->objects[0].model_matrix, &ctx->cam.view_matrix, &ctx->mvp_matrix);
	mat4x4_mult(&ctx->mvp_matrix, &ctx->cam.projection_matrix, &ctx->mvp_matrix);
	glUniformMatrix4fv(ctx->mvp, 1, GL_TRUE, &ctx->mvp_matrix.mat[0][0]);
	glUniform1ui(ctx->frames, gdk_frame_clock_get_frame_counter(ctx->clock));
	print_opengl_error("before drawElements");
	glDrawElements(GL_TRIANGLES, ctx->objects[0].nb_faces * 3, GL_UNSIGNED_INT, (void *)0);
	print_opengl_error("after drawElements");
	glDisableVertexAttribArray(0);
	return (TRUE);
}

static gboolean frame_update(GdkFrameClock *clock, GtkGLArea *gl_area)
{
	print_fps(clock);
	gtk_gl_area_queue_render(gl_area);
	return (TRUE);
}

static gboolean realize_gl_area(GtkGLArea *gl_area, t_context *ctx)
{
	gtk_gl_area_make_current(gl_area);
	gtk_gl_area_set_has_depth_buffer(gl_area, TRUE);
	//gtk_gl_area_set_has_alpha(gl_area, TRUE);
	GdkGLContext *gl_context = gtk_gl_area_get_context(gl_area);
	GdkWindow *gl_window = gdk_gl_context_get_window(gl_context);
	GdkFrameClock *clock = gdk_window_get_frame_clock(gl_window);
	g_signal_connect(clock, "update", G_CALLBACK(frame_update), gl_area);
	print_opengl_error("realize_gl_area");
	ctx->clock = clock;
	init_opengl(ctx);
	gdk_frame_clock_begin_updating(clock);
	print_opengl_error("End of realizing gl area");
	return (TRUE);
}

static void on_app_activate(GApplication *app, t_context *ctx)
{
	GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
	gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
	GtkWidget *gl_area = gtk_gl_area_new();
	gtk_gl_area_set_required_version(GTK_GL_AREA(gl_area), 3, 3);
	g_signal_connect(window, "key-press-event", G_CALLBACK(key_press), ctx);
	g_signal_connect(window, "button-press-event", G_CALLBACK(button_press), ctx);
	g_signal_connect(window, "scroll-event", G_CALLBACK(scroll), ctx);
	g_signal_connect(window, "motion-notify-event", G_CALLBACK(mouse_motion), ctx);
	gtk_widget_add_events(window, GDK_SCROLL_MASK | GDK_POINTER_MOTION_MASK);
	g_signal_connect(gl_area, "render", G_CALLBACK(render), ctx);
	g_signal_connect(gl_area, "realize", G_CALLBACK(realize_gl_area), ctx);
	gtk_container_add(GTK_CONTAINER(window), gl_area);
	init_ctx(ctx);
	gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char **argv)
{
	t_context		ctx;
	GtkApplication	*app;
	int				exit_status;

	load_opengl_funcs();
	app = gtk_application_new("fr.eduwer.scop", G_APPLICATION_FLAGS_NONE);
	ctx.app = app;
	if (argc >= 2)
		ctx.filename = argv[1];
	else
		ctx.filename = NULL;
	if (argc >= 3)
		ctx.text_name = argv[2];
	else
		ctx.text_name = NULL;
	g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), &ctx);
	exit_status = g_application_run(G_APPLICATION(app), 0, NULL);
	g_object_unref(app);
	return (exit_status);
}
