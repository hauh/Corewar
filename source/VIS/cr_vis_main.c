/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/30 16:22:23 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_cleanup(corewar_t *cr)
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

int		cr_vis_main(corewar_t *cr, int action)
{
	if (action == V_INIT)
		cr_vis_initvis(cr);
	else if (action == V_CONTROL)
	{
		cr_vis_timer(cr);
		cr_vis_keys(cr);
	}
	else if (action == V_UPDATE && cr->p_arena_obj->cycle_amount >= cr->vis->startfrom)
	{
		cr_vis_updatemap(cr);
		cr->vis->step = 0;
		cr->vis->tick = 0;
	}
	if (cr->vis && cr->p_arena_obj->cycle_amount >= cr->vis->startfrom)
	{
		cr_vis_printinfo(cr);
		refresh();
	}
	if (action == V_CLEANUP)
		cr_vis_cleanup(cr);
	return (0);
}