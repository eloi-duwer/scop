#include <scop.h>

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
	while (true)
	{
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glDrawArrays(GL_TRIANGLES, 1, 3);
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
    SDL_Quit();

    return 0;
}
