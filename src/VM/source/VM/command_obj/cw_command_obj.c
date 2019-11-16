/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:38:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_command **pp_command_instance)
{
	(*pp_command_instance)->id = CO_NAMELESS;
}

static void	cw_destructor(t_command **pp_command_instance)
{
	free(*pp_command_instance);
	*pp_command_instance = NULL;
}

extern void	cw_create_instance_command(t_command **pp_command_obj)
{
	if (!(*pp_command_obj = (t_command *)malloc(sizeof(t_command))))
		cw_error_catcher(CO_OBJECT_NAME, CO_OBJECT_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_command_obj, 0, sizeof(t_command));
	(*pp_command_obj)->cw_constructor = cw_constructor;
	(*pp_command_obj)->cw_destructor = cw_destructor;
	(*pp_command_obj)->cw_constructor(pp_command_obj);
	cw_command_functions_linker(*pp_command_obj);
}
