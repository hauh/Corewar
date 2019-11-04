/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_buildmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/04 13:45:26 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cr_vis_putx(int num, int i, int colour, int rev)
{
	char	ret[3];
	char	power[16];
	int		xy[2];

	ft_memmove(power, "0123456789abcdef", 16);
	xy[0] = (i * 3) % (V_SEP - 8) + 5;
	xy[1] = (i * 3) / (V_SEP - 8) + 2;
	ft_bzero(ret, 3);
	ret[1] = power[num % 16];
	num = num / 16;
	ret[0] = power[num % 16];
	cr_vis_printattr(xy, ret, colour, rev);
}

int			cr_vis_printattr(int *xy, char *str, int colour, int reverse)
{
	if (colour)
		attron(COLOR_PAIR(colour));
	if (reverse)
		attron(A_REVERSE);
	mvaddstr(xy[1], xy[0], str);
	if (colour)
		attroff(COLOR_PAIR(colour));
	if (reverse)
		attroff(A_REVERSE);
	return (0);
}

int			cr_vis_getcolour(int i, t_corewar *cr)
{
	int			colour;
	t_player	*player;

	player = cr->p_player_obj;
	colour = i / (MEM_SIZE / cr->players_amount);
	if (cr->players_amount == 3 && i == MEM_SIZE - 1)
		return (0);
	while (colour-- && player->p_next)
		player = player->p_next;
	return ((i % (MEM_SIZE / cr->players_amount)) > player->code_size - 1 ?
	0 : player->id);
}

int			cr_vis_printmap(unsigned char *f, int f_len, t_corewar *cr)
{
	int		i;

	i = 0;
	cr_vis_buildbox(V_LEFT);
	while (i < f_len)
	{
		cr_vis_putx(f[i], i, cr_vis_getcolour(i, cr), 0);
		i += 1;
	}
	return (0);
}
