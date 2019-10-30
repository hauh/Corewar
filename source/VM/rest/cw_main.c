/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 19:50:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	t_corewar	*p_game_obj;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_obj_init(p_game_obj);
	p_game_obj->cw_player_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_carriage_obj_init(p_game_obj);
	p_game_obj->cw_command_obj_init(p_game_obj);
	p_game_obj->cw_arrange_units_on_field(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	ft_printf("%032b\n", p_game_obj->test);
	p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
