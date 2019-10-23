/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/23 20:23:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	corewar_t	*p_game_obj;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cwArenaObjInit(p_game_obj);
	p_game_obj->cwPlayerObjInit(p_game_obj, argc, argv);
	p_game_obj->cwCarriageObjInit(p_game_obj);
	p_game_obj->cwCommandObjInit(p_game_obj);
	p_game_obj->cwArrangeUnitsOnField(p_game_obj);
	p_game_obj->cwIntroducePlayers(p_game_obj);
	p_game_obj->cwStartGame(p_game_obj);
	p_game_obj->cwCongratulations(p_game_obj);
	p_game_obj->cwDestructor(&p_game_obj);
	return (CW_SUCCESS);
}
