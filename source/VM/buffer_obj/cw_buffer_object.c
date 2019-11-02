/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:53:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_buffer **pp_buffer_instance)
{
	if (!((*pp_buffer_instance)->p_data =
	(unsigned char *)malloc(sizeof(unsigned char) * CW_REG_SIZE)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
}

static void	cw_destructor(t_buffer **pp_buffer_instance)
{
	free((*pp_buffer_instance)->p_data);
	free(*pp_buffer_instance);
	*pp_buffer_instance = NULL;
}

static void cw_error(t_buffer *pp_buffer_instance, char *file, char *function, int line)
{
	ft_printf("Run time error occured:\n");
	ft_printf("\tObject: arena\n");
	ft_printf("\tFile: %s", file);
	ft_printf("\tFunction: %s", function);
	ft_printf("\tLine: %d", line);
	ft_printf("\tNext data was in object: \n");
	ft_printf("\t\t");
}

extern void	cw_create_instance_buffer(t_buffer **pp_buffer_obj)
{
	if (!(*pp_buffer_obj = (t_buffer *)malloc(sizeof(t_buffer))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset(*pp_buffer_obj, 0, sizeof(t_buffer));
	(*pp_buffer_obj)->cw_constructor = cw_constructor;
	(*pp_buffer_obj)->cw_destructor = cw_destructor;
	(*pp_buffer_obj)->cw_constructor(pp_buffer_obj);
	cw_buffer_functions_linker(*pp_buffer_obj);
}
