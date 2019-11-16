/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_welcomescr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:44:55 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/16 13:37:53 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cr_vis_clearscreen(void)
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

static void		cr_vis_welcome_printknight(int vh, int vw)
{
	mvaddstr(vh - 29, vw, "                 _A_");
	mvaddstr(vh - 28, vw, "                / | \\");
	mvaddstr(vh - 27, vw, "               |.-=-.|");
	mvaddstr(vh - 26, vw, "               )\\_|_/(");
	mvaddstr(vh - 25, vw, "            .=='\\   /`==.");
	mvaddstr(vh - 24, vw, "          .'\\   (`:')   /`.");
	mvaddstr(vh - 23, vw, "        _/_ |_.-' : `-._|__\\_");
	mvaddstr(vh - 22, vw, "       <___>'\\    :   / `<___>");
	mvaddstr(vh - 21, vw, "       /  /   >=======<  /  /");
	mvaddstr(vh - 20, vw, "     _/ .'   /  ,-:-.  \\/=,'");
	mvaddstr(vh - 19, vw, "    / _/    |__/v^v^v\\__) \\");
	mvaddstr(vh - 18, vw, "    \\(\\)     |V^V^V^V^V|\\_/");
	mvaddstr(vh - 17, vw, "     (\\\\     \\`---|---'/");
	mvaddstr(vh - 16, vw, "       \\\\     \\-._|_,-/");
	mvaddstr(vh - 15, vw, "        \\\\     |__|__|");
	mvaddstr(vh - 14, vw, "         \\\\   <___X___>");
	mvaddstr(vh - 13, vw, "          \\\\   \\..|../");
	mvaddstr(vh - 12, vw, "           \\\\   \\ | /");
	mvaddstr(vh - 11, vw, "            \\\\  /V|V\\");
	mvaddstr(vh - 10, vw, "             \\|/  |  \\");
	mvaddstr(vh - 9, vw, "              '--' `--`");
}

static void		cr_vis_welcome_printplayer(int i, t_corewar *cr)
{
	attron(COLOR_PAIR(cr->p_scheduler->p_processes_list->p_owner->id));
	mvprintw(V_H / 2 + i, V_W / 2 - 21,
	"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
	cr->p_scheduler->p_processes_list->p_owner->id,
	cr->p_scheduler->p_processes_list->p_owner->code_size,
	cr->p_scheduler->p_processes_list->p_owner->p_name,
	cr->p_scheduler->p_processes_list->p_owner->p_comment);
	cr_vis_welcome_printknight
(V_H / 2 + (i % 2 * 39), V_W / 2 - 24 + ((i == 2 || i == 3) ? 35 : 0));
	attroff(COLOR_PAIR(cr->p_scheduler->p_processes_list->p_owner->id));
}

void			cr_vis_winner(t_corewar *cr)
{
	cr_vis_clearscreen();
	attron(A_BOLD);
	attron(COLOR_PAIR(cr->p_arena_obj->p_winner->id));
	cr_vis_welcome_printknight(V_H / 2 + 7, V_W / 2 - 8);
	mvprintw(V_H / 2, V_W / 2 - 6, "Contestant %d, \"%s\", has won !\n",
	cr->p_arena_obj->p_winner->id,
	cr->p_arena_obj->p_winner->p_name);
	attroff(COLOR_PAIR(cr->p_arena_obj->p_winner->id));
	mvprintw(V_H / 2 + 1, V_W / 2, "(Press 's' to exit)");
	attroff(A_BOLD);
	while (getch() != 's')
		;
}

void			cr_vis_welcome(t_corewar *cr)
{
	int				iter;

	iter = CW_BEGIN_FROM_ZERO;
	attron(A_BOLD);
	mvprintw(V_H / 2 - 1, V_W / 2, "Introducing contestants...\n");
	while (iter < cr->p_scheduler->players_amount)
	{
		cr->p_scheduler->p_processes_list =
		cr->p_scheduler->p_processes_list->p_prev;
		cr_vis_welcome_printplayer(iter, cr);
		iter += 1;
	}
	mvprintw(V_H / 2 + iter, V_W / 2, "(Press 's' to continue)");
	attroff(A_BOLD);
	refresh();
	while (getch() != 's')
		;
	cr_vis_clearscreen();
}
