/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_stack_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 13:56:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print_content(stackk_t *p_stack_instance)
{
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_stack_instance->size)
	{
		ft_printf("Player_name: %s\nPlayer_id: %d\nCarriage_id: %d\n",
		p_stack_instance->p_current_carriage->p_owner->p_name,
		p_stack_instance->p_current_carriage->p_owner->id,
		p_stack_instance->p_current_carriage->id);
		ft_printf("Carriage_registers: ");
		for (int i = 0 ; i < CW_REG_NUMBER * CW_REG_SIZE; ++i)
			ft_printf("%02x ", p_stack_instance->p_current_carriage->p_registers[i]);
		ft_printf("\n");
		++iter;
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_next;
	}
}

static void		cw_distribute_carriage(stackk_t *p_stack_instance, queue_t *p_waiting_queue, arena_t *p_arena_obj)
{
	carriage_t	*tmp;

	while(p_stack_instance->p_current_carriage && p_stack_instance->p_current_carriage->checked != p_arena_obj->cycle_amount)
	{
		p_stack_instance->p_current_carriage->cw_set_command_time(p_stack_instance->p_current_carriage, p_arena_obj);
		if (p_stack_instance->p_current_carriage->p_current_command && !p_stack_instance->p_current_carriage->error_ocurred)
		{
			p_stack_instance->cw_pop(p_stack_instance, &tmp);
			p_waiting_queue->cw_enqueue(p_waiting_queue, tmp);
			if (!p_stack_instance->min_carriage_waiting_time ||
				tmp->p_current_command->waiting_time < p_stack_instance->min_carriage_waiting_time)
				p_stack_instance->min_carriage_waiting_time = tmp->p_current_command->waiting_time;
		}
		else
			p_stack_instance->cw_rotate(p_stack_instance, p_arena_obj->cycle_amount);
	}
	if (p_stack_instance->p_current_carriage)
		p_stack_instance->current_waiting_time = 0;
}

static void		cw_peek(stackk_t *p_stack_instance, carriage_t **p_peeking_carriage)
{
	if (p_peeking_carriage)
		*p_peeking_carriage = p_stack_instance->p_current_carriage;
}

static void		cw_reverse_rotate(stackk_t *p_stack_instance)
{
	if (p_stack_instance->p_current_carriage)
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_prev;
}

static void		cw_rotate(stackk_t *p_stack_instance, int cycle_amount)
{
	if (p_stack_instance->p_current_carriage)
	{
		p_stack_instance->p_current_carriage->checked = cycle_amount;
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_next;
	}
}

static void 	cw_pop(stackk_t *p_stack_instance, carriage_t **p_deleting_carriage)
{
	carriage_t	*free_tmp;

	if (p_stack_instance->p_current_carriage)
	{
		free_tmp = p_stack_instance->p_current_carriage;
		p_stack_instance->p_current_carriage->p_next->p_prev = p_stack_instance->p_current_carriage->p_prev;
		p_stack_instance->p_current_carriage->p_prev->p_next = p_stack_instance->p_current_carriage->p_next;
		p_stack_instance->p_current_carriage = p_stack_instance->p_current_carriage->p_next;
		if (!p_deleting_carriage)
			free_tmp->cw_destructor(&free_tmp);
		else
			*p_deleting_carriage = free_tmp;
		p_stack_instance->size -= 1;
	}
}

static void		cw_push(stackk_t *p_stack_instance, carriage_t *p_adding_carriage)
{
	if (p_adding_carriage)
	{
		if (!p_stack_instance->p_current_carriage)
		{
			p_stack_instance->p_current_carriage = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_next = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_prev = p_adding_carriage;
		}
		else
		{
			p_adding_carriage->p_next = p_stack_instance->p_current_carriage;
			p_adding_carriage->p_prev = p_stack_instance->p_current_carriage->p_prev;
			p_stack_instance->p_current_carriage->p_prev->p_next = p_adding_carriage;
			p_stack_instance->p_current_carriage->p_prev = p_adding_carriage;
			p_stack_instance->p_current_carriage = p_adding_carriage;
		}
		p_stack_instance->size += 1;
	}
}

static void		cw_constructor(stackk_t	**pp_stack_instance)
{
	(*pp_stack_instance)->p_current_carriage = NULL;
	(*pp_stack_instance)->max_carriage_number = 0;
	(*pp_stack_instance)->min_carriage_waiting_time = 0;
	(*pp_stack_instance)->current_waiting_time = 1;
}

static void		cw_destructor(stackk_t **pp_stack_instance)
{
	free(*pp_stack_instance);
	*pp_stack_instance = NULL;
}

extern void		cw_create_instance_stack(stackk_t **pp_stack_obj)
{
	if (!(*pp_stack_obj = (stackk_t *)malloc(sizeof(stackk_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, "Qeueue has not been created");
	(*pp_stack_obj)->cw_constructor = cw_constructor;
	(*pp_stack_obj)->cw_destructor = cw_destructor;
	(*pp_stack_obj)->cw_push = cw_push;
	(*pp_stack_obj)->cw_print_content = cw_print_content;
	(*pp_stack_obj)->cw_peek = cw_peek;
	(*pp_stack_obj)->cw_pop = cw_pop;
	(*pp_stack_obj)->cw_rotate = cw_rotate;
	(*pp_stack_obj)->cw_reverse_rotate = cw_reverse_rotate;
	(*pp_stack_obj)->cw_constructor(pp_stack_obj);
}