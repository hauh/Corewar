/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_callback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 18:39:22 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	if (-p_game_obj->p_carriage_obj->p_owner->id == p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value)
	{
		p_game_obj->p_arena_obj->p_last_survivor = p_game_obj->p_carriage_obj->p_owner;
		p_game_obj->p_carriage_obj->p_owner->live_amount += 1;
	}
	p_game_obj->p_carriage_obj->last_speak_cycle = p_game_obj->p_arena_obj->cycle_amount;
	p_game_obj->p_arena_obj->live_amount += 1;
}

void	ld_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_carriage_obj->cw_check_carry(p_game_obj->p_carriage_obj);
}

void	st_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->second_arg);
}

void	add_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);;
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value + p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value;
	p_game_obj->p_carriage_obj->cw_conversion_value_to_bytes(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], CW_INT);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	sub_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value - p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value;
	p_game_obj->p_carriage_obj->cw_conversion_value_to_bytes(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], CW_INT);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	and_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value & p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value;
	p_game_obj->p_carriage_obj->cw_conversion_value_to_bytes(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], CW_INT);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	or_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value | p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value;
	p_game_obj->p_carriage_obj->cw_conversion_value_to_bytes(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], CW_INT);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	xor_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value ^ p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value;
	p_game_obj->p_carriage_obj->cw_conversion_value_to_bytes(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], CW_INT);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	zjmp_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	if (p_game_obj->p_carriage_obj->carry)
		p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.short_value - p_game_obj->p_carriage_obj->odometer);
}

void	ldi_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types (p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = ((p_game_obj->p_carriage_obj->first_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value) + (p_game_obj->p_carriage_obj->second_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value)) % IDX_MOD;
	p_game_obj->p_carriage_obj->cw_save_pos(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);
	p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value - p_game_obj->p_carriage_obj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, 1))
		p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->p_data[i] = p_game_obj->p_arena_obj->p_field[p_game_obj->p_carriage_obj->current_location];
	p_game_obj->p_carriage_obj->cw_carriage_return(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
}

void	sti_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types (p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_SPARE_BUF]->s_types.int_value = ((p_game_obj->p_carriage_obj->second_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value) + (p_game_obj->p_carriage_obj->third_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value)) % IDX_MOD;
	p_game_obj->p_carriage_obj->cw_save_pos(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);
	p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_SPARE_BUF]->s_types.int_value - p_game_obj->p_carriage_obj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, 1))
	{
		p_game_obj->p_arena_obj->p_field[p_game_obj->p_carriage_obj->current_location] = p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->p_data[i];
		if (p_game_obj->visualizator)
			cr_vis_putx(p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->p_data[i], p_game_obj->p_carriage_obj->current_location, p_game_obj->p_carriage_obj->p_owner->id, 0, p_game_obj->p_carriage_obj->game_ref);
	}
	p_game_obj->p_carriage_obj->cw_carriage_return(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);

}

void	fork_exec(t_corewar *p_game_obj)
{
	t_carriage *p_carriage_obj;

	p_game_obj->p_carriage_obj->cw_parse_types (p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	cw_create_instance_carriage(&p_carriage_obj);
	p_game_obj->p_carriage_obj->cw_copy_reg(p_game_obj->p_carriage_obj, p_carriage_obj);
	p_carriage_obj->carry = p_game_obj->p_carriage_obj->carry;
	p_carriage_obj->last_speak_cycle = p_game_obj->p_carriage_obj->last_speak_cycle;
	p_carriage_obj->current_location = (p_game_obj->p_carriage_obj->current_location + (p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.short_value - p_game_obj->p_carriage_obj->odometer) % IDX_MOD) % MEM_SIZE;
	if (p_carriage_obj->current_location < 0)
		p_carriage_obj->current_location = MEM_SIZE + p_carriage_obj->current_location;
	p_carriage_obj->pp_command_container = p_game_obj->p_carriage_obj->pp_command_container;
	p_carriage_obj->p_owner = p_game_obj->p_carriage_obj->p_owner;
	p_carriage_obj->id = ++p_game_obj->numerate_carriage;
	p_game_obj->cw_push_to_queue(p_game_obj, p_carriage_obj);
}

void	lld_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation	(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_carriage_obj->cw_check_carry	(p_game_obj->p_carriage_obj);
}

void	lldi_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types (p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2], p_game_obj->p_carriage_obj->second_arg);
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value = ((p_game_obj->p_carriage_obj->first_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.int_value) + (p_game_obj->p_carriage_obj->second_arg == CW_DIR_CODE ? p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.short_value :
	p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_2]->s_types.int_value));
	p_game_obj->p_carriage_obj->cw_save_pos(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);
	p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->s_types.int_value - p_game_obj->p_carriage_obj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_game_obj->p_carriage_obj->cw_move_to(p_game_obj->p_carriage_obj, 1))
		p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3]->p_data[i] = p_game_obj->p_arena_obj->p_field[p_game_obj->p_carriage_obj->current_location];
	p_game_obj->p_carriage_obj->cw_carriage_return(p_game_obj->p_carriage_obj, CW_ADDIT_SAVE);
	p_game_obj->p_carriage_obj->cw_write_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_3], p_game_obj->p_carriage_obj->third_arg);
	p_game_obj->p_carriage_obj->cw_check_carry(p_game_obj->p_carriage_obj);
}

void	lfork_exec(t_corewar *p_game_obj)
{
	t_carriage *p_carriage_obj;

	p_game_obj->p_carriage_obj->cw_parse_types (p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	cw_create_instance_carriage(&p_carriage_obj);
	p_game_obj->p_carriage_obj->cw_copy_reg(p_game_obj->p_carriage_obj, p_carriage_obj);
	p_carriage_obj->carry = p_game_obj->p_carriage_obj->carry;
	p_carriage_obj->last_speak_cycle = p_game_obj->p_carriage_obj->last_speak_cycle;
	p_carriage_obj->current_location = (p_game_obj->p_carriage_obj->current_location + (p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.short_value - p_game_obj->p_carriage_obj->odometer)) % MEM_SIZE;
	if (p_carriage_obj->current_location < 0)
		p_carriage_obj->current_location = MEM_SIZE + p_carriage_obj->current_location;
	p_carriage_obj->pp_command_container = p_game_obj->p_carriage_obj->pp_command_container;
	p_carriage_obj->p_owner = p_game_obj->p_carriage_obj->p_owner;
	p_carriage_obj->id = ++p_game_obj->numerate_carriage;
	p_game_obj->cw_push_to_queue(p_game_obj, p_carriage_obj);
}

void	aff_exec(t_corewar *p_game_obj)
{
	p_game_obj->p_carriage_obj->cw_parse_types(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj);
	if (p_game_obj->p_carriage_obj->error_ocurred) return ;
	p_game_obj->p_carriage_obj->cw_read_operation(p_game_obj->p_carriage_obj, p_game_obj->p_arena_obj, p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1], p_game_obj->p_carriage_obj->first_arg);
	//ft_printf("%c", p_game_obj->p_arena_obj->pa_buffer_set[CW_VALUE_BUF_1]->s_types.char_value);
}