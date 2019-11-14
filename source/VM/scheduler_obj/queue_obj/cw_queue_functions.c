/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:10:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 19:57:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			cw_print_content(t_queue *p_queue_instance,
										t_process *p_root, int level)
{
	t_iter			i;

	if (p_root)
	{
		p_queue_instance->cw_print_content(p_queue_instance,
											p_root->p_left, level + 1);
		i = CW_ITERATOR;
		while (++i < level)
			ft_printf("   ");
		ft_printf("%d\n", p_root->id);
		p_queue_instance->cw_print_content(p_queue_instance,
											p_root->p_right, level + 1);
	}
}

static void			cw_exec_tree_processes(t_queue *p_queue_instance,
										t_process *p_process_obj)
{
	t_process		*p_left;
	t_process		*p_right;

	if (p_process_obj)
	{
		p_left = p_process_obj->p_left;
		p_right = p_process_obj->p_right;
		p_queue_instance->cw_exec_processes(p_queue_instance, p_right);
		if (!p_process_obj->kill)
		{
			p_queue_instance->GA_WORK_UNIT_O = p_process_obj;
			p_process_obj->cw_set_command_time(p_process_obj, QU_GAME_OBJ_I);
			p_process_obj->cw_exec_command(p_process_obj, QU_GAME_OBJ_I);
			p_queue_instance->GA_SCHEDULER_O->pa_timeline[p_process_obj->
			nearest_cycle]->p_root = p_queue_instance->GA_SCHEDULER_O->
			pa_timeline[p_process_obj->nearest_cycle]->
			cw_enqueue(p_queue_instance->GA_SCHEDULER_O->
			pa_timeline[p_process_obj->nearest_cycle],
			p_queue_instance->GA_SCHEDULER_O->
			pa_timeline[p_process_obj->nearest_cycle]->p_root, p_process_obj);
		}
		else
			p_process_obj->cw_destructor(&p_process_obj);
		p_queue_instance->cw_exec_processes(p_queue_instance, p_left);
	}
}

static t_process	*cw_enqueue(t_queue *p_queue_instance, t_process *p_node,
									t_process *p_process_obj)
{
	if (p_process_obj)
	{
		if (p_node)
		{
			if (p_process_obj->id < p_node->id)
				p_node->p_left = p_queue_instance->
				cw_enqueue(p_queue_instance, p_node->p_left, p_process_obj);
			else
				p_node->p_right = p_queue_instance->
				cw_enqueue(p_queue_instance, p_node->p_right, p_process_obj);
			return (p_queue_instance->cw_balance(p_queue_instance, p_node));
		}
		else
		{
			p_process_obj->p_right = NULL;
			p_process_obj->p_left = NULL;
			return (p_queue_instance->
			cw_balance(p_queue_instance, p_process_obj));
		}
	}
	return (NULL);
}

extern void			cw_queue_functions_linker(t_queue *p_queue_instance)
{
	p_queue_instance->cw_enqueue = cw_enqueue;
	p_queue_instance->cw_print_content = cw_print_content;
	p_queue_instance->cw_exec_processes = cw_exec_tree_processes;
}
