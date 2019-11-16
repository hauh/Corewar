/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:10:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/15 17:55:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_clearinfo(t_corewar *cr)
{
	if (cr->vis->carinfo != -1 || cr->vis->info != -1)
	{
		cr_vis_clearbox(V_MID, cr->mini);
		cr_vis_clearbox(V_RIGHT, cr->mini);
	}
	if (!cr->vis->carinfo && !cr->vis->info)
	{
		cr->vis->carinfo = -1;
		cr->vis->info = -1;
	}
}

int		cr_vis_lastlive(t_corewar *cr, int id)
{
	t_process	*car;
	int			life;
	int			barrier;

	barrier = -1;
	life = 0;
	car = cr->p_scheduler->p_processes_list;
	while (car->p_next && ++barrier < cr->p_scheduler->processes_amount)
	{
		if (car->p_owner->id == id && car->last_speak_cycle > life)
			life = car->last_speak_cycle;
		car = car->p_next;
	}
	return (cr->p_arena_obj->cycle - life);
}

int		cr_vis_printplayers(t_corewar *cr)
{
	int			i;
	t_player	*p;

	i = 0;
	p = cr->p_scheduler->p_players_list;
	while (++i <= cr->p_scheduler->players_amount)
	{
		mvprintw(p->id + i * 3 + 6, V_SEP + 6, "Player %d: ", p->id);
		attron(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 6, V_SEP + 17, "%.42s", p->p_name);
		attroff(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 7, V_SEP + 12,
		"Last live: %d", cr_vis_lastlive(cr, p->id));
		mvprintw(p->id + i * 3 + 8, V_SEP + 12, "Some info", p->p_name);
		p = p->p_next;
	}
	return (0);
}

int		cr_vis_printinfo(t_corewar *cr)
{
	cr_vis_clearinfo(cr);
	if (!cr->mini && cr->vis->carinfo == 1)
		cr_vis_printcarinfo(cr);
	if (cr->vis->info == 1)
	{
		cr_vis_buildbox(V_MID);
		attron(A_BOLD);
		mvprintw(2, V_SEP + 18,
		"<< %s >>", (cr->vis->flow || cr->vis->step) ? "running" : "paused");
		mvprintw(4, V_SEP + 12, "Cycles/second limit: %d",
		(CLOCKS_PER_SEC / (CLOCKS_PER_SEC / cr->vis->fpsdiv)));
		mvprintw(6, V_SEP + 18, " Cycle: %d", cr->p_arena_obj->cycle);
		mvprintw(8, V_SEP + 18, "Processes: %d",
		cr->p_scheduler->processes_amount);
		cr_vis_printplayers(cr);
		mvprintw(cr->p_scheduler->players_amount * 4 + 12, V_SEP + 6,
		"CYCLE_TO_DIE: %d   CYCLE_DELTA: %d", CYCLE_TO_DIE, CYCLE_DELTA);
		mvprintw(cr->p_scheduler->players_amount * 4 + 14, V_SEP + 6,
		"NBR_LIVE: % 8d   MAX_CHECKS: % 3d", NBR_LIVE, MAX_CHECKS);
		cr_vis_printhealth(cr);
		attroff(A_BOLD);
	}
	return (0);
}
