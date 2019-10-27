/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwQueueObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 13:18:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cwTypedefObjects.h"

#ifndef CW_QUEUE_OBJECT_H
# define CW_QUEUE_OBJECT_H

typedef struct	queue_s
{
	counter_t	size;

	carriage_t	*p_current_carriage;

	void		(*cw_constructor)	(queue_t **);
	void		(*cw_enqueue)		(queue_t *, carriage_t *);
	void		(*cw_dequeue)		(queue_t *, carriage_t **);
	void		(*cw_count)			(queue_t *, int *);
	void		(*cw_peek)			(queue_t *, carriage_t **);
	void		(*cw_sort)			(queue_t *);
	void		(*cw_reduce_time)	(queue_t *);
	void		(*cw_exec)			(queue_t *);
	void		(*cw_print_content)	(queue_t *);
	void		(*cw_destructor)	(queue_t **);
}				queue_t;

#endif