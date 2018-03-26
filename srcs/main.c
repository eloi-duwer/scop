/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:50:13 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 16:36:29 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	main_loop(t_infos *infos)
{
	int i;

	glUniformMatrix4fv(infos->mat_proj_id, 1, GL_FALSE, infos->proj.projection_matrix);
	glUniform3f(infos->deplacement_id, 0.0, 0.0, infos->obj_distance);
	glUniform3f(infos->comp_id, infos->middle_obj_pos.x, infos->middle_obj_pos.y, infos->middle_obj_pos.z);
	glUniform1f(infos->scale_id, infos->scale);
	while (true)
	{
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniformMatrix4fv(infos->mat_rot_id, 1, GL_FALSE, infos->proj.rotation_matrix);
		i = 0;
		while (i < infos->nb_indexes / 6)
		{
			glUniform1i(infos->color_id, i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)(i * 6 * sizeof(GLuint)));
			++i;
		}
		//glDrawElements(GL_TRIANGLES, infos->nb_indexes, GL_UNSIGNED_INT, (void *)0);
		glFlush();
		SDL_GL_SwapWindow(infos->window);
		if (infos->mouse_control == false)
			rotation_matrix_y(infos->proj.rotation_matrix, 0.02);
	}
}

int		main(int argc, char *argv[])
{
	t_infos infos;

	init_struct(&infos);
	parse_file(&infos, argc, argv);
	init_sdl_opengl(&infos);
	setup_objects(&infos);
	init_projection_infos(&infos, &infos.proj);
	infos.scale = 5 / fmax(fmax(infos.max_point.x - \
		infos.min_point.x,infos.max_point.y - infos.min_point.y), \
		infos.max_point.z - infos.min_point.z);
	main_loop(&infos);
	return (0);
}
