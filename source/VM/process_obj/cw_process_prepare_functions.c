/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_prepare_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:37 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 14:03:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_exec_command(t_process *p_process_instance,
								t_corewar *p_game_obj)
{
	if (!PR_CURRENT_COMMAND_I)
	{
		p_process_instance->cw_move_to(p_process_instance, 1);
		PR_NEAREST_CYCLE_I = GA_ARENA_OBJ_O->cycle + 1;
	}
	else if (PR_NEAREST_CYCLE_I == GA_ARENA_OBJ_O->cycle)
	{
		PR_CURRENT_COMMAND_I->cw_callback(p_game_obj);
		PR_CURRENT_COMMAND_I = NULL;
		PR_WAITING_TIME_I = 0;
		PR_NEAREST_CYCLE_I = GA_ARENA_OBJ_O->cycle + 1;
	}
}

static void	cw_set_command_time(t_process *p_process_instance,
									t_corewar *p_game_obj)
{
	if (PR_CURRENT_COMMAND_I || GA_ARENA_OBJ_O->p_field[PR_CURRENT_LOCATION_I]
	< CO_LIVE || GA_ARENA_OBJ_O->p_field[PR_CURRENT_LOCATION_I] > CO_AFF)
		return ;
	PR_CURRENT_COMMAND_I =
		PR_COMMAND_CONTAINER_I[GA_ARENA_OBJ_O->p_field[PR_CURRENT_LOCATION_I]];
	PR_NEAREST_CYCLE_I =
		GA_ARENA_OBJ_O->cycle + PR_CURRENT_COMMAND_I->waiting_time - 1;
	p_process_instance->cw_save_pos(p_process_instance, PR_MAIN_SAVE);
	PR_ERROR_OCCURED_I = CW_FALSE;
	PR_OFFSET_I = 0;
}

static void	cw_set_owner(t_process *p_process_instance,
							t_scheduler *p_scheduler_obj)
{
	int	iter;

	iter = CW_ITERATOR;
	while (++iter < SC_PLAYERS_AMOUNT_O)
	{
		if (SC_PLAYERS_LIST_O->id > SC_PLAYERS_AMOUNT_O)
			cw_error_catcher(PL_OBJECT_NAME,
				PL_SET_ID_ERROR, __FILE__, __LINE__);
		if (SC_PLAYERS_LIST_O->id == PR_ID_I)
			PR_OWNER_I = SC_PLAYERS_LIST_O;
		SC_PLAYERS_LIST_O = SC_PLAYERS_LIST_O->p_next;
	}
}

extern void	cw_process_prepare_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_set_owner = cw_set_owner;
	p_process_instance->cw_exec_command = cw_exec_command;
	p_process_instance->cw_set_command_time = cw_set_command_time;
}
