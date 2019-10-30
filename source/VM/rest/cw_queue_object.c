/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:13:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 14:53:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_get_value(t_queue *p_queue_instance, int index)
{
	t_carriage	*iter;
	int			tmp;

	iter = p_queue_instance->p_current_carriage;
	if (iter)
	{
		while (index--)
			iter = iter->p_next;
		tmp = iter->id;
		return (tmp);
	}
	return (0);
}

static void		cw_print_content(t_queue *p_queue_instance)
{
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_queue_instance->size)
	{
		ft_printf("Player_name: %s\nPlayer_id: %d\nCarriage_id: %d\n",
		p_queue_instance->p_current_carriage->p_owner->p_name,
		p_queue_instance->p_current_carriage->p_owner->id,
		p_queue_instance->p_current_carriage->id);
		ft_printf("Carriage_registers: ");
		for (int i = 0 ; i < CW_REG_NUMBER * CW_REG_SIZE; ++i)
			ft_printf("%02x ", p_queue_instance->p_current_carriage->p_registers[i]);
		ft_printf("\n");
		++iter;
		p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
	}
}

static void		cw_peek(t_queue *p_queue_instance, t_carriage **p_peeking_carriage)
{
	if (p_peeking_carriage)
		*p_peeking_carriage = p_queue_instance->p_current_carriage;
}

static void		cw_dequeue(t_queue *p_queue_instance, t_carriage **p_deleting_carriage)
{
	t_carriage *free_tmp;

	if (p_queue_instance->p_current_carriage)
	{
		free_tmp = p_queue_instance->p_current_carriage;
		p_queue_instance->p_current_carriage->p_next->p_prev = p_queue_instance->p_current_carriage->p_prev;
		p_queue_instance->p_current_carriage->p_prev->p_next = p_queue_instance->p_current_carriage->p_next;
		if (p_queue_instance->p_current_carriage == p_queue_instance->p_current_carriage->p_next)
			p_queue_instance->p_current_carriage = NULL;
		else
			p_queue_instance->p_current_carriage = p_queue_instance->p_current_carriage->p_next;
		if (!p_deleting_carriage)
			free_tmp->cw_destructor(&free_tmp);
		else
			*p_deleting_carriage = free_tmp;
		p_queue_instance->size -= 1;
	}
}

static void		cw_enqueue(t_queue *p_queue_instance, t_carriage *p_adding_carraige)
{
	if (p_adding_carraige)
	{
		if (!p_queue_instance->p_current_carriage)
		{
			p_queue_instance->p_current_carriage = p_adding_carraige;
			p_queue_instance->p_current_carriage->p_next = p_adding_carraige;
			p_queue_instance->p_current_carriage->p_prev = p_adding_carraige;
		}
		else
		{
			p_adding_carraige->p_next = p_queue_instance->p_current_carriage;
			p_adding_carraige->p_prev = p_queue_instance->p_current_carriage->p_prev;
			p_queue_instance->p_current_carriage->p_prev->p_next = p_adding_carraige;
			p_queue_instance->p_current_carriage->p_prev = p_adding_carraige;
		}
		p_queue_instance->size += 1;
	}
}

static void		cw_constructor(t_queue **pp_queue_instance)
{
	(*pp_queue_instance)->p_current_carriage = NULL;
	(*pp_queue_instance)->size = 0;
}

static void		cw_destructor(t_queue **pp_queue_instance)
{
	free(*pp_queue_instance);
	*pp_queue_instance = NULL;
}

extern void		cw_create_instance_queue(t_queue **pp_queue_obj)
{
	if (!(*pp_queue_obj = (t_queue *)malloc(sizeof(t_queue))))
		cw_error_catcher(CW_NOT_ALLOCATED, "Queue object has not been created");
	(*pp_queue_obj)->cw_constructor = cw_constructor;
	(*pp_queue_obj)->cw_destructor = cw_destructor;
	(*pp_queue_obj)->cw_enqueue = cw_enqueue;
	(*pp_queue_obj)->cw_dequeue = cw_dequeue;
	(*pp_queue_obj)->cw_peek = cw_peek;
	(*pp_queue_obj)->cw_print_content = cw_print_content;
	(*pp_queue_obj)->cw_constructor(pp_queue_obj);
}