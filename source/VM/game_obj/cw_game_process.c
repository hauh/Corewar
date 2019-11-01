/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/01 18:38:33 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_merge_queue_to_list(t_corewar *p_game_instance)
{
	t_carriage	*p_tmp_carriage;
	int			iter;

	iter = 0;
	while (iter < p_game_instance->queue_size)
	{
		p_tmp_carriage = p_game_instance->p_waiting_queue->p_next;
		p_game_instance->cw_add_carriage_to_list(p_game_instance,
		p_game_instance->p_waiting_queue, 0);
		p_game_instance->carriages_amount += 1;
		p_game_instance->p_waiting_queue = p_tmp_carriage;
		++iter;
	}
	p_game_instance->p_waiting_queue = NULL;
	p_game_instance->queue_size = 0;
}

void		cw_push_to_queue(t_corewar *p_game_instance,
									t_carriage *p_adding_carriage)
{
	p_game_instance->queue_size += 1;
	if (!p_game_instance->p_waiting_queue)
	{
		p_game_instance->p_waiting_queue = p_adding_carriage;
		p_adding_carriage->p_next = p_adding_carriage;
		p_adding_carriage->p_prev = p_adding_carriage;
	}
	else
	{
		p_adding_carriage->p_next = p_game_instance->p_waiting_queue;
		p_adding_carriage->p_prev = p_game_instance->p_waiting_queue->p_prev;
		p_game_instance->p_waiting_queue->p_prev->p_next = p_adding_carriage;
		p_game_instance->p_waiting_queue->p_prev = p_adding_carriage;
	}
}

void		cw_delete_carriage(t_corewar *p_game_instance, int *p_del_car)
{
	t_carriage	*p_tmp_carrriage;

	p_tmp_carrriage = p_game_instance->p_carriage_obj;
	if (p_game_instance->p_carriage_obj)
	{
		if (p_game_instance->p_carriage_obj->p_next == p_game_instance->p_carriage_obj)
			p_game_instance->p_carriage_obj = NULL;
		else
		{
			p_game_instance->p_carriage_obj->p_prev->p_next	= p_game_instance->p_carriage_obj->p_next;
			p_game_instance->p_carriage_obj->p_next->p_prev	= p_game_instance->p_carriage_obj->p_prev;
			p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next;
			//p_tmp_carrriage->cw_destructor(&p_tmp_carrriage);
		}
	}
	*p_del_car += 1;
}

void		cw_main_checking(t_corewar *p_game_instance)
{
	t_carriage 	*tmp;
	int			deleted_count;
	int			iter;

	iter = CW_ITERATOR;
	deleted_count = 0;
	p_game_instance->p_arena_obj->check_amount += 1;
	p_game_instance->last_check_cycle = p_game_instance->p_arena_obj->cycle_amount;
	while (++iter < p_game_instance->carriages_amount && p_game_instance->p_carriage_obj)
	{
		p_game_instance->p_carriage_obj ? p_game_instance->p_carriage_obj->p_owner->live_amount = 0 : CW_FALSE;
		if (p_game_instance->p_arena_obj->cycle_to_die <= p_game_instance->p_arena_obj->cycle_amount - p_game_instance->p_carriage_obj->last_speak_cycle || p_game_instance->p_arena_obj->cycle_to_die <= 0)
			p_game_instance->cw_delete_carriage(p_game_instance, &deleted_count);
		else
			p_game_instance->p_carriage_obj ? p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next : CW_FALSE;
	}
	if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount >= MAX_CHECKS)
	{
		p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
		p_game_instance->p_arena_obj->check_amount = 0;
	}
	p_game_instance->carriages_amount -= deleted_count;
	p_game_instance->p_arena_obj->live_amount = 0;
}

void	cw_start_game(t_corewar *p_game_instance)
{
	int		iter;

	if (p_game_instance->visualizator == CW_TRUE)
		cr_vis_main(p_game_instance, V_INIT);
	while (p_game_instance->p_carriage_obj)
	{
		iter = CW_ITERATOR;
		if (p_game_instance->visualizator == CW_TRUE && p_game_instance->p_carriage_obj)
			cr_vis_main(p_game_instance, V_CONTROL);
		if (p_game_instance->visualizator == CW_TRUE && p_game_instance->vis->exit)
			p_game_instance->cw_destructor(&p_game_instance);
		else if (p_game_instance->visualizator == CW_FALSE || ((p_game_instance->vis->step || p_game_instance->vis->flow) && p_game_instance->vis->tick))
		{
			p_game_instance->p_arena_obj->cycle_amount += 1;
			while (++iter < p_game_instance->carriages_amount)
			{
				p_game_instance->p_carriage_obj->cw_set_command_time(p_game_instance->p_carriage_obj, p_game_instance->p_arena_obj);
				p_game_instance->p_carriage_obj->cw_reduce_time(p_game_instance->p_carriage_obj);
				p_game_instance->p_carriage_obj->cw_exec_command(p_game_instance->p_carriage_obj, p_game_instance);
				p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next;
			}
			//for (int i = 0; i < p_game_instance->carriages_amount; ++i, p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next)
			//	ft_printf("%#06x\n", p_game_instance->p_carriage_obj->current_location);
			if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
				p_game_instance->cw_main_checking(p_game_instance);
			p_game_instance->cw_merge_queue_to_list(p_game_instance);
			if (p_game_instance->load_dump == p_game_instance->p_arena_obj->cycle_amount)
				p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
			if (p_game_instance->visualizator == CW_TRUE && p_game_instance->p_carriage_obj)
				cr_vis_main(p_game_instance, V_UPDATE);
		}
	}
	if (p_game_instance->visualizator)
		cr_vis_winner(p_game_instance);
	else
		p_game_instance->cw_congratulations(p_game_instance);
}
