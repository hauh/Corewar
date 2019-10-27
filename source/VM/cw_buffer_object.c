/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 12:10:06 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_erase_data(buffer_t *p_buffer_instance)
{
	ft_memset(p_buffer_instance->p_data, 0, CW_REG_SIZE);
}

static void	cw_constructor(buffer_t **pp_buffer_instance)
{
	if (!((*pp_buffer_instance)->p_data =
		(unsigned char *)malloc(sizeof(unsigned char) * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*pp_buffer_instance)->s_types.int_value = 0;
	(*pp_buffer_instance)->s_types.char_value = 0;
	(*pp_buffer_instance)->s_types.short_value = 0;
}

static void	cw_destructor(buffer_t **pp_buffer_instance)
{
	free((*pp_buffer_instance)->p_data);
	free(*pp_buffer_instance);
	*pp_buffer_instance = NULL;
}

extern void	cw_create_instance_buffer(buffer_t **pp_buffer_obj)
{
	if (!(*pp_buffer_obj = (buffer_t *)malloc(sizeof(buffer_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*pp_buffer_obj)->cw_constructor = cw_constructor;
	(*pp_buffer_obj)->cw_destructor = cw_destructor;
	(*pp_buffer_obj)->cw_erase_data = cw_erase_data;
	(*pp_buffer_obj)->cw_constructor(pp_buffer_obj);
}
