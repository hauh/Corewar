/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:24:27 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 20:08:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_deadline(t_scheduler *p_scheduler_instance,
								t_corewar *p_game_obj)
{
	t_process	*iter;

	iter = p_scheduler_instance->p_processes_list;
	ITER = p_scheduler_instance->processes_amount;
	p_game_obj->p_arena_obj->check_amount += 1;
	p_game_obj->last_check_cycle = p_game_obj->p_arena_obj->cycle;
	while (ITER-- && iter && !(iter->p_owner->live_amount = 0))
	{
		if (p_game_obj->AR_CYCLE_TO_DIE_O <= (p_game_obj->AR_CYCLE_O -
		iter->last_speak_cycle) || p_game_obj->AR_CYCLE_TO_DIE_O <= 0)
		{
			p_scheduler_instance->cw_delete_process(p_scheduler_instance,
				&iter, p_game_obj->AR_CYCLE_O);
			iter && GA_VERBOSE_O == GA_SHOW_DEATH ? SC_TRACE : CW_FALSE;
		}
		else
			iter ? iter = iter->p_next : CW_FALSE;
	}
	if ((p_game_obj->AR_LIVE_AMOUNT_O >= NBR_LIVE ||
	p_game_obj->AR_CHECK_AMOUNT_O >= MAX_CHECKS) &&
	(p_game_obj->AR_CYCLE_TO_DIE_O -= CYCLE_DELTA) > -10000 &&
	!(p_game_obj->AR_CHECK_AMOUNT_O = 0))
		if (GA_VERBOSE_O == GA_SHOW_CYCLES)
			ft_printf("Cycle to die now %d\n", GA_ARENA_OBJ_O->cycle_to_die);
	p_game_obj->AR_LIVE_AMOUNT_O = 0;
}

static void		cw_ordinary_execution_processes(
			t_scheduler *p_scheduler_instance, t_corewar *p_game_obj, int cycle)
{
	t_process	*iter;
	t_iterator	i;
	t_mark		check_point;

	i = CW_ITERATOR;
	iter = p_scheduler_instance->p_processes_list;
	check_point = p_scheduler_instance->processes_amount;
	while (++i < check_point)
	{
		p_game_obj->p_working_process = iter;
		iter->cw_set_command_time(iter, p_game_obj);
		iter->cw_exec_command(iter, p_game_obj);
		iter = iter->p_next;
	}
	(void)cycle;
}

static void		cw_timeline_execution_processes(
			t_scheduler *p_scheduler_instance, t_corewar *p_game_obj, int cycle)
{
	p_scheduler_instance->pa_timeline[cycle]->
	cw_exec_processes(p_scheduler_instance->pa_timeline[cycle],
	p_scheduler_instance->pa_timeline[cycle]->p_root);
	p_scheduler_instance->pa_timeline[cycle]->p_root = NULL;
	(void)p_game_obj;
}

static void		cw_timeline_init(t_scheduler *p_scheduler_instance,
										t_corewar *p_game_obj)
{
	t_counter	iter;
	t_queue		*p_queue;

	iter = CW_ITERATOR;
	if (!(p_scheduler_instance->pa_timeline =
	(t_queue **)malloc(sizeof(t_queue *) * SC_MAX_CYCLE_SUPPORT)))
		cw_error_catcher(SC_OBJ_NAME, SC_TREE_ERROR, __FILE__, __LINE__);
	while (++iter < SC_MAX_CYCLE_SUPPORT)
	{
		cw_create_instance_queue(&p_queue);
		p_queue->p_game_obj = p_game_obj;
		p_scheduler_instance->pa_timeline[iter] = p_queue;
	}
}

extern void		cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance,
												t_corewar *p_game_obj)
{
	p_scheduler_instance->cw_timeline_init = cw_timeline_init;
	p_scheduler_instance->cw_deadline = cw_deadline;
	if (p_game_obj)
		if (GA_TREE_TIME_O || GA_LIST_TIME_O)
			p_scheduler_instance->cw_execution_processes =
				cw_timeline_execution_processes;
		else
			p_scheduler_instance->cw_execution_processes =
				cw_ordinary_execution_processes;
	else
		p_scheduler_instance->cw_execution_processes =
			cw_ordinary_execution_processes;
}
