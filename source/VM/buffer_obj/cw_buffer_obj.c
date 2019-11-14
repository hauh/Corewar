/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:37:47 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_buffer **pp_buffer_instance)
{
	if (!((*pp_buffer_instance)->p_data =
	(unsigned char *)malloc(sizeof(unsigned char) * CW_REG_SIZE)))
		cw_error_catcher(BU_OBJECT_NAME, BU_DATA_ERROR, __FILE__, __LINE__);
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
		cw_error_catcher(BU_OBJECT_NAME, BU_OBJECT_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_buffer_obj, 0, sizeof(t_buffer));
	(*pp_buffer_obj)->cw_constructor = cw_constructor;
	(*pp_buffer_obj)->cw_destructor = cw_destructor;
	(*pp_buffer_obj)->cw_constructor(pp_buffer_obj);
	cw_buffer_functions_linker(*pp_buffer_obj);
}
