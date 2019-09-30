/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/24 16:44:29 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_cleanup(corewar_t *cr)
{
	free(cr->vis->field);
	free(cr->vis);
	cr->vis = NULL;
	endwin();
	return (0);
}

int		cr_vis_main(corewar_t *cr, int action)
{
	if (action == V_INIT)
		cr_vis_initvis(cr);
	else if (action == V_CONTROL)
	{
		cr_vis_timer(cr->vis);
		cr_vis_keys(cr->vis);
	}
	else if (action == V_UPDATE)
	{
		cr_vis_updatemap(cr);
		cr->vis->step = 0;
		cr->vis->tick = 0;
	}
	else if (action == V_INFO)
		cr_vis_printinfo(cr);
	else if (action == V_CLEANUP)
		cr_vis_cleanup(cr);
	refresh();
	return (0);
}