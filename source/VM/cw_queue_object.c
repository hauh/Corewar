/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:13:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 18:16:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(queue_t **pp_queue_instance)
{
	;
}

static void		cw_destructor(queue_t **pp_queue_instance)
{
	;
}

extern void		cw_create_queue_object(queue_t **pp_queue_obj)
{
	if (!(*pp_queue_obj = (queue_t *)malloc(sizeof(queue_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, "Queue object has not been created");
	(*pp_queue_obj)->cw_constructor = cw_constructor;
	(*pp_queue_obj)->cw_destructor = cw_destructor;
}