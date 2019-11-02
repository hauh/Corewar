/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_object.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:54:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 19:22:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

static void	cw_constructor(t_scheduler **pp_scheduler_instance)
{
	(*pp_scheduler_instance)->nearest_cycle = 1;
}

static void	cw_destructor(t_scheduler **pp_scheduler_instance)
{
	free(*pp_scheduler_instance);
	*pp_scheduler_instance = NULL;
}

extern void	cw_create_instance_scheduler(t_scheduler **pp_scheduler_obj)
{
	if (!(*pp_scheduler_obj = (t_scheduler *)malloc(sizeof(t_scheduler))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_GAME);
	(*pp_scheduler_obj)->cw_constructor = cw_constructor;
	(*pp_scheduler_obj)->cw_destructor = cw_destructor;
	(*pp_scheduler_obj)->cw_constructor(pp_scheduler_obj);
}