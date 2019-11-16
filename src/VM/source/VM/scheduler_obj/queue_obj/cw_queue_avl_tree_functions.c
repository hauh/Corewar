/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_avl_tree_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:20:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 20:09:52 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_process	*cw_rotate(t_queue *p_queue_instance,
									t_process *p_process_obj, t_mark side)
{
	t_process		*p_left;
	t_process		*p_right;

	if (side == QU_RIGHT && p_process_obj->p_left)
	{
		p_left = p_process_obj->p_left;
		p_process_obj->p_left = p_left->p_right;
		p_left->p_right = p_process_obj;
		p_queue_instance->cw_height(p_queue_instance, p_process_obj,
			QU_SET_MODE);
		p_queue_instance->cw_height(p_queue_instance, p_left, QU_SET_MODE);
		return (p_left);
	}
	else if (side == QU_LEFT && p_process_obj->p_right)
	{
		p_right = p_process_obj->p_right;
		p_process_obj->p_right = p_right->p_left;
		p_right->p_left = p_process_obj;
		p_queue_instance->cw_height(p_queue_instance, p_process_obj,
			QU_SET_MODE);
		p_queue_instance->cw_height(p_queue_instance, p_right, QU_SET_MODE);
		return (p_right);
	}
	return (p_process_obj);
}

static int			cw_get_balance_factor(t_queue *p_queue_instance,
											t_process *p_process_instance)
{
	if (p_process_instance)
		return (p_queue_instance->cw_height(p_queue_instance,
		p_process_instance->p_right, QU_GET_MODE) - p_queue_instance->
		cw_height(p_queue_instance, p_process_instance->p_left, QU_GET_MODE));
	else
		return (0);
}

static int			cw_height(t_queue *p_queue_instance,
								t_process *p_process_obj, int mode)
{
	t_tmp			left_height;
	t_tmp			right_height;

	if (mode == QU_SET_MODE)
	{
		left_height = p_queue_instance->cw_height(p_queue_instance,
			p_process_obj->p_left, QU_GET_MODE);
		right_height = p_queue_instance->cw_height(p_queue_instance,
			p_process_obj->p_right, QU_GET_MODE);
		p_process_obj->height = (left_height > right_height ? left_height :
			right_height) + 1;
		return (0);
	}
	return (p_process_obj ? p_process_obj->height : 0);
}

static t_process	*cw_balance(t_queue *p_queue_instance,
									t_process *p_process_obj)
{
	if (p_process_obj)
	{
		p_queue_instance->cw_height(p_queue_instance, p_process_obj, QU_SET_MO);
		if (p_queue_instance->cw_get_balance_factor(p_queue_instance,
			p_process_obj) == 2)
		{
			if (p_queue_instance->cw_get_balance_factor(p_queue_instance,
				p_process_obj->p_right) < 0)
				p_process_obj->p_right = p_queue_instance->
			cw_rotate(p_queue_instance, p_process_obj->p_right, QU_RIGHT);
			return (p_queue_instance->cw_rotate(p_queue_instance,
				p_process_obj, QU_LEFT));
		}
		else if (p_queue_instance->cw_get_balance_factor(p_queue_instance,
			p_process_obj) == -2)
		{
			if (p_queue_instance->cw_get_balance_factor(p_queue_instance,
			p_process_obj->p_left) > 0)
				p_process_obj->p_left = p_queue_instance->
			cw_rotate(p_queue_instance, p_process_obj->p_left, QU_LEFT);
			return (p_queue_instance->cw_rotate(p_queue_instance,
				p_process_obj, QU_RIGHT));
		}
	}
	return (p_process_obj);
}

extern void			cw_queue_avl_tree_functions_linker(
									t_queue *p_queue_instance)
{
	p_queue_instance->cw_get_balance_factor = cw_get_balance_factor;
	p_queue_instance->cw_balance = cw_balance;
	p_queue_instance->cw_rotate = cw_rotate;
	p_queue_instance->cw_height = cw_height;
}
