/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:50:13 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/30 17:03:49 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_timer(t_corewar *cr)
{
	long int	check;
	t_vis		*vis;

	vis = cr->vis;
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

int		cr_vis_keys(t_corewar *cr)
{
	int key;
	t_vis		*vis;

	vis = cr->vis;
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
	if (key == KEY_UP)
		vis->car_place = (vis->car_place + V_CARVOL >= cr->carriages_amount) ?
		vis->car_place : (vis->car_place + V_CARVOL);
	if (key == KEY_DOWN)
		vis->car_place =
		(vis->car_place <= 0) ? 0 : (vis->car_place - V_CARVOL);
	if (key == 'c')
		vis->carinfo = vis->carinfo ? 0 : 1;
	if (key == 'i')
		vis->info = vis->info ? 0 : 1;
	return (0);
}