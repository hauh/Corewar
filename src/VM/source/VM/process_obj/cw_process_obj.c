/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 19:49:19 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_process **pp_process_instance)
{
	if (!((*pp_process_instance)->p_registers =
	(unsigned char *)malloc(sizeof(unsigned char) * (CW_REG_NUM * CW_REG_L))))
		cw_error_catcher(PR_OBJECT_NAME, PR_OBJECT_ERROR, __FILE__, __LINE__);
	ft_memset((*pp_process_instance)->p_registers, 0, CW_REG_NUM * CW_REG_L);
	(*pp_process_instance)->nearest_cycle = 1;
}

static void	cw_destructor(t_process **pp_process_instance)
{
	free((*pp_process_instance)->p_registers);
	free((*pp_process_instance));
	*pp_process_instance = NULL;
}

extern void	cw_create_instance_process(t_process **pp_process_obj)
{
	if (!(*pp_process_obj = (t_process *)malloc(sizeof(t_process))))
		cw_error_catcher(PR_OBJECT_NAME, PR_OBJECT_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_process_obj, 0, sizeof(t_process));
	(*pp_process_obj)->cw_constructor = cw_constructor;
	(*pp_process_obj)->cw_destructor = cw_destructor;
	(*pp_process_obj)->cw_constructor(pp_process_obj);
	cw_process_movements_functions_linker(*pp_process_obj);
	cw_process_prepare_functions_linker(*pp_process_obj);
	cw_process_read_write_functions_linker(*pp_process_obj);
	cw_process_registers_functions_linker(*pp_process_obj);
}
