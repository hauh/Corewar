/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_stack_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:20:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 14:39:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_STACK_OBJECT_H
# define CW_STACK_OBJECT_H

#include "cw_obj_container.h"

typedef struct	s_stack
{
	t_counter	size;

	t_mark		max_carriage_number;
	t_mark		current_waiting_time;
	t_mark		min_carriage_waiting_time;

	t_carriage	*p_current_carriage;

	void		(*cw_constructor)	(t_stack **);
	void		(*cw_push)			(t_stack *, t_carriage *);
	void		(*cw_pop)			(t_stack *, t_carriage **);
	void		(*cw_peek)			(t_stack *, t_carriage **);
	void		(*cw_rotate)		(t_stack *, int);
	void		(*cw_reverse_rotate)(t_stack *);
	void		(*cw_print_content)	(t_stack *);
	void		(*cw_distribute)	(t_stack *, t_queue *, t_arena *);
	void		(*cw_reduce_w_t)	(t_stack *);
	void		(*cw_destructor)	(t_stack **);
}				t_stack;

#endif