/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwStackObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:20:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 19:53:26 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_STACK_OBJECT_H
# define CW_STACK_OBJECT_H

#include "cwTypedefObjects.h"

typedef struct	stackk_s
{
	counter_t	size;

	mark_t		max_carriage_number;
	mark_t		current_waiting_time;
	mark_t		min_carriage_waiting_time;

	carriage_t	*p_current_carriage;

	void		(*cw_constructor)	(stackk_t **);
	void		(*cw_push)			(stackk_t *, carriage_t *);
	void		(*cw_pop)			(stackk_t *, carriage_t **);
	void		(*cw_peek)			(stackk_t *, carriage_t *);
	void		(*cw_rotate)		(stackk_t *, int);
	void		(*cw_distribute)	(stackk_t *, queue_t *, queue_t *);
	void		(*cw_reduce_w_t)	(stackk_t *);
	void		(*cw_destructor)	(stackk_t **);
}				stackk_t;

#endif