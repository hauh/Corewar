/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:50:13 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/24 16:31:23 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_timer(t_vis	*vis)
{
	long int check;

	// if (!vis->time)
	// 	vis->time = clock();
	if (time < 0)
		return (1);
	check = clock();
	if ((check - vis->time) >= (CLOCKS_PER_SEC / vis->fpsdiv))
	{
		vis->tick = 1;
		vis->time = check;
	}
	return (0);
}

int		cr_vis_keys(t_vis *vis)
{
	int key;

	key = getch();
	if (key == KEY_F(1))
		vis->exit = 1;
	if (key == 'f')
		vis->flow = !vis->flow;
	if (key == 's')
		vis->step = 1;
	if (key == ']')
		vis->fpsdiv = vis->fpsdiv >= 1000 ? 1000 : vis->fpsdiv + 10;
	if (key == '[')
		vis->fpsdiv = vis->fpsdiv <= 10 ? 10 : vis->fpsdiv - 10;
	return (0);
}