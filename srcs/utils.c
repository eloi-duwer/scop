#include <scop.h>

void	free_string_tab(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	quit_prog(t_infos *infos)
{
	if (infos->window != NULL)
		SDL_DestroyWindow(infos->window);
	free(infos->vertices);
	free(infos->indexes);
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
	else if (event_type == SDL_MOUSEBUTTONDOWN && infos->event.button.button \
		== SDL_BUTTON_LEFT)
	{
		if (infos->mouse_control == false)
		{
			infos->mouse_control = true;
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else
		{
			infos->mouse_control = false;
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	else if (event_type == SDL_MOUSEMOTION && infos->mouse_control == true)
	{
		rotation_matrix_x(infos->proj.rotation_matrix, 0.01 * infos->event.motion.yrel);
		rotation_matrix_y(infos->proj.rotation_matrix, 0.01 * infos->event.motion.xrel);
	}
	else if (event_type == SDL_MOUSEWHEEL)
	{
		infos->obj_distance *= (infos->event.wheel.y > 0 ? 0.9: 1.1);
		glUniform3f(infos->deplacement_id, 0.0, 0.0, infos->obj_distance);
	}
}
