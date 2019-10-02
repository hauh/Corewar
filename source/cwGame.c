/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGame.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/02 18:53:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	delete_carriage(corewar_t *game)
{
	--game->carriages_amount;
	if (game->carriages->next == game->carriages)
		game->carriages = NULL;
	else
	{
		if (game->carriages == game->arena->last_carriage)
		{
			game->arena->last_carriage = game->carriages;
			game->arena->last_carriage = game->carriages->prev;
		}
		game->carriages->prev->next = game->carriages->next;
		game->carriages->next->prev = game->carriages->prev;
		game->carriages = game->carriages->next;
	}
}

void		start_checking(corewar_t *game)
{
	int		iter;

	iter = 0;
	while (iter < game->carriages_amount)
	{
		if (game->arena->cycle_amount - game->carriages->last_cycle >= game->arena->cycle_to_die || game->arena->cycle_to_die <= 0)
			delete_carriage(game);
		if (game->carriages)
			game->carriages = game->carriages->prev;
		++iter;
	}
	if (game->arena->live_amount >= NBR_LIVE)
	{
		game->arena->cycle_to_die -= CYCLE_DELTA;
		game->arena->check_amount = 0;
	}
	else
		++game->arena->check_amount;
	if (game->arena->check_amount >= MAX_CHECKS)
	{
		game->arena->check_amount = 0;
		game->arena->cycle_to_die -= CYCLE_DELTA;
	}
	game->arena->live_amount = 0;
}

void			cwReduceWaitingTime(corewar_t *game)
{
	CW_WAITING_TIME -= 1;
	CW_WAITING_TIME < 0 ? cwErrorCatcher(CW_KERNEL_ERROR, CW_CARRIAGE) : CW_FALSE;
}

void			cwExecCommand(corewar_t *game)
{
	logging(game, 0);
	CW_CURRENT_COMMAND->function(game);
	CW_CARRIAGE_LOCATION = (CW_CARRIAGE_LOCATION + game->carriages->jump) % MEM_SIZE;
	if (CW_CARRIAGE_LOCATION < 0)
		CW_CARRIAGE_LOCATION = MEM_SIZE + CW_CARRIAGE_LOCATION;
	logging(game, 1);
}

void			cwSetCommand(corewar_t *game)
{
	if (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] > 0 && CW_GAME_ARENA[CW_CARRIAGE_LOCATION] < 17)
	{
		CW_CURRENT_COMMAND		= game->commands[CW_GAME_ARENA[CW_CARRIAGE_LOCATION]];
		CW_WAITING_TIME			= CW_CURRENT_COMMAND->waiting_time;
	}
	else
	{
		CW_CARRIAGE_LOCATION 	= (CW_CARRIAGE_LOCATION + 1) % MEM_SIZE;
		game->carriages->error_occured = CW_TRUE;
	}
}

void		cwHereWeGo(corewar_t *game)
{
	int		carriage_iter;

	while (game->carriages)
	{
		carriage_iter = 0;
		while (carriage_iter < game->carriages_amount)
		{
			if (!game->carriages->waiting_time)
				cwSetCommand(game);
			if (game->carriages->error_occured == CW_TRUE)
			{
				game->carriages->error_occured = CW_FALSE;
				continue;
			}
			if (game->carriages->waiting_time)
				cwReduceWaitingTime(game);
			if (!game->carriages->waiting_time)
				cwExecCommand(game);
			game->carriages = game->carriages->prev;
			++carriage_iter;
		}
		++game->arena->cycle_amount;
 		if (game->arena->cycle_to_die <= 0 || !(game->arena->cycle_amount % game->arena->cycle_to_die))
 			start_checking(game);
	}
 	printf("Player %s under number %d is WINNER!!!\n", game->arena->last_survivor->name, game->arena->last_survivor->id);
}