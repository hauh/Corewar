/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_registers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 15:49:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_copy_reg(t_process *p_process_instance, t_process *p_process_obj)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE * CW_REG_NUM)
		PR_REGISTERS_O[iter] = PR_REGISTERS_I[iter];
}

static void	cw_write_owner_id_to_reg(t_process *p_process_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE)
		PR_REGISTERS_I[iter] = (-PR_OWNER_I->id << (iter * 8)) >> 24;
}

static void	cw_check_carry(t_process *p_process_instance)
{
	int		iter;

	iter = PR_CURRENT_REGISTER_I * CW_REG_SIZE - 1;
	while (++iter < (PR_CURRENT_REGISTER_I + 1) * CW_REG_SIZE)
		if (PR_REGISTERS_I[iter] != 0 && !(PR_CARRY_I = 0))
			return ;
	PR_CARRY_I = 1;
}

static void	cw_conversion(t_process *p_process_instance, t_buffer *p_buffer_obj,
							int type, int mode)
{
	if (mode == PR_VALUE)
	{
		p_buffer_obj->cw_erase_data(p_buffer_obj);
		while (type < CW_REG_SIZE)
		{
			BU_DATA_O[type] = BU_INT_VALUE_O >> (24 - (type * 8)) & 0xff;
			++type;
		}
	}
	else if (mode == PR_BYTE)
	{
		BU_INT_VALUE_O = 0;
		while (type < CW_REG_SIZE)
		{
			BU_INT_VALUE_O |= BU_DATA_O[type] << ((3 - type) * 8);
			++type;
		}
	}
	(void)p_process_instance;
}

extern void	cw_process_registers_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_write_owner_id_to_reg = cw_write_owner_id_to_reg;
	p_process_instance->cw_check_carry = cw_check_carry;
	p_process_instance->cw_conversion = cw_conversion;
	p_process_instance->cw_copy_reg = cw_copy_reg;
}
