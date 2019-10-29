/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_printcar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:15:43 by dbrady            #+#    #+#             */
/*   Updated: 2019/10/29 17:47:36 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static carriage_t		*cr_vis_getcarp(corewar_t *cr, int place)
{
	carriage_t *car;

	car = cr->p_carriage_obj;
	while (car->id != 1 && place)
	{
		car = car->p_next;
		place -= 1;
	}
	return (car);
}

static void				cr_vis_printreg(unsigned char *reg, int y)
{
	int i;

	i = 0;
	while (i < CW_REG_SIZE * CW_REG_NUMBER)
	{
		if (i == 32)
			y += 1;
		mvprintw(y, V_SEPSEP + 9 + (i % 32) * 4, "% -4d", reg[i]);
		i += 1;
	}
}

void					cr_vis_printcarinfo(corewar_t *cr)
{
	carriage_t *car;
	int y;

	y = 3;
	
	car = cr_vis_getcarp(cr, cr->vis->car_place);
	attron(A_BOLD);
	mvprintw(2, V_SEPSEP + 9, "currently viewing carriages %d through %d   ...   place: %d | car_id: %d | amount: %d | reg_len: %d | carvol: %d",
	car->id, cr_vis_getcarp(cr, cr->vis->car_place + (V_CARVOL - 1))->id, cr->vis->car_place, car->id, cr->carriages_amount, CW_REG_SIZE * CW_REG_NUMBER, V_CARVOL);
	while (y / 3 - 1 < V_CARVOL)
	{
		attron(A_BOLD);
		mvprintw(y, V_SEPSEP + 9, "id: % 6d | own: % 6d | car: % 6d | do: % 6d "
		"| sp: % 6d | wt: % 6d | ad: % 6d | lsc: % 6d | asp: % 6d | cl: % 6d "
		"| cr: % 6d | eo: % 6d | fa: % 6d | sa: % 6d | ta: % 6d | off: % 6d ",
		car->id, car->p_owner->id,
		car->carry, car->odometer, car->save_point, car->waiting_time,
		car->addit_odometer, car->last_speak_cycle, car->addit_save_point,
		car->current_location, car->current_register, car->error_ocurred,
		car->first_arg, car->second_arg, car->third_arg, car->offset);
		attroff(A_BOLD);
		cr_vis_printreg(car->p_registers, y + 1);
		if (car->id == 1)
			break ;
		car = car->p_next;
		y += 3;
	}
}