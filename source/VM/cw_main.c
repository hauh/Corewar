/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/29 17:59:16 by vrichese         ###   ########.fr       */
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
	p_game_obj->cw_arrange_units_on_field(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}

// static void	cw_start_game(corewar_t *p_game_instance)
// {
// 	int		iter;

// 	while (p_game_instance->p_carriage_obj && ++p_game_instance->p_arena_obj->cycle_amount)
// 	{
// 		iter = CW_ITERATOR;
// 		// if (p_game_instance->p_arena_obj->cycle_amount == )
// 		// {
// 		// 	for (int i = 0; i < p_game_instance->carriages_amount; ++i, p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next)
// 		// 		if (p_game_instance->p_carriage_obj->p_current_command)
// 		// 			ft_printf("%d\n", p_game_instance->p_carriage_obj->p_current_command->id);
// 		// 	exit(1);
// 		// }
// 		while (++iter < p_game_instance->carriages_amount)
// 		{
// 			p_game_instance->p_carriage_obj->cw_set_command_time(p_game_instance->p_carriage_obj, p_game_instance->p_arena_obj);
// 			p_game_instance->p_carriage_obj->cw_reduce_time(p_game_instance->p_carriage_obj);
// 			p_game_instance->p_carriage_obj->cw_exec_command(p_game_instance->p_carriage_obj, p_game_instance);
// 			p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next;
// 		}
// 		p_game_instance->cw_merge_queue_to_list(p_game_instance);
// 		if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
// 			p_game_instance->cw_main_checking(p_game_instance);
// 		if (p_game_instance->load_dump == p_game_instance->p_arena_obj->cycle_amount)
// 			p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
// 	}
// }
