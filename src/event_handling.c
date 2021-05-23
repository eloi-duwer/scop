/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:21 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/23 13:34:54 by eduwer           ###   ########.fr       */
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
	else if (e->keyval == GDK_KEY_space && ctx->display_mode == DISPLAY_FACES)
		ctx->display_mode = DISPLAY_TEXTURES;
	else if (e->keyval == GDK_KEY_space && ctx->display_mode == DISPLAY_TEXTURES)
		ctx->display_mode = DISPLAY_FACES;
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
	GdkEventButton *e;

	e = (GdkEventButton *)event;
	if (e->type == GDK_BUTTON_PRESS && e->button == 1)
		ctx->rotating = !ctx->rotating;
	return (TRUE);
}

gboolean	mouse_motion(GtkWidget *widget, GdkEvent *event, t_context *ctx)
{
	GdkEventMotion *e;

	e = (GdkEventMotion *)event;
	if (!ctx->rotating && ctx->prev_pos_x != -G_MAXDOUBLE && ctx->prev_pos_y != -G_MAXDOUBLE)
	{
		rotation_around_axis_vec(&ctx->cam.pos, &ctx->cam.norm_vec, 0.01 * (e->y - ctx->prev_pos_y));
		ctx->cam.total_angle += 0.01 * (e->y - ctx->prev_pos_y);
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
		rotation_vec_y(&ctx->cam.pos, -0.01 * (e->x - ctx->prev_pos_x));
		rotation_vec_y(&ctx->cam.norm_vec, -0.01 * (e->x - ctx->prev_pos_x));
		init_view_matrix(&ctx->cam.pos, &ctx->cam.look_at, &ctx->cam.up_vec, &ctx->cam.view_matrix);
	}
	ctx->prev_pos_x = e->x;
	ctx->prev_pos_y = e->y;
	return (TRUE);
}
