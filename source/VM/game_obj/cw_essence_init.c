/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_essence_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:39:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/31 16:33:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_command_obj_init(t_corewar *p_game_instance)
{
	t_command		*pCommandObj;
	int				iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cw_create_instance_command			(&pCommandObj);
		pCommandObj->cw_recognize	(pCommandObj, iter);
		p_game_instance->pa_commands[iter]	= pCommandObj;
		++iter;
	}
}

void		cw_carriage_obj_init(t_corewar *p_game_instance)
{
	t_carriage	*p_carriage_obj;
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_game_instance->players_amount)
	{
		cw_create_instance_carriage(&p_carriage_obj);
		p_carriage_obj->id = ++p_game_instance->carriages_amount;
		p_carriage_obj->pp_command_container = p_game_instance->pa_commands;
		p_carriage_obj->cw_set_owner(p_carriage_obj, p_game_instance->p_player_obj, p_game_instance->players_amount);
		p_carriage_obj->cw_write_owner_id_to_reg(p_carriage_obj);
		p_carriage_obj->game_ref = p_game_instance;
		p_game_instance->cw_add_carriage_to_list(p_game_instance, p_carriage_obj, 0);
		++iter;
	}
	p_game_instance->numerate_carriage = p_game_instance->carriages_amount;
	p_game_instance->p_arena_obj->p_last_survivor = p_game_instance->p_carriage_obj->p_prev->p_owner;
}

void		cw_queue_obj_init(t_corewar *p_game_instance)
{
	;
}

void		cw_stack_obj_init(t_corewar *p_game_instance)
{
	t_stack 	*stack;

	cw_create_instance_stack(&stack);
	p_game_instance->p_distribution_stack = stack;
}

void		cw_player_obj_init(t_corewar *p_game_instance, int argc, char **argv)
{
	t_player	*p_player_obj;
	int			standartId;
	int			customId;
	int			iter;
	int			busyByte;

	standartId	= 0;
	customId	= 0;
	busyByte	= CW_ALL_FREE;
	iter		= CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (*(argv[iter]) == CW_KEY)
		{
			while (*++(argv[iter]))
				if (*(argv[iter]) == 'n' && iter + 1 < argc)
					(customId = ft_atoi(argv[iter + 1])) < CW_MIN_PLAYERS
						|| (customId = ft_atoi(argv[iter + 1])) > CW_MAX_PLAYERS ?
							cw_error_catcher(CW_NOT_VALID_KEY, "Not valid number near -n") :
								CW_FALSE;
				else if (*(argv[iter]) == 'd' && iter + 1 < argc)
					(p_game_instance->load_dump = ft_atoi(argv[iter + 1])) < CW_MIN_DUMP_CYCLE ?
						cw_error_catcher(CW_NOT_VALID_KEY, "Not valid nubmer near -d") :
							CW_FALSE;
				else if (*(argv[iter]) == 's' && iter + 1 < argc)
					(p_game_instance->visual_cycle = ft_atoi(argv[iter + 1])) < CW_MIN_DUMP_CYCLE ?
						cw_error_catcher(CW_NOT_VALID_KEY, "Not valid nubmer near -s") :
							CW_FALSE;
				else if (*(argv[iter]) == 'v')
					p_game_instance->visualizator = CW_TRUE;
				else
					cw_error_catcher(CW_NOT_VALID_KEY, "Not that place");
			p_game_instance->load_dump || customId ? ++iter : CW_FALSE;
		}
		else if (++p_game_instance->players_amount)
		{
			cw_create_instance_player		(&p_player_obj);
			p_player_obj->cw_read_file		(p_player_obj, argv[iter]);
			p_player_obj->cw_self_build		(p_player_obj);
			p_player_obj->cw_self_validate	(p_player_obj);
			if (customId)
				p_player_obj->cw_set_id		(p_player_obj, &busyByte, customId, CW_TRUE);
			p_game_instance->cw_add_player_to_list(p_game_instance, p_player_obj);
			customId = 0;
		}
		++iter;
	}
	if (p_game_instance->players_amount < 1 || p_game_instance->players_amount > 4)
		cw_error_catcher(CW_INVALID_PLAYERS, CW_PLAYER);
	iter = 0;
	while (iter < p_game_instance->players_amount)
	{
		if (p_game_instance->p_player_obj->id == 0)
			p_game_instance->p_player_obj->cw_set_id(p_game_instance->p_player_obj, &busyByte, 1, CW_FALSE);
		p_game_instance->p_player_obj = p_game_instance->p_player_obj->p_next;
		++iter;
	}
}

void		cw_arena_obj_init(t_corewar *gameInstance)
{
	t_arena		*p_arena_obj;

	cw_create_instance_arena(&p_arena_obj);
	p_arena_obj->cw_buffer_init(p_arena_obj);
	gameInstance->p_arena_obj = p_arena_obj;
}