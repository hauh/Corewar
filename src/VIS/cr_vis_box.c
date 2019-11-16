/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:06:01 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/16 13:34:14 by dbrady           ###   ########.fr       */
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

void	cr_vis_clearbox(int part, int mini)
{
	int		y;
	int		x;
	char	*str;

	mini = 0;
	y = (part == V_MID) ? (V_SEPSEP - V_SEP) : (V_W - V_SEPSEP);
	str = ft_strnew(y);
	ft_memset(str, ' ', y);
	y = -1;
	x = (part == V_MID) ? V_SEP + 3 : V_SEPSEP;
	while (++y < V_H)
		mvprintw(y, x, str);
	ft_strdel(&str);
}

int		cr_vis_box_manager(int action)
{
	static t_box *box;

	if (!box)
	{
		box = (t_box *)malloc(sizeof(t_box));
		box->vh = (action == V_BM_SET_MINI) ? 68 : 100;
		box->vs = (action == V_BM_SET_MINI) ? 200 : 136;
		box->vss = box->vs + 60;
		box->vw = (action == V_BM_SET_MINI) ? box->vs + 62 : 400;
		box->vcarvol = box->vh / 3 - 2;
	}
	if (action == V_BM_GET_VW)
		return (box->vw);
	else if (action == V_BM_GET_VH)
		return (box->vh);
	else if (action == V_BM_GET_VS)
		return (box->vs);
	else if (action == V_BM_GET_VSS)
		return (box->vss);
	else if (action == V_BM_GET_VCARVOL)
		return (box->vcarvol);
	else if (action == V_BM_CLEAR)
		free(box);
	return (0);
}
