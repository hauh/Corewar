/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printhealth.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:15:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/04 16:19:13 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_healthmeter(int life, int id, int y)
{
	int step;

	step = 0;
	while (life > 0)
	{
		if (life > 64)
			mvprintw(y + 2 + step, V_SEP + id * 10 - 2, "%s%s", V_BSYM, V_BSYM);
		else if (life >= 32)
			mvprintw(y + 2 + step, V_SEP + id * 10 - 2,
			"%s%s", V_BSYM, life >= 48 ? V_BHALF : V_BQUARTER);
		else
			mvprintw(y + 2 + step, V_SEP + id * 10 - 2,
			"%s", life >= 16 ? V_BHALF : V_BQUARTER);
		step += 1;
		life -= 64;
	}
}

int		cr_vis_printhealth(t_corewar *cr)
{
	int y;
	int	id;
	int	life;

	id = 1;
	y = cr->players_amount * 4 + 18;
	while (id <= cr->players_amount)
	{
		life = cr_vis_lastlive(cr, id);
		attron(COLOR_PAIR(id));
		mvprintw(y - 2, V_SEP + id * 10 - 2, "P%d", id);
		mvprintw(y, V_SEP + id * 10 - 2, "L%d", life);
		life = cr->p_arena_obj->cycle_to_die - life;
		cr_vis_healthmeter(life, id, y);
		attroff(COLOR_PAIR(id));
		id += 1;
	}
	return (0);
}
