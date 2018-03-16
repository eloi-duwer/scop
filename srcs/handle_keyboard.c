#include <scop.h>

void	handlekeyboarddown(t_infos *infos)
{
	int key;

	key = (infos->event).key.keysym.sym;
	if (key == SDLK_ESCAPE)
		quit_prog(infos);
}

