/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 16:54:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_buffer **pp_buffer_instance)
{
	if (!((*pp_buffer_instance)->p_data =
		(unsigned char *)malloc(sizeof(unsigned char) * CW_REG_SIZE)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*pp_buffer_instance)->s_types.int_value = 0;
	(*pp_buffer_instance)->s_types.char_value = 0;
	(*pp_buffer_instance)->s_types.short_value = 0;
}

static void	cw_destructor(t_buffer **pp_buffer_instance)
{
	free((*pp_buffer_instance)->p_data);
	free(*pp_buffer_instance);
	*pp_buffer_instance = NULL;
}

extern void	cw_create_instance_buffer(t_buffer **pp_buffer_obj)
{
	if (!(*pp_buffer_obj = (t_buffer *)malloc(sizeof(t_buffer))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*pp_buffer_obj)->cw_constructor = cw_constructor;
	(*pp_buffer_obj)->cw_destructor = cw_destructor;
	(*pp_buffer_obj)->cw_erase_data = cw_erase_data;
	(*pp_buffer_obj)->cw_constructor(pp_buffer_obj);
}
