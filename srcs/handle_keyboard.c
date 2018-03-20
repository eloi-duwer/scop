/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:49:44 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/20 15:59:01 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	handlekeyboarddown(t_infos *infos)
{
	int key;

	key = (infos->event).key.keysym.sym;
	if (key == SDLK_ESCAPE)
		quit_prog(infos);
}
