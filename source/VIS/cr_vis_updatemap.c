/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_updatemap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:36:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/29 16:37:12 by dbrady           ###   ########.fr       */
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

int		cr_vis_printcarmap(corewar_t *cr)
{
	carriage_t	*car;
	int			colour;
	int			i;

	car = cr->p_carriage_obj;
	i = -1;
	while (++i < cr->carriages_amount)
	{
		colour = cr_vis_getxcolour(car->current_location);
		cr_vis_putx(cr->p_arena_obj->p_field[car->current_location], car->current_location, colour, 1, cr);
		car = car->p_next;
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
	f_cr = cr->p_arena_obj->p_field;
	while (++i < MEM_SIZE)
	{
		if (f_vis[i] != f_cr[i] || cr_vis_getxrev(i))
		{
			cr_vis_putx(f_cr[i], i, cr_vis_getxcolour(i), 0, cr);
			f_vis[i] = f_cr[i];
		}
	}
	return (0);
}

int		cr_vis_updatemap(corewar_t *cr)
{
	cr_vis_printdiff(cr);
	cr_vis_printcarmap(cr);
	return (0);
}