/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 19:41:01 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*p_game_obj;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_obj_init(p_game_obj);
	p_game_obj->cw_player_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_carriage_obj_init(p_game_obj);
	p_game_obj->cw_command_obj_init(p_game_obj);
	for (int i = 1; i < CW_COMMAND_AMOUNT; ++i)
		ft_printf("%3d %08b %08b %08b %3d %3d %3d %5d\n",
		p_game_obj->pa_commands[i]->id,
		p_game_obj->pa_commands[i]->args >> 24 & 0xff,
		p_game_obj->pa_commands[i]->args >> 16 & 0xff,
		p_game_obj->pa_commands[i]->args >> 8 & 0xff,
		p_game_obj->pa_commands[i]->change_carry,
		p_game_obj->pa_commands[i]->type_byte,
		p_game_obj->pa_commands[i]->dir_size,
		p_game_obj->pa_commands[i]->waiting_time);
	p_game_obj->cw_arrange_units_on_field(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
