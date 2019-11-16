/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_and_or_xor_zjmp_ldi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:57:55 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 13:52:33 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	and_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value =
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value &
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value;
	GA_WORK_UNIT_O->cw_conversion(GA_WORK_UNIT_O,
		p_game_obj->AR_VALUE_BUF_3_O, CW_INT, PR_VALUE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	or_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value =
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value |
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value;
	GA_WORK_UNIT_O->cw_conversion(GA_WORK_UNIT_O,
		p_game_obj->AR_VALUE_BUF_3_O, CW_INT, PR_VALUE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	xor_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value =
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value ^
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value;
	GA_WORK_UNIT_O->cw_conversion(GA_WORK_UNIT_O,
		p_game_obj->AR_VALUE_BUF_3_O, CW_INT, PR_VALUE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	zjmp_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	if (GA_WORK_UNIT_O->carry)
		GA_WORK_UNIT_O->cw_move_to(GA_WORK_UNIT_O,
			(p_game_obj->AR_VALUE_BUF_1_O->s_types.short_value % IDX_MOD) -
				GA_WORK_UNIT_O->odometer);
}

void	ldi_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value = (((GA_FIRST_ARG)
	== CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_1_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value) + ((GA_SECOND_ARG)
	== CW_DIR_CODE ? p_game_obj->AR_VALUE_BUF_2_O->s_types.short_value :
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value)) % IDX_MOD % MEM_SIZE;
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
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
}
