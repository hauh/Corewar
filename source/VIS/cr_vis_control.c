/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:50:13 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/05 14:10:01 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_timer(t_corewar *cr)
{
	long int	check;
	t_vis		*vis;

	vis = cr->vis;
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

void	cr_vis_morekeys(t_corewar *cr, int key)
{
	t_vis		*vis;

	vis = cr->vis;
	if (key == 'i')
		vis->info = (vis->info == 1) ? 0 : 1;
	if (key == 'k')
		cr_vis_sound(cr->vis, 'k');
	if (key == 'b')
		cr_vis_sound(cr->vis, 'b');
	if (key == 'h')
		cr_vis_sound(cr->vis, 'h');
}

int		cr_vis_keys(t_corewar *cr)
{
	int			key;
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
		vis->carinfo = (vis->carinfo == 1) ? 0 : 1;
	cr_vis_morekeys(cr, key);
	return (0);
}
