/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live_ld_st_add_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:57:08 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 15:46:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	if (p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value <= -1 &&
		p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value >= -4)
	{
		GA_ITERATOR_O = CW_ITERATOR;
		while (++GA_ITERATOR_O < GA_SC_PL_AM_O)
		{
			if (GA_SC_PL_O->id ==
			-p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value)
				GA_ARENA_OBJ_O->p_winner = GA_SC_PL_O;
			GA_SC_PL_O = GA_SC_PL_O->p_next;
		}
		if (GA_VERBOSE_O == GA_SHOW_LIVES)
			ft_printf("Player %d (%s) is said to be alive\n",
			GA_ARENA_OBJ_O->p_winner->id, GA_ARENA_OBJ_O->p_winner->p_name);
		GA_ARENA_OBJ_O->p_winner->live_amount += 1;
	}
	GA_WORK_UNIT_O->last_speak_cycle = GA_ARENA_OBJ_O->cycle;
	GA_ARENA_OBJ_O->live_amount += 1;
}

void	ld_exec(t_corewar *p_game_obj)
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

void	st_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_SECOND_ARG);
}

void	add_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value =
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value +
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value;
	GA_WORK_UNIT_O->cw_conversion(GA_WORK_UNIT_O,
		p_game_obj->AR_VALUE_BUF_3_O, CW_INT, PR_VALUE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}

void	sub_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_2_O, GA_SECOND_ARG);
	p_game_obj->AR_VALUE_BUF_3_O->s_types.int_value =
	p_game_obj->AR_VALUE_BUF_1_O->s_types.int_value -
	p_game_obj->AR_VALUE_BUF_2_O->s_types.int_value;
	GA_WORK_UNIT_O->cw_conversion(GA_WORK_UNIT_O,
		p_game_obj->AR_VALUE_BUF_3_O, CW_INT, PR_VALUE);
	GA_WORK_UNIT_O->cw_write_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG);
	GA_WORK_UNIT_O->cw_check_carry(GA_WORK_UNIT_O);
}
