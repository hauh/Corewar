/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printcar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:15:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/11/15 17:25:02 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_process		*cr_vis_getcarp(t_corewar *cr, int place)
{
	t_process *car;

	car = cr->p_scheduler->p_processes_list;
	while (car->id != 1 && place)
	{
		if (car->p_next == cr->p_scheduler->p_processes_list)
			return (car);
		car = car->p_next;
		place -= 1;
	}
	return (car);
}

static void				cr_vis_printreg(unsigned char *reg, int y)
{
	int i;

	i = 0;
	while (i < CW_REG_SIZE * CW_REG_NUM)
	{
		if (i == 32)
			y += 1;
		mvprintw(y, V_SEPSEP + 9 + (i % 32) * 4, "% -2x", reg[i]);
		i += 1;
	}
}

static void				cr_vis_bbmvprintw(t_process *car, int y)
{
	int			xy[2];
	char		owner[2];

	mvprintw(y, V_SEPSEP + 9, "id: % 6d | own: % 6d | car: % 6d | do: % 6d"
" | sp: % 6d | wt: % 6d | ad: % 6d | lsc: % 6d | asp: % 6d | cl: % 6d | cr:"
" % 6d | eo: % 6d | args: % 6d | off: % 6d ",
car->id, car->p_owner->id, car->carry, car->odometer, car->save_point,
car->waiting_time, car->addit_odometer, car->last_speak_cycle,
car->addit_save_point, car->current_location, car->current_register,
car->error_ocurred, car->args, car->offset);
	xy[1] = y;
	xy[0] = V_SEPSEP + 32;
	owner[0] = car->p_owner->id + '0';
	owner[1] = 0;
	cr_vis_printattr(xy, owner, car->p_owner->id, 0);
}

void					cr_vis_printcarinfo(t_corewar *cr)
{
	t_process	*car;
	int			y;

	cr_vis_buildbox(V_RIGHT);
	y = 3;
	car = cr_vis_getcarp(cr, cr->vis->car_place);
	attron(A_BOLD);
	mvprintw(2, V_SEPSEP + 9, "currently viewing carriages %d through %d",
car->id, cr_vis_getcarp(cr, cr->vis->car_place + (V_CARVOL - 1))->id,
cr->vis->car_place);
	while (y / 3 - 1 < V_CARVOL)
	{
		attron(A_BOLD);
		cr_vis_bbmvprintw(car, y + 1);
		attroff(A_BOLD);
		cr_vis_printreg(car->p_registers, y + 2);
		if (car->p_next == cr->p_scheduler->p_processes_list)
			break ;
		car = car->p_next;
		y += 3;
	}
}
