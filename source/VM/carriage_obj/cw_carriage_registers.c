/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_registers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/01 13:45:06 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_reg_check(t_carriage *p_carriage_instance, t_arena *p_arena_obj, int type, int *found)
{
	if (!*found)
		return ;
	if (type == CW_REG_CODE)
	{
		p_carriage_instance->offset += CW_REG_CODE_SIZE;
		if (p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] < 1
		|| p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] > 16)
		{
			p_carriage_instance->error_ocurred = CW_TRUE;
			*found = CW_FALSE;
		}
	}
	else if (type == CW_DIR_CODE)
		p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size;
	else if (type == CW_IND_CODE)
		p_carriage_instance->offset += CW_IND_CODE_SIZE;
}

void	cw_copy_reg(t_carriage *p_carriage_instance, t_carriage *p_copying_carriage)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE * CW_REG_NUMBER)
		p_copying_carriage->p_registers[iter] = p_carriage_instance->p_registers[iter];
}

void	cw_write_owner_id_to_reg(t_carriage *p_carriage_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	while (iter < CW_REG_SIZE)
	{
		p_carriage_instance->p_registers[iter] = (-p_carriage_instance->p_owner->id << (iter * 8)) >> 24;
		++iter;
	}
}

void	cw_check_carry(t_carriage *p_carriage_instance)
{
	int		iter;

	iter = p_carriage_instance->current_register * CW_REG_SIZE - 1;
	while (++iter < (p_carriage_instance->current_register + 1) * CW_REG_SIZE)
		if (p_carriage_instance->p_registers[iter] != 0 && !(p_carriage_instance->carry = 0))
			return ;
	p_carriage_instance->carry = 1;
}

void	cw_conversion_value_to_bytes(t_carriage *pCarraigeInstance, t_buffer *pBufferObj, int type)
{
	ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->p_data[type] = pBufferObj->s_types.int_value >> (24 - (type * 8)) & 0xff;
		++type;
	}
}

void	cw_conversion_bytes_to_value(t_carriage *pCarraigeInstance, t_buffer *pBufferObj, int type)
{
	pBufferObj->s_types.int_value = 0;
	while (type < CW_REG_SIZE)
	{
		pBufferObj->s_types.int_value |= pBufferObj->p_data[type] << ((3 - type) * 8);
		++type;
	}
}