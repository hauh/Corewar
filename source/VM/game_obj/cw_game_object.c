/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/31 12:30:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(t_corewar **pp_game_instance)
{
	(*pp_game_instance)->queue_size = 0;
	(*pp_game_instance)->players_amount = 0;
	(*pp_game_instance)->numerate_carriage = 0;
	(*pp_game_instance)->commands_amount = 0;
	(*pp_game_instance)->carriages_amount = 0;
	(*pp_game_instance)->last_check_cycle = 0;
	(*pp_game_instance)->visualizator = CW_FALSE;
	(*pp_game_instance)->load_dump = CW_FALSE;
	(*pp_game_instance)->p_arena_obj = NULL;
	(*pp_game_instance)->p_player_obj = NULL;
	(*pp_game_instance)->p_carriage_obj = NULL;
	(*pp_game_instance)->p_waiting_queue = NULL;
	(*pp_game_instance)->vis = NULL;
}

static void		cw_destructor(t_corewar **pp_game_instance)
{
	cr_vis_main(*pp_game_instance, V_CLEANUP);
	(*pp_game_instance)->p_arena_obj->cw_destructor(&(*pp_game_instance)->p_arena_obj);
	(*pp_game_instance)->cw_free_all_carriages(*pp_game_instance);
	(*pp_game_instance)->cw_free_all_players(*pp_game_instance);
	(*pp_game_instance)->cw_free_all_commands(*pp_game_instance);
	free(*pp_game_instance);
	*pp_game_instance = NULL;
}

extern void		cw_create_instance_game(t_corewar **pp_game_obj)
{
	if (!(*pp_game_obj = (t_corewar *)malloc(sizeof(t_corewar))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_GAME);
	(*pp_game_obj)->cw_constructor = cw_constructor;
	(*pp_game_obj)->cw_destructor = cw_destructor;
	(*pp_game_obj)->cw_arrange_units_on_field = cw_arrange_units_on_field;
	(*pp_game_obj)->cw_add_carriage_to_list = cw_add_t_carriageo_list;
	(*pp_game_obj)->cw_merge_queue_to_list = cw_merge_queue_to_list;
	(*pp_game_obj)->cw_carriage_obj_init = cw_carriage_obj_init;
	(*pp_game_obj)->cw_command_obj_init = cw_command_obj_init;
	(*pp_game_obj)->cw_free_all_commands = cw_free_all_commands;
	(*pp_game_obj)->cw_player_obj_init = cw_player_obj_init;
	(*pp_game_obj)->cw_arena_obj_init = cw_arena_obj_init;
	(*pp_game_obj)->cw_start_game = cw_start_game;
	(*pp_game_obj)->cw_main_checking = cw_main_checking;
	(*pp_game_obj)->cw_delete_carriage = cw_delete_carriage;
	(*pp_game_obj)->cw_free_all_players = cw_free_all_players;
	(*pp_game_obj)->cw_add_player_to_list = cw_add_player_to_list;
	(*pp_game_obj)->cw_free_all_carriages = cw_free_all_carriages;
	(*pp_game_obj)->cw_introduce_players = cw_introduce_players;
	(*pp_game_obj)->cw_congratulations = cw_congratulations;
	(*pp_game_obj)->cw_push_to_queue = cw_push_to_queue;
	(*pp_game_obj)->cw_queue_obj_init = cw_queue_obj_init;
	(*pp_game_obj)->cw_stack_obj_init = cw_stack_obj_init;
	(*pp_game_obj)->cw_constructor(pp_game_obj);
}
