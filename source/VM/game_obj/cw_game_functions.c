/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 16:02:09 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_arrange_units_on_field(t_corewar *p_game_instance)
{
	int		iter;
	int		playerLocation;
	int		memoryStep;
	int		codeIter;

	memoryStep = MEM_SIZE / p_game_instance->players_amount;
	iter = CW_BEGIN_FROM_ZERO;
	while (iter < p_game_instance->carriages_amount)
	{
		p_game_instance->p_carriage_obj	= p_game_instance->p_carriage_obj->p_prev;
		codeIter = CW_BEGIN_FROM_ZERO;
		playerLocation = memoryStep * iter;
		p_game_instance->p_carriage_obj->current_location = playerLocation;
		while (playerLocation < memoryStep * iter + CHAMP_MAX_SIZE)
			p_game_instance->p_arena_obj->p_field[playerLocation++] = p_game_instance->p_carriage_obj->p_owner->p_code[codeIter++];
		++iter;
	}
}

static void	cw_congratulations(t_corewar *p_game_instance)
{
	if (p_game_instance->visualizator)
		cr_vis_winner(p_game_instance);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		p_game_instance->p_arena_obj->p_last_survivor->id,
		p_game_instance->p_arena_obj->p_last_survivor->p_name);
}

static void	cw_introduce_players(t_corewar *gameInstance)
{
	int		iter;

	iter = CW_BEGIN_FROM_ZERO;
	ft_printf("Introducing contestants...\n");
	while (iter < gameInstance->carriages_amount)
	{
		gameInstance->p_carriage_obj = gameInstance->p_carriage_obj->p_prev;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		gameInstance->p_carriage_obj->p_owner->id,
		gameInstance->p_carriage_obj->p_owner->code_size,
		gameInstance->p_carriage_obj->p_owner->p_name,
		gameInstance->p_carriage_obj->p_owner->p_comment);
		++iter;
	}
}

static void	cw_free_all_commands(t_corewar *p_game_instance)
{
	int		iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		p_game_instance->pa_commands[iter]->cw_destructor(&p_game_instance->pa_commands[iter]);
		++iter;
	}
}

static void	cw_free_all_carriages(t_corewar *p_game_instance)
{
	t_carriage *c1;
	t_carriage *c2;

	if (p_game_instance->p_carriage_obj)
	{
		c1 = p_game_instance->p_carriage_obj;
		c2 = c2->p_next;
		while (c2 != p_game_instance->p_carriage_obj)
		{
			c2 = c1->p_next;
			c1->cw_destructor(&c1);
			c1 = c2;
		}
	}
}

static void	cw_free_all_players(t_corewar *p_game_instance)
{
	t_player *p1;
	t_player *p2;

	p1 = p_game_instance->p_player_obj;
	p2 = p_game_instance->p_player_obj->p_next;
	while (p2 != p_game_instance->p_player_obj)
	{
		p2 = p1->p_next;
		p1->cw_destructor(&p1);
		p1 = p2;
	}
}

static void	cw_add_t_carriageo_list(t_corewar *p_game_instance, t_carriage *pCarriageAdding, int ascending)
{
	if (!p_game_instance->p_carriage_obj)
	{
		p_game_instance->p_carriage_obj	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_next	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_prev	= pCarriageAdding;
	}
	else
	{
		pCarriageAdding->p_next							= p_game_instance->p_carriage_obj;
		pCarriageAdding->p_prev							= p_game_instance->p_carriage_obj->p_prev;
		p_game_instance->p_carriage_obj->p_prev->p_next	= pCarriageAdding;
		p_game_instance->p_carriage_obj->p_prev			= pCarriageAdding;
		if (!ascending)
			p_game_instance->p_carriage_obj = pCarriageAdding;
	}
}

static void	cw_add_player_to_list(t_corewar *p_game_instance, t_player *pPlayerAdding)
{
	if (!p_game_instance->p_player_obj)
	{
		p_game_instance->p_player_obj		 = pPlayerAdding;
		p_game_instance->p_player_obj->p_next = pPlayerAdding;
		p_game_instance->p_player_obj->p_prev = pPlayerAdding;
	}
	else
	{
		pPlayerAdding->p_next					= p_game_instance->p_player_obj;
		pPlayerAdding->p_prev					= p_game_instance->p_player_obj->p_prev;
		p_game_instance->p_player_obj->p_prev->p_next	= pPlayerAdding;
		p_game_instance->p_player_obj->p_prev		= pPlayerAdding;
	}
}

extern void	cw_game_functions_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_arrange_units_on_field	= cw_arrange_units_on_field;
	p_game_instance->cw_add_carriage_to_list	= cw_add_t_carriageo_list;
	p_game_instance->cw_free_all_commands		= cw_free_all_commands;
	p_game_instance->cw_free_all_players		= cw_free_all_players;
	p_game_instance->cw_add_player_to_list		= cw_add_player_to_list;
	p_game_instance->cw_free_all_carriages		= cw_free_all_carriages;
	p_game_instance->cw_introduce_players		= cw_introduce_players;
	p_game_instance->cw_congratulations			= cw_congratulations;
}
