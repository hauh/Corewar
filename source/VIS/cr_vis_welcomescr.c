/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_welcomescr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:44:55 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/14 14:27:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cr_vis_clearscreen()
{
	int		y;
	char	*x;

	x = ft_strnew(V_W);
	ft_memset(x, ' ', V_W);
	y = -1;
	while (++y < V_H)
		mvprintw(y, 0, x);
	ft_strdel(&x);
}

void	cr_vis_winner(t_corewar *cr)
{
	cr_vis_clearscreen();
	attron(A_BOLD);
	mvprintw(V_H / 2, V_W / 2, "Contestant %d, \"%s\", has won !\n",
	cr->p_arena_obj->p_winner->id,
	cr->p_arena_obj->p_winner->p_name);
	mvprintw(V_H / 2 + 1, V_W / 2, "(Press 's' to exit)");
	attroff(A_BOLD);
	while (getch() != 's')
		;
}

void	cr_vis_welcome(t_corewar *cr)
{
	int				iter;

	iter = CW_BEGIN_FROM_ZERO;
	attron(A_BOLD);
	mvprintw(V_H / 2, V_W / 2, "Introducing contestants...\n");
	while (iter < cr->p_scheduler->players_amount)
	{
		cr->p_scheduler->p_processes_list = cr->p_scheduler->p_processes_list->p_prev;
		mvprintw(V_H / 2 + iter, V_W / 2,
		"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		cr->p_scheduler->p_processes_list->p_owner->id,
		cr->p_scheduler->p_processes_list->p_owner->code_size,
		cr->p_scheduler->p_processes_list->p_owner->p_name,
		cr->p_scheduler->p_processes_list->p_owner->p_comment);
		++iter;
	}
	mvprintw(V_H / 2 + iter, V_W / 2, "(Press 's' to continue)");
	attroff(A_BOLD);
	refresh();
	while (getch() != 's')
		;
	cr_vis_clearscreen();
}
