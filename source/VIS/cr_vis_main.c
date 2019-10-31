/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/31 17:30:22 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_cleanup(t_corewar *cr)
{
	endwin();
	if (cr)
	{
		if (cr->vis)
		{
			if (cr->vis->field)
				free(cr->vis->field);
			free(cr->vis);
		}
		cr->vis = NULL;
	}
	return (0);
}

int		cr_vis_main(t_corewar *cr, int action)
{
	if (action == V_INIT && cr->p_carriage_obj)
		cr_vis_initvis(cr);
	else if (action == V_CONTROL && cr->p_carriage_obj)
	{
		cr_vis_timer(cr);
		cr_vis_keys(cr);
	}
	else if (action == V_UPDATE && cr->p_arena_obj->cycle_amount >= cr->visual_cycle && cr->p_carriage_obj)
	{
		cr_vis_updatemap(cr);
		cr->vis->step = 0;
		cr->vis->tick = 0;
	}
	if (cr->vis && cr->p_arena_obj->cycle_amount >= cr->visual_cycle && cr->p_carriage_obj)
	{
		cr_vis_printinfo(cr);
		refresh();
	}
	if (action == V_CLEANUP)
		cr_vis_cleanup(cr);
	return (0);
}