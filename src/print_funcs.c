/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:21:51 by eduwer            #+#    #+#             */
/*   Updated: 2021/05/22 17:21:52 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	print_vec(t_vec3 *point)
{
	printf("Vec3 (%f, %f, %f)\n", point->x, point->y, point->z);
}

void	print_face_indexes(t_triangle *faces, int nb_faces)
{
	int	i;

	i = -1;
	printf("faces (%p)\n", faces);
	while (++i < nb_faces)
	{
		printf("\t%d %d %d\n", faces[i].points[0], faces[i].points[1], \
			faces[i].points[2]);
	}
}

void	print_face_coords(t_object *obj)
{
	int	i;

	printf("faces coords (obj %p)\n", obj);
	i = -1;
	while (++i < obj->nb_faces)
	{
		printf("Face %d:\n", i);
		printf("\t");
		print_vec(&obj->vertexes[obj->faces[i].points[0]]);
		printf("\t");
		print_vec(&obj->vertexes[obj->faces[i].points[1]]);
		printf("\t");
		print_vec(&obj->vertexes[obj->faces[i].points[2]]);
	}
}

void	print_mat4x4(t_mat4x4 *mat)
{
	int i;

	printf("Mat4x4: (\n\t(");
	i = 0;
	while (i < 16)
	{
		if (i > 0 && i % 4 == 0)
			printf(")\n\t(");
		printf("%.4f", mat->mat[i / 4][i % 4]);
		if (i < 15)
			printf(", ");
		++i;
	}
	printf("\n)\n");
}

void	print_fps(GdkFrameClock *clock)
{
	static	gint64 last_time;
	static	gint64 last_frame_count;
	gint64	current_time;
	gint64	current_frame_count;

	current_time = gdk_frame_clock_get_frame_time(clock);
	current_frame_count = gdk_frame_clock_get_frame_counter(clock);
	if (current_frame_count == 0)
	{
		last_time = current_time;
		last_frame_count = current_frame_count;
	}
	else if (current_time - last_time > 5 * 1000000)
	{
		printf("fps: %.2f\n", \
			(double)(current_frame_count - last_frame_count) / \
			((double)(current_time - last_time) / 1000000.0f));
		last_time = current_time;
		last_frame_count = current_frame_count;
	}
}
