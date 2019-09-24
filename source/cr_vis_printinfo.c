/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:10:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/24 18:06:18 by vrichese         ###   ########.fr       */
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

int		cr_vis_printplayers(corewar_t *cr)
{
	int			i;
	int			y;
	player_t	*p;

	y = cr->players_amount * 3;
	i = cr->players_amount;
	p = cr->players;
	while (i--)
	{
		y -= 3;
		mvprintw(p->id + y + 9, 208, "Player %d: ", p->id);
		attron(COLOR_PAIR(p->id));
		mvprintw(p->id + y + 9, 219, "% 15s", p->name);
		attroff(COLOR_PAIR(p->id));
		mvprintw(p->id + y + 10, 214, "Some info", p->name);
		mvprintw(p->id + y + 11, 214, "Some info", p->name);
		p = p->next;
	}
	return (0);
}

int		cr_vis_printinfo(corewar_t *cr)
{
	cr_vis_clearinfo();
	attron(A_BOLD);
	mvprintw(2, 224, "<< %s >>", (cr->vis->flow || cr->vis->step) ? "running" : "paused");
	mvprintw(4, 217, "Cycles/second limit: %d", (CLOCKS_PER_SEC / (CLOCKS_PER_SEC / cr->vis->fpsdiv)));
	mvprintw(6, 224, " Cycle: %d", cr->arena->cycle_amount);
	mvprintw(8, 224, "Processes: %d", cr->carriages_amount);
	mvprintw(cr->players_amount * 3 + 12, 212, "CYCLE_TO_DIE: %d   CYCLE_DELTA: %d", CYCLE_TO_DIE, CYCLE_DELTA);
	mvprintw(cr->players_amount * 3 + 14, 212, "NBR_LIVE: % 8d   MAX_CHECKS: % 3d", NBR_LIVE, MAX_CHECKS);
	cr_vis_printplayers(cr);
	attroff(A_BOLD);
	return (0);
}