/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_sti_fork_lld_lldi_lfork.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/15 17:39:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sti_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	p_game_obj->AR_SPARE_BUF_O->s_types.int_value = (((GA_SECOND_ARG) ==
	CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_2_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value) + ((GA_THIRD_ARG) ==
	CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_3_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value)) % IDX_MOD % MEM_SIZE;
	GA_WORK_UNIT_O->cw_save_pos(GA_WORK_UNIT_O, PR_ADDIT_SAVE);
	GA_WORK_UNIT_O->cw_move_to(GA_WORK_UNIT_O,
	p_game_obj->AR_SPARE_BUF_O->s_types.int_value - GA_WORK_UNIT_O->odometer);
	GA_ITERATOR_O = CW_ITERATOR;
	while (++GA_ITERATOR_O < CW_REG_SIZE)
	{
		GA_ARENA_OBJ_O->p_field[GA_WORK_UNIT_O->current_location] = SPI2;
		GA_WORK_UNIT_O->cw_move_to(GA_WORK_UNIT_O, 1);
		GA_NCURSES_O ? cr_vis_putx(SPI2, SPI3, SPI4, SPI5) : 0;
	}
	GA_WORK_UNIT_O->cw_carriage_return(GA_WORK_UNIT_O, PR_ADDIT_SAVE);
}

void	fork_exec(t_corewar *p_game_obj)
{
	t_process *p_process_obj;

	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	cw_create_instance_process(&p_process_obj);
	GA_WORK_UNIT_O->cw_copy_reg(GA_WORK_UNIT_O, p_process_obj);
	p_process_obj->carry = GA_WORK_UNIT_O->carry;
	p_process_obj->last_speak_cycle = GA_WORK_UNIT_O->last_speak_cycle;
	p_process_obj->current_location = (GA_WORK_UNIT_O->save_point +
	(p_game_obj->AR_VALUE_BUF_1_O->s_types.short_value % IDX_MOD)) % MEM_SIZE;
	if (p_process_obj->current_location < 0)
		p_process_obj->current_location = MEM_SIZE +
			p_process_obj->current_location;
	p_process_obj->pp_command_container = GA_WORK_UNIT_O->pp_command_container;
	p_process_obj->p_owner = GA_WORK_UNIT_O->p_owner;
	p_process_obj->id = ++p_game_obj->numerate_carriage;
	p_process_obj->nearest_cycle = GA_ARENA_OBJ_O->cycle + 1;
	p_game_obj->p_scheduler->cw_insert_process(p_game_obj->p_scheduler,
		p_process_obj, p_process_obj->nearest_cycle);
}

void	lld_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_SECOND_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	lldi_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value = (((GA_FIRST_ARG) ==
		CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_1_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value) + ((GA_SECOND_ARG) ==
		CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_2_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value)) % MEM_SIZE;
	GA_WORK_UNIT_O->cw_save_pos(GA_WORK_UNIT_O, PR_ADDIT_SAVE);
	GA_WORK_UNIT_O->cw_move_to(GA_WORK_UNIT_O,
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value - GA_WORK_UNIT_O->odometer);
	GA_ITERATOR_O = CW_ITERATOR;
	while (++GA_ITERATOR_O < CW_REG_SIZE)
	{
		p_game_obj->AR_VALUE_BUF_3_O->p_data[GA_ITERATOR_O] =
			GA_ARENA_OBJ_O->p_field[GA_WORK_UNIT_O->current_location];
		GA_WORK_UNIT_O->cw_move_to(GA_WORK_UNIT_O, 1);
	}
	GA_WORK_UNIT_O->cw_carriage_return(GA_WORK_UNIT_O, PR_ADDIT_SAVE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O, GA);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	lfork_exec(t_corewar *p_game_obj)
{
	t_process *p_process_obj;

	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	cw_create_instance_process(&p_process_obj);
	GA_WORK_UNIT_O->cw_copy_reg(GA_WORK_UNIT_O, p_process_obj);
	p_process_obj->carry = GA_WORK_UNIT_O->carry;
	p_process_obj->last_speak_cycle = GA_WORK_UNIT_O->last_speak_cycle;
	p_process_obj->current_location = (GA_WORK_UNIT_O->save_point +
		p_game_obj->AR_VALUE_BUF_1_O->s_types.short_value) % MEM_SIZE;
	if (p_process_obj->current_location < 0)
		p_process_obj->current_location = MEM_SIZE +
			p_process_obj->current_location;
	p_process_obj->pp_command_container =
		GA_WORK_UNIT_O->pp_command_container;
	p_process_obj->p_owner = GA_WORK_UNIT_O->p_owner;
	p_process_obj->id = ++p_game_obj->numerate_carriage;
	p_process_obj->nearest_cycle = GA_ARENA_OBJ_O->cycle + 1;
	p_game_obj->p_scheduler->cw_insert_process(p_game_obj->p_scheduler,
		p_process_obj, p_process_obj->nearest_cycle);
}
