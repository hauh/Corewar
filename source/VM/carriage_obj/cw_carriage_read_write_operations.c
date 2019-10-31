/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_read_write_operations.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:10:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/31 17:22:43 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_write_operation(t_carriage *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE] = pBufferObj->p_data[i];
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CW_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
		p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_carriage_instance->cw_save_pos(p_carriage_instance, CW_ADDIT_SAVE);
		p_carriage_instance->cw_move_to	(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
		{
			p_arena_obj->p_field[p_carriage_instance->current_location] = pBufferObj->p_data[i];
			if (p_carriage_instance->game_ref->visualizator)
				cr_vis_putx(pBufferObj->p_data[i], p_carriage_instance->current_location, p_carriage_instance->p_owner->id, 0, p_carriage_instance->game_ref);
		}
		p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_ADDIT_SAVE);
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Write operation error");
}

void	cw_read_operation(t_carriage *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			pBufferObj->p_data[i] = p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = 4 - p_carriage_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, 4 - p_carriage_instance->p_current_command->dir_size);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CW_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_carriage_instance->cw_save_pos(p_carriage_instance, CW_ADDIT_SAVE);
		p_carriage_instance->cw_move_to(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_ADDIT_SAVE);
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Read not valid");
}