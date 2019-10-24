/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/24 17:03:31 by dbrady           ###   ########.fr       */
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
	else if (action == V_UPDATE)
	{
		cr_vis_printinfo(cr);
		cr_vis_updatemap(cr);
		refresh();
		cr->vis->step = 0;
		cr->vis->tick = 0;
	}
	else if (action == V_CLEANUP)
		cr_vis_cleanup(cr);
	return (0);
}