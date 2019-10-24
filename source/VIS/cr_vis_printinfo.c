/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:10:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/24 17:03:11 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_clearinfo()
{
	int y;

	y = 0;
	while (++y < 67)
		mvaddstr(y, 201,
		"                                                         ");
}

int		cr_vis_lastlive(corewar_t *cr, int id)
{
	carriage_t	*car;
	int			life;
	int			barrier;

	barrier = -1;
	life = 0;
	car = cr->pCarriageObj;
	while (car->pNext && ++barrier < cr->carriagesAmount)
	{
		if (car->pOwnerCarriage->id == id && car->lastSpeakCycle > life)
			life = car->lastSpeakCycle;
		car = car->pNext;
	}
	return (cr->pArenaObj->cycleAmount - life);
}

int		cr_vis_printplayers(corewar_t *cr)
{
	int			i;
	player_t	*p;

	i = 0;
	p = cr->pPlayerObj;
	while (++i <= cr->playersAmount)
	{
		mvprintw(p->id + i * 3 + 6, 208, "Player %d: ", p->id);
		attron(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 6, 219, "% 15s", p->pName);
		attroff(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 7, 214, "Last live: %d", cr_vis_lastlive(cr, p->id));
		mvprintw(p->id + i * 3 + 8, 214, "Some info", p->pName);
		p = p->pNext;
	}
	return (0);
}

int		cr_vis_printhealth(corewar_t *cr)
{
	int y;
	int	step;
	int	id;
	int	life;

	id = 1;
	y = cr->playersAmount * 4 + 18;
	while (id <= cr->playersAmount)
	{
		step = 0;
		life = cr_vis_lastlive(cr, id);
		attron(COLOR_PAIR(id));
		mvprintw(y - 2, 204 + id * 10, "P%d", id);
		mvprintw(y, 202 + id * 10, "L%d", life);
		life = CYCLE_TO_DIE - life;
		while (life > 0)
		{
			if (life > 64)
				mvprintw(y + 2 + step, 204 + id * 10, "%s%s", V_BSYM, V_BSYM);
			else if (life >= 32)
				mvprintw(y + 2 + step, 204 + id * 10, "%s%s", V_BSYM, life >= 48 ? V_BHALF : V_BQUARTER);
			else
				mvprintw(y + 2 + step, 204 + id * 10, "%s", life >= 16 ? V_BHALF : V_BQUARTER);
			step += 1;
			life -= 64;
		}
		attroff(COLOR_PAIR(id));
		id += 1;
	}
	return (0);
}

int		cr_vis_printinfo(corewar_t *cr)
{
	cr_vis_clearinfo();
	attron(A_BOLD);
	mvprintw(2, 224, "<< %s >>", (cr->vis->flow || cr->vis->step) ? "running" : "paused");
	mvprintw(4, 217, "Cycles/second limit: %d", (CLOCKS_PER_SEC / (CLOCKS_PER_SEC / cr->vis->fpsdiv)));
	mvprintw(6, 224, " Cycle: %d", cr->pArenaObj->cycleAmount);
	mvprintw(8, 224, "Processes: %d", cr->carriagesAmount);
	cr_vis_printplayers(cr);
	mvprintw(cr->playersAmount * 4 + 12, 212, "CYCLE_TO_DIE: %d   CYCLE_DELTA: %d", CYCLE_TO_DIE, CYCLE_DELTA);
	mvprintw(cr->playersAmount * 4 + 14, 212, "NBR_LIVE: % 8d   MAX_CHECKS: % 3d", NBR_LIVE, MAX_CHECKS);
	cr_vis_printhealth(cr);
	attroff(A_BOLD);
	return (0);
}
