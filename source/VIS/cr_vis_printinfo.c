/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:10:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/30 17:03:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_clearinfo()
{
	int y;
	char *x;

	x = ft_strnew(V_W - V_SEP);
	ft_memset(x, ' ', V_W - V_SEP - 5);
	y = 0;
	while (++y < V_H - 1)
	{
		mvprintw(y, V_SEP + 3 , x);
		mvaddstr(y, V_SEPSEP, V_BSYM);
		mvaddstr(y, V_SEPSEP + 1, V_BSYM);
	}
	ft_strdel(&x);
}

int		cr_vis_lastlive(t_corewar *cr, int id)
{
	t_carriage	*car;
	int			life;
	int			barrier;

	barrier = -1;
	life = 0;
	car = cr->p_carriage_obj;
	while (car->p_next && ++barrier < cr->carriages_amount)
	{
		if (car->p_owner->id == id && car->last_speak_cycle > life)
			life = car->last_speak_cycle;
		car = car->p_next;
	}
	return (cr->p_arena_obj->cycle_amount - life);
}

int		cr_vis_printplayers(t_corewar *cr)
{
	int			i;
	t_player	*p;

	i = 0;
	p = cr->p_player_obj;
	while (++i <= cr->players_amount)
	{
		mvprintw(p->id + i * 3 + 6, V_SEP + 6, "Player %d: ", p->id);
		attron(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 6, V_SEP + 17, "% 15s", p->p_name);
		attroff(COLOR_PAIR(p->id));
		mvprintw(p->id + i * 3 + 7, V_SEP + 12, "Last live: %d", cr_vis_lastlive(cr, p->id));
		mvprintw(p->id + i * 3 + 8, V_SEP + 12, "Some info", p->p_name);
		p = p->p_next;
	}
	return (0);
}

int		cr_vis_printhealth(t_corewar *cr)
{
	int y;
	int	step;
	int	id;
	int	life;

	id = 1;
	y = cr->players_amount * 4 + 18;
	while (id <= cr->players_amount)
	{
		step = 0;
		life = cr_vis_lastlive(cr, id);
		attron(COLOR_PAIR(id));
		mvprintw(y - 2, V_SEP + id * 10 - 2, "P%d", id);
		mvprintw(y, V_SEP + id * 10 - 2, "L%d", life);
		life = CYCLE_TO_DIE - life;
		while (life > 0)
		{
			if (life > 64)
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2, "%s%s", V_BSYM, V_BSYM);
			else if (life >= 32)
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2, "%s%s", V_BSYM, life >= 48 ? V_BHALF : V_BQUARTER);
			else
				mvprintw(y + 2 + step, V_SEP + id * 10 - 2, "%s", life >= 16 ? V_BHALF : V_BQUARTER);
			step += 1;
			life -= 64;
		}
		attroff(COLOR_PAIR(id));
		id += 1;
	}
	return (0);
}

int		cr_vis_printinfo(t_corewar *cr)
{
	cr_vis_clearinfo();
	if (cr->vis->carinfo)
		cr_vis_printcarinfo(cr);
	if (cr->vis->info)
	{
		attron(A_BOLD);
		mvprintw(2, V_SEP + 18, "<< %s >>", (cr->vis->flow || cr->vis->step) ? "running" : "paused");
		mvprintw(4, V_SEP + 12, "Cycles/second limit: %d", (CLOCKS_PER_SEC / (CLOCKS_PER_SEC / cr->vis->fpsdiv)));
		mvprintw(6, V_SEP + 18, " Cycle: %d", cr->p_arena_obj->cycle_amount);
		mvprintw(8, V_SEP + 18, "Processes: %d", cr->carriages_amount);
		cr_vis_printplayers(cr);
		mvprintw(cr->players_amount * 4 + 12, V_SEP + 6, "CYCLE_TO_DIE: %d   CYCLE_DELTA: %d", CYCLE_TO_DIE, CYCLE_DELTA);
		mvprintw(cr->players_amount * 4 + 14, V_SEP + 6, "NBR_LIVE: % 8d   MAX_CHECKS: % 3d", NBR_LIVE, MAX_CHECKS);
		cr_vis_printhealth(cr);
		attroff(A_BOLD);
	}
	return (0);
}