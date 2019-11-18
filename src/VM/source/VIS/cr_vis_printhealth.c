/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printhealth.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:15:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/18 19:30:12 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			cr_vis_printdeath(int ctd, int mini, int amount)
{
	int		y;
	int		x;
	int		count;
	char	*str;

	str = " death ";
	count = 0;
	y = V_H - 2;
	mini ? ctd = ctd + 64 * (5 - ((amount - 1) * 2)) : 0;
	attron(COLOR_PAIR(4));
	attroff(A_BOLD);
	while (ctd > 0)
	{
		x = V_SEP + 3;
		while (x < V_SEPSEP)
		{
			mvaddch(y, x, str[count % 6]);
			count += 1;
			x += 1;
		}
		y -= 1;
		ctd -= mini ? 64 : 32;
	}
	attroff(COLOR_PAIR(4));
	attron(A_BOLD);
}

static void			cr_vis_healthmeter(int life, int id, int y, int ctd)
{
	int step;

	step = 0;
	if (life < ctd)
	{
		while (life > 0)
		{
			if (life > 32)
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2,
				"%s%s", V_BSYM, V_BSYM);
			else if (life >= 12)
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2,
				"%s%s", V_BSYM, life >= 24 ? V_BHALF : V_BQUARTER);
			else
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2,
				"%s", life >= 8 ? V_BHALF : V_BQUARTER);
			step += 1;
			life -= 32;
		}
	}
}

int					cr_vis_printhealth(t_corewar *cr)
{
	int y;
	int	id;
	int	life;

	id = 1;
	y = cr->p_scheduler->players_amount * 4 + 18;
	cr_vis_printdeath(
		(CYCLE_TO_DIE - cr->p_arena_obj->cycle_to_die +
		32 * (30 - cr->p_scheduler->players_amount * 4)),
		cr->mini, cr->p_scheduler->players_amount);
	while (id <= cr->p_scheduler->players_amount)
	{
		life = cr_vis_lastlive(cr, id);
		attron(COLOR_PAIR(id));
		mvprintw(y - 2, V_SEP + id * 10 - 2, "P%d", id);
		if (life < cr->p_arena_obj->cycle_to_die)
			mvprintw(y, V_SEP + id * 10 - 2, "L%d", life);
		else
			mvprintw(y, V_SEP + id * 10 - 2, "X_X");
		cr_vis_healthmeter(
			cr->mini ? life / 2 : life, id, y, cr->p_arena_obj->cycle_to_die);
		attroff(COLOR_PAIR(id));
		id += 1;
	}
	return (0);
}
