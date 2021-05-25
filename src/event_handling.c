/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:21 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/25 01:32:39 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void	do_scroll(t_context *ctx, float scale_factor)
{
	ctx->cam.pos.x *= scale_factor;
	ctx->cam.pos.y *= scale_factor;
	ctx->cam.pos.z *= scale_factor;
	init_view_matrix(&ctx->cam.pos, &ctx->cam.look_at, &ctx->cam.up_vec, \
		&ctx->cam.view_matrix);
}

gboolean	key_press(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	GdkEventKey	*e;

	e = (GdkEventKey *)event;
	if (e->keyval == GDK_KEY_Escape)
		quit_prog(ctx);
	else if (e->state & GDK_CONTROL_MASK && e->keyval == GDK_KEY_o)
		open_file_chooser(ctx);
	else if (e->keyval == GDK_KEY_l)
		ctx->objects[0].world_position.x -= 0.1;
	else if (e->keyval == GDK_KEY_j)
		ctx->objects[0].world_position.x += 0.1;
	else if (e->keyval == GDK_KEY_i)
		ctx->objects[0].world_position.y += 0.1;
	else if (e->keyval == GDK_KEY_k)
		ctx->objects[0].world_position.y -= 0.1;
	else if (e->keyval == GDK_KEY_u)
		ctx->objects[0].world_position.z += 0.1;
	else if (e->keyval == GDK_KEY_o)
		ctx->objects[0].world_position.z -= 0.1;
	else if (e->keyval == GDK_KEY_plus || e->keyval == GDK_KEY_KP_Add)
		do_scroll(ctx,  1 / 1.25);
	else if (e->keyval == GDK_KEY_minus || e->keyval == GDK_KEY_KP_Subtract)
		do_scroll(ctx, 1.25);
	else if (e->keyval == GDK_KEY_space)
		ctx->display_target = (ctx->display_target + 1) % 4;
	return (TRUE);
}

gboolean	scroll(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	GdkEventScroll	*e;

	e = (GdkEventScroll *)event;
	if (e->direction == GDK_SCROLL_DOWN)
		do_scroll(ctx, 1.25);
	else if (e->direction == GDK_SCROLL_UP)
		do_scroll(ctx, 1 / 1.25);
	return (TRUE);
}

gboolean	button_press(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	GdkEventButton	*e;
	GdkDisplay		*display;
	GdkSeat			*seat;
	gint			pos_win[2];
	gdouble			pos_cursor[2];

	e = (GdkEventButton *)event;
	if (e->type == GDK_BUTTON_PRESS && e->button == 1)
	{
		display  = gdk_display_get_default();
		seat = gdk_display_get_default_seat(display);
		if (ctx->rotating)
		{
			gdk_seat_grab(seat, ctx->window, GDK_SEAT_CAPABILITY_ALL_POINTING, TRUE, gdk_cursor_new_for_display(display, GDK_BLANK_CURSOR), event, NULL, NULL);
			gdk_device_get_position_double(gdk_seat_get_pointer(seat), NULL, pos_cursor, pos_cursor + 1);
			gdk_window_get_position(ctx->window, pos_win, pos_win + 1);
			ctx->screen_cursor_x = pos_cursor[0];
			ctx->screen_cursor_y = pos_cursor[1];
			ctx->window_cursor_x = pos_cursor[0] - pos_win[0];
			ctx->window_cursor_y = pos_cursor[1] - pos_win[1];
		}
		else
			gdk_seat_ungrab(gdk_display_get_default_seat(display));
		ctx->rotating = !ctx->rotating;
	}
	return (TRUE);
}

gboolean	mouse_motion(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	GdkEventMotion	*e;
	GdkDevice		*device;

	e = (GdkEventMotion *)event;
	if (!ctx->rotating && (e->x != ctx->window_cursor_x || e->y != ctx->window_cursor_y))
	{
		rotation_around_axis_vec(&ctx->cam.pos, &ctx->cam.norm_vec, 0.01 * (e->y - ctx->window_cursor_y));
		ctx->cam.total_angle += 0.01 * (e->y - ctx->window_cursor_y);
		if (ctx->cam.total_angle > M_PI / 2)
		{
			ctx->cam.up_vec.y = -ctx->cam.up_vec.y;
			ctx->cam.total_angle -= M_PI;
		}
		else if (ctx->cam.total_angle < -M_PI / 2)
		{
			ctx->cam.up_vec.y = -ctx->cam.up_vec.y;
			ctx->cam.total_angle += M_PI;
		}
		rotation_vec_y(&ctx->cam.pos, -0.01 * (e->x - ctx->window_cursor_x));
		rotation_vec_y(&ctx->cam.norm_vec, -0.01 * (e->x - ctx->window_cursor_x));
		init_view_matrix(&ctx->cam.pos, &ctx->cam.look_at, &ctx->cam.up_vec, &ctx->cam.view_matrix);
		device = gdk_seat_get_pointer(gdk_display_get_default_seat(gdk_display_get_default()));
		gdk_device_warp(device, gdk_screen_get_default(), ctx->screen_cursor_x, ctx->screen_cursor_y);
	}
	return (TRUE);
}
