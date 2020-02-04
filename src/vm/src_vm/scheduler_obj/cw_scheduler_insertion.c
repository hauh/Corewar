/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_insertion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:46:34 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 20:09:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_insert_player(t_scheduler *p_scheduler_instance,
									t_player *p_adding_player)
{
	if (p_adding_player)
	{
		if (!p_scheduler_instance->p_players_list)
		{
			p_adding_player->p_next = p_adding_player;
			p_adding_player->p_prev = p_adding_player;
			p_scheduler_instance->p_players_list = p_adding_player;
		}
		else
		{
			p_adding_player->p_next = p_scheduler_instance->p_players_list;
			p_adding_player->p_prev =
				p_scheduler_instance->p_players_list->p_prev;
			p_scheduler_instance->p_players_list->p_prev->p_next =
				p_adding_player;
			p_scheduler_instance->p_players_list->p_prev = p_adding_player;
			p_scheduler_instance->p_players_list = p_adding_player;
		}
		p_scheduler_instance->players_amount += 1;
	}
}

static void		cw_insert_process_to_list(t_scheduler *p_scheduler_instance,
										t_process *p_adding_process, int stub)
{
	if (p_adding_process)
	{
		if (!p_scheduler_instance->p_processes_list)
		{
			p_scheduler_instance->p_processes_list = p_adding_process;
			p_adding_process->p_next = p_adding_process;
			p_adding_process->p_prev = p_adding_process;
		}
		else
		{
			p_adding_process->p_next = p_scheduler_instance->p_processes_list;
			p_adding_process->p_prev =
				p_scheduler_instance->p_processes_list->p_prev;
			p_scheduler_instance->p_processes_list->p_prev->p_next =
				p_adding_process;
			p_scheduler_instance->p_processes_list->p_prev = p_adding_process;
			p_scheduler_instance->p_processes_list = p_adding_process;
		}
		if (!p_scheduler_instance->avl_tree_timeline_on
			&& !p_scheduler_instance->list_timeline_on)
			p_scheduler_instance->processes_amount += 1;
		(void)stub;
	}
}

static void		cw_delete_process(t_scheduler *p_scheduler_instance,
							t_process **p_deleting_process, t_mark mode)
{
	t_process	*tmp;

	if (*p_deleting_process && (mode = 1))
	{
		(*p_deleting_process)->kill = CW_TRUE;
		if (*p_deleting_process == (*p_deleting_process)->p_next)
		{
			if (!SC_AVL_I && !SC_LIST_I)
				(*p_deleting_process)->cw_destructor(p_deleting_process);
			p_scheduler_instance->p_processes_list = NULL;
		}
		else
		{
			tmp = *p_deleting_process;
			if (*p_deleting_process == p_scheduler_instance->p_processes_list)
				SC_PROCESSES_LIST_I = (*p_deleting_process)->p_next;
			(*p_deleting_process)->p_prev->p_next =
				(*p_deleting_process)->p_next;
			(*p_deleting_process)->p_next->p_prev =
				(*p_deleting_process)->p_prev;
			*p_deleting_process = (*p_deleting_process)->p_next;
			!SC_AVL_I && !SC_LIST_I ? tmp->cw_destructor(&tmp) : CW_FALSE;
		}
		p_scheduler_instance->processes_amount -= 1;
	}
}

static void		cw_insert_process_to_avl_queue(
	t_scheduler *p_scheduler_instance, t_process *p_adding_process, int cycle)
{
	t_queue		*p_current_queue;

	p_current_queue = p_scheduler_instance->pa_timeline[cycle];
	p_current_queue->p_root = p_current_queue->cw_enqueue(p_current_queue,
		p_current_queue->p_root, p_adding_process);
	cw_insert_process_to_list(p_scheduler_instance, p_adding_process, cycle);
	p_scheduler_instance->processes_amount += 1;
}

extern void		cw_scheduler_insertion_linker(t_scheduler *p_scheduler_instance,
												t_corewar *p_game_ref)
{
	p_scheduler_instance->cw_insert_player = cw_insert_player;
	p_scheduler_instance->cw_delete_process = cw_delete_process;
	if (p_game_ref)
		if (p_game_ref->timeline_avl_tree_mode &&
		(p_scheduler_instance->avl_tree_timeline_on = CW_TRUE))
			p_scheduler_instance->cw_insert_process =
				cw_insert_process_to_avl_queue;
		else if (p_game_ref->timeline_list_mode &&
		(p_scheduler_instance->list_timeline_on = CW_TRUE))
		{
			ft_printf("Not supported feature yet, but soon\n");
			exit(1);
		}
		else
			p_scheduler_instance->cw_insert_process =
				cw_insert_process_to_list;
	else
		p_scheduler_instance->cw_insert_process = cw_insert_process_to_list;
}
