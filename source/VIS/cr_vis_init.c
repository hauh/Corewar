/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:44:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/28 16:43:11 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_initvis(corewar_t *cr)
{
	t_vis *tmp;

	tmp = (t_vis *)malloc(sizeof(t_vis));
	ft_bzero(tmp, sizeof(t_vis));
	tmp->flow = 0;
	cr_vis_initterm();
	cr_vis_initcolour();
	tmp->field = (unsigned char *)malloc(MEM_SIZE);
	ft_memmove(tmp->field, cr->p_arena_obj->p_field, MEM_SIZE);
	tmp->fpsdiv = 420;
	cr->vis = tmp;
	cr_vis_drawborder();
	cr_vis_printmap(cr->p_arena_obj->p_field, MEM_SIZE, cr);
	refresh();
	return (0);
}

int		cr_vis_initcolour(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	return (0);
}

int		cr_vis_initterm(void)
{
	// system("printf '\033[8;68;260t'");
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	return (0);
}