/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_read_write_functions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:10:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 15:52:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_ind_write_handle(t_process *p_process_instance,
						t_arena *p_arena_obj, t_buffer *p_buffer_obj, t_iter i)
{
	AR_SYSTEM_BUF_O->cw_erase_data(AR_SYSTEM_BUF_O);
	i = CW_SHORT - 1;
	while (++i < CW_REG_SIZE)
	{
		AR_SYSTEM_BUF_O->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_move_to(p_process_instance, 1);
	}
	p_process_instance->cw_conversion(p_process_instance,
		AR_SYSTEM_BUF_O, CW_SHORT, PR_BYTE);
	if (PR_CURRENT_COMMAND_I->id != CO_LLD)
		AR_SYSTEM_BUF_O->s_types.short_value %= IDX_MOD;
	p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
	p_process_instance->cw_move_to(p_process_instance,
		AR_SYSTEM_BUF_O->s_types.short_value - PR_ODOMETER_I);
	i = CW_ITERATOR;
	while (++i < CW_REG_SIZE)
	{
		AR_FIELD_O[PR_CURRENT_LOCATION_I] = BU_DATA_O[i];
		p_process_instance->cw_move_to(p_process_instance, 1);
		if (AR_NCURSES_O)
			cr_vis_putx(BU_DATA_O[i], PR_CURRENT_LOCATION_I, PR_OWNER_I->id, 0);
	}
	p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
}

static void	cw_write_operation(t_process *p_process_instance,
					t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
{
	t_iter	i;

	i = CW_ITERATOR;
	if (input_arg == CW_REG_CODE)
	{
		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
		while (++i < CW_REG_SIZE)
			PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE] =
				BU_DATA_O[i];
		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
	}
	else if (input_arg == CW_IND_CODE)
		cw_ind_write_handle(p_process_instance, p_arena_obj, p_buffer_obj, i);
	else
		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
}

static void	cw_ind_read_handle(t_process *p_process_instance,
						t_arena *p_arena_obj, t_buffer *p_buffer_obj, t_iter i)
{
	AR_BUFFERS_O[CW_SYSTEM_BUF]->cw_erase_data(AR_BUFFERS_O[CW_SYSTEM_BUF]);
	i = CW_SHORT - 1;
	while (++i < CW_REG_SIZE)
	{
		AR_SYSTEM_BUF_O->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_move_to(p_process_instance, 1);
	}
	p_process_instance->cw_conversion(p_process_instance,
		AR_SYSTEM_BUF_O, CW_SHORT, PR_BYTE);
	if (PR_CURRENT_COMMAND_I->id != CO_LLD)
		AR_SYSTEM_BUF_O->s_types.short_value %= IDX_MOD;
	p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
	PR_MOVE_TO(AR_SYSTEM_BUF_O->s_types.short_value - PR_ODOMETER_I);
	i = CW_ITERATOR;
	while (++i < CW_REG_SIZE)
	{
		BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
		p_process_instance->cw_move_to(p_process_instance, 1);
	}
	p_process_instance->cw_conversion(p_process_instance, p_buffer_obj,
		CW_INT, PR_BYTE);
	p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
}

static void	cw_read_operation(t_process *p_process_instance,
				t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
{
	t_iter	i;

	p_buffer_obj->cw_erase_data(p_buffer_obj);
	if (input_arg == CW_REG_CODE && (i = CW_ITERATOR))
	{
		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
		while (++i < CW_REG_SIZE)
			BU_DATA_O[i] =
				PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE];
		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj,
			CW_INT, PR_BYTE);
		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
	}
	else if (input_arg == CW_DIR_CODE && (i = 3 - PR_CO_DIR_SIZE_I) >= -1)
	{
		while (++i < CW_REG_SIZE)
		{
			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
			p_process_instance->cw_move_to(p_process_instance, 1);
		}
		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj,
			4 - PR_CURRENT_COMMAND_I->dir_size, PR_BYTE);
	}
	else if (input_arg == CW_IND_CODE)
		cw_ind_read_handle(p_process_instance, p_arena_obj, p_buffer_obj, i);
}

extern void	cw_process_read_write_functions_linker(t_process *p_process_linker)
{
	p_process_linker->cw_read_operation = cw_read_operation;
	p_process_linker->cw_write_operation = cw_write_operation;
}
