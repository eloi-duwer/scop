/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:15 by eduwer            #+#    #+#             */
/*   Updated: 2021/06/03 17:14:19 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

char	*g_default_obj = "./models/42.obj";
char	*g_default_tex = "./textures/unicorn_pattern.bmp";

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
	GdkGLContext *gl_context = gtk_gl_area_get_context(gl_area);
	ctx->window = gdk_gl_context_get_window(gl_context);
	GdkFrameClock *clock = gdk_window_get_frame_clock(ctx->window);
	g_signal_connect(clock, "update", G_CALLBACK(frame_update), gl_area);
	print_opengl_error("realize_gl_area");
	ctx->clock = clock;
	init_opengl(ctx);
	gdk_frame_clock_begin_updating(clock);
	print_opengl_error("End of realizing gl area");
	return (TRUE);
}

static gboolean blur_event(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	gdk_seat_ungrab(gdk_display_get_default_seat(gdk_display_get_default()));
	ctx->rotating = true;
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
	g_signal_connect(window, "focus-out-event", G_CALLBACK(blur_event), ctx);
	gtk_widget_add_events(window, GDK_SCROLL_MASK | GDK_POINTER_MOTION_MASK | GDK_FOCUS_CHANGE_MASK);
	g_signal_connect(gl_area, "render", G_CALLBACK(render), ctx);
	g_signal_connect(gl_area, "realize", G_CALLBACK(realize_gl_area), ctx);
	gtk_container_add(GTK_CONTAINER(window), gl_area);
	init_ctx(ctx);
	gtk_widget_show_all(GTK_WIDGET(window));
}

static int	print_help(void)
{
	ft_fdprintf(2, "Usage: ./scop [object file] [texture file]\n\n\
Controls once the object is loaded:\n\
i, j, k, l, u, o : Move the camera Up, Left, Down, Right, Backward, Forward respectively\n\
Scroll whell / + and - : zoom / unzoom\n\
Left click : Stop the object rotation and Rotate the camera manually\n\
Space: Apply the texture\n\
Ctrl + o: Open an another file object\n");
	return (0);
}

int main(int argc, char **argv)
{
	t_context		ctx;
	GtkApplication	*app;
	int				exit_status;

	if (argc == 2 && ft_strcmp(argv[1], "-h") == 0)
		return (print_help());
	load_opengl_funcs();
	app = gtk_application_new("fr.eduwer.scop", G_APPLICATION_FLAGS_NONE);
	ctx.app = app;
	if (argc >= 2)
		ctx.filename = argv[1];
	else
		ctx.filename = g_default_obj;
	if (argc >= 3)
		ctx.text_name = argv[2];
	else
		ctx.text_name = g_default_tex;
	g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), &ctx);
	exit_status = g_application_run(G_APPLICATION(app), 0, NULL);
	g_object_unref(app);
	return (exit_status);
}
