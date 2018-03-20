#include <scop.h>

void	print_mat(float *mat)
{
	int i;
	int j;

	i = 0;
	printf("Going to print matrix:\n");
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.2f, ", mat[i + j * 4]);
			++j;
		}
		printf("\n");
		++i;
	}
}

void	quit_prog(t_infos *infos)
{
	SDL_DestroyWindow(infos->window);
	SDL_Quit();
	exit(0);
}

void	print_error(t_infos *infos, char *str)
{
	printf("%s\n", str);
	quit_prog(infos);
}

void	test_event(t_infos *infos)
{
	int event_type;

	event_type = (infos->event).type;
	if (event_type == SDL_KEYDOWN)
		handlekeyboarddown(infos);
	else if (event_type == SDL_QUIT)
		quit_prog(infos);
}

void	main_loop(t_infos *infos)
{
	float			matrix[16];
	t_projection	projection;

	infos->mat_proj_id = glGetUniformLocation(infos->program, "projection");
	infos->mat_rot_id = glGetUniformLocation(infos->program, "rotation");
	infos->deplacement_id = glGetUniformLocation(infos->program, "deplacement");
	init_identity_matrix(matrix);
	init_projection_infos(infos, &projection);
	glUniform3f(infos->deplacement_id, 0.0, 0.0, -5.0);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	while (true)
	{
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniformMatrix4fv(infos->mat_proj_id, 1, GL_FALSE, projection.projection_matrix);
		glUniformMatrix4fv(infos->mat_rot_id, 1, GL_FALSE, matrix);
		rotation_matrix_Y(matrix, 0.01);
			rotation_matrix_X(matrix, 0.01);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
		glFlush();
		SDL_GL_SwapWindow(infos->window);
	}
}

int		main(int argc, char *argv[])
{
	t_infos infos;

	init_sdl_opengl(&infos);
	setup_objects(&infos);
	main_loop(&infos);
	return 0;
}
