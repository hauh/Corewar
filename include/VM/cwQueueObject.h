/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwQueueObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 20:02:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cwTypedefObjects.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	queue_s
{
	carriage_t	*p_current_carriage;
	carriage_t 	*p_next_carriage;
	carriage_t 	*p_prev_carriage;

	carriage_t	*p_next;
	carriage_t	*p_prev;

	void		(*cw_constructor)	(queue_t **);
	void		(*cw_enqueue)		(queue_t *, carriage_t *);
	void		(*cw_dequeue)		(queue_t *, carriage_t *);
	void		(*cw_count)			(queue_t *, int *);
	void		(*cw_peek)			(queue_t *, carriage_t *);
	void		(*cw_sort)			(queue_t *);
	void		(*cw_reduce_time)	(queue_t *);
	void		(*cw_exec)			(queue_t *);
	void		(*cw_destructor)	(queue_t **);
}				queue_t;

#endif