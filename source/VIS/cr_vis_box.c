/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:06:01 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/04 14:11:50 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_buildbox(int part)
{
	int x;
	int y;

	y = -1;
	while (++y < V_H)
	{
		x = -1;
		while (++x < V_W)
		{
			if ((part == V_LEFT || part == V_SCREEN) && (x == 0 || x == 1 ||
			y == 0 || y == V_H - 1 || x == V_SEP + 2 || x == V_SEP + 1))
				if (x <= V_SEP + 2)
					mvaddstr(y, x, V_BSYM);
			if ((part == V_MID || part == V_SCREEN) && (y == 0 ||
			y == V_H - 1 || x == V_SEPSEP || x == V_SEPSEP + 1))
				if (x > V_SEP + 2 && x <= V_SEPSEP + 1)
					mvaddstr(y, x, V_BSYM);
			if ((part == V_RIGHT || part == V_SCREEN) && (y == 0 ||
			y == V_H - 1 || x == V_W - 1 || x == V_W - 2
			|| x == V_SEPSEP || x == V_SEPSEP + 1))
				if (x >= V_SEPSEP)
					mvaddstr(y, x, V_BSYM);
		}
	}
}

void	cr_vis_clearbox(int part)
{
	int		y;
	int		x;
	char	*str;

	y = (part == V_MID) ? (V_SEPSEP - V_SEP) : (V_W - V_SEPSEP);
	str = ft_strnew(y);
	ft_memset(str, ' ', y);
	y = -1;
	x = (part == V_MID) ? V_SEP + 3 : V_SEPSEP;
	while (++y < V_H)
		mvprintw(y, x, str);
	ft_strdel(&str);
}
