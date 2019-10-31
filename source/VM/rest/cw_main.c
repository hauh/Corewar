/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/10/31 16:25:48 by vrichese         ###   ########.fr       */
=======
/*   Updated: 2019/10/31 15:27:16 by dbrady           ###   ########.fr       */
>>>>>>> 21cde07fe462407a92572315aae4f6409d13b1d1
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
<<<<<<< HEAD
	p_game_obj->cw_congratulations(p_game_obj);
	ft_printf("%032b\n", p_game_obj->test);
=======
	cr_vis_winner(p_game_obj);
	// p_game_obj->cw_congratulations(p_game_obj);
	// ft_printf("%d\n", p_game_obj->p_arena_obj->cycle_amount);
>>>>>>> 21cde07fe462407a92572315aae4f6409d13b1d1
	p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
