/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_updatemap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:36:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/24 18:24:55 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_getxcolour(int i)
{
	int y;
	int x;
	int	c;

	x = (i * 3) % (V_SEP - 8) + 5;
	y = (i * 3) / (V_SEP - 8) + 2;
	c = mvinch(y, x) & A_COLOR;
	if (c == COLOR_PAIR(1))
		return (1);
	else if (c == COLOR_PAIR(2))
		return (2);
	else if (c == COLOR_PAIR(3))
		return (3);
	else if (c == COLOR_PAIR(4))
		return (4);
	else
		return (0);
}

int		cr_vis_getxrev(int i)
{
	int y;
	int x;
	int	c;

	x = (i * 3) % (V_SEP - 8) + 5;
	y = (i * 3) / (V_SEP - 8) + 2;
	c = (mvinch(y, x) & A_ATTRIBUTES) & A_REVERSE;
	if (c)
		return (1);
	return (0);
}

int		cr_vis_checkzero(int i)
{
	int y;
	int x;

	x = (i * 3) % (V_SEP - 8) + 5;
	y = (i * 3) / (V_SEP - 8) + 2;
	if (((mvinch(y, x) & A_CHARTEXT) == '0') && ((mvinch(y, x + 1) & A_CHARTEXT) == '0'))
		return (0);
	return (1);
}

int		cr_vis_printcar(corewar_t *cr)
{
	carriage_t	*car;
	int			colour;
	int			i;

	car = cr->carriages;
	i = -1;
	while (++i < cr->carriages_amount)
	{
		colour = cr_vis_getxcolour(car->current_location);;
		if (!car->carry || !cr_vis_checkzero(car->current_location))
			colour = car->owner->id;
		cr_vis_putx(cr->arena->field[car->current_location], car->current_location, colour, 1);
		car = car->next;
	}
	return (0);
}

int		cr_vis_printdiff(corewar_t *cr)
{
	int				i;
	unsigned char	*f_vis;
	unsigned char	*f_cr;

	i = -1;
	f_vis = cr->vis->field;
	f_cr = cr->arena->field;
	while (++i < MEM_SIZE)
	{
		if (f_vis[i] != f_cr[i] || cr_vis_getxrev(i))
		{
			cr_vis_putx(f_cr[i], i, cr_vis_getxcolour(i), 0);
			f_vis[i] = f_cr[i];
		}
	}
	return (0);
}

int		cr_vis_updatemap(corewar_t *cr)
{
	cr_vis_printdiff(cr);
	cr_vis_printcar(cr);
	return (0);
}