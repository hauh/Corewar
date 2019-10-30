/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 15:40:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_command **pp_command_instance)
{
	(*pp_command_instance)->id = 0;
	(*pp_command_instance)->args = 0;
	(*pp_command_instance)->dir_size = 0;
	(*pp_command_instance)->change_carry = 0;
	(*pp_command_instance)->waiting_time = 0;
	(*pp_command_instance)->type_byte = 0;
	(*pp_command_instance)->cw_callback = NULL;
}

static void	cw_destructor(t_command **pp_command_instance)
{
	free(*pp_command_instance);
	*pp_command_instance = NULL;
}

extern void	cw_create_instance_command(t_command **pp_command_obj)
{
	if (!(*pp_command_obj = (t_command *)malloc(sizeof(t_command))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_COMMAND);
	(*pp_command_obj)->cw_constructor = cw_constructor;
	(*pp_command_obj)->cw_destructor = cw_destructor;
	(*pp_command_obj)->cw_recognize = cw_recognize_command;
	(*pp_command_obj)->cw_put_param = cw_put_param;
	(*pp_command_obj)->cw_constructor(pp_command_obj);
}
