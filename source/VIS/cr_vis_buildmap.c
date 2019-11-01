/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_buildmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/01 13:38:26 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cr_vis_putx(int num, int i, int colour, int rev, t_corewar *cr)
{
	char	ret[3];
	char	*power = "0123456789abcdef";
	int		x;
	int		y;

	cr->vis->field[i] = num;
	x = (i * 3) % (V_SEP - 8) + 5;
	y = (i * 3) / (V_SEP - 8) + 2;
	ft_bzero(ret, 3);
	ret[1] = power[num % 16];
	num = num / 16;
	ret[0] = power[num % 16];
	cr_vis_printattr(y, x, ret, colour, rev);
}

int		cr_vis_printattr(int y, int x, char *str, int colour, int reverse)
{
	if (colour)
		attron(COLOR_PAIR(colour));
	if (reverse)
		attron(A_REVERSE);
	// attron(A_BOLD);
	mvaddstr(y, x, str);
	// attroff(A_BOLD);
	if (colour)
		attroff(COLOR_PAIR(colour));
	if (reverse)
		attroff(A_REVERSE);
	return (0);
}

int		cr_vis_drawborder(void)
{
	int x;
	int y;

	y = -1;
	while (++y < V_H)
	{
		x = -1;
		while (++x < V_W)
		{
			if (x == 0 || x == 1 || y == 0 || x == V_W - 1 ||
			y == V_H - 1 || x == V_W - 2 || x == V_SEP + 2 ||
			x == V_SEP + 1)
				mvaddstr(y, x, V_BSYM);
		}
	}
	return (0);
}

int		cr_vis_getcolour(int i, t_corewar *cr)
{
	int			colour;
	t_player	*player;

	player = cr->p_player_obj;
	colour = i / (MEM_SIZE / cr->players_amount);
	if (cr->players_amount == 3 && i == MEM_SIZE - 1)
		return (0);
	while (colour-- && player->p_next)
		player = player->p_next;
	return ((i % (MEM_SIZE / cr->players_amount)) > player->code_size - 1 ? 0 : player->id);
}

int		cr_vis_printmap(unsigned char *f, int f_len, t_corewar *cr)
{
	int		i;

	i = 0;
	while (i < f_len)
	{
		cr_vis_putx(f[i], i, cr_vis_getcolour(i, cr), 0, cr);
		i += 1;
	}
	return (0);
}