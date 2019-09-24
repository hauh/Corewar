/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_on.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 17:30:06 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				compute_sum(char target, int trim_byte)
{
	int total;
	int iter;

	total = 2;
	iter = 4;
	while (iter >= 0)
	{
		if (target & (REG_CODE << iter))
			total += 1;
		else if (target & (DIR_CODE << iter))
			trim_byte ? total += 2 : (total += 4);
		else if (target & (IND_CODE << iter))
			total += 2;
		iter -= 2;
	}
	return (total);
}

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

void			start_checking(corewar_t *game)
{
	int			iter;

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

void			here_we_go(corewar_t *game)
{
	int			iter;

	while (TRUE)
	{
		iter = 0;
		while (iter < game->carriages_amount)
		{
			if (!game->carriages->waiting_time)
			{
				if (game->arena->field[game->carriages->current_location] > 0 && game->arena->field[game->carriages->current_location] < 17)
					game->carriages->current_command = game->commands[game->arena->field[game->carriages->current_location]];
				else
				{
					game->carriages->current_location = (game->carriages->current_location + 1) % MEM_SIZE;
					continue;
				}
				game->carriages->waiting_time = game->carriages->current_command->waiting_time;
			}
			if (game->carriages->waiting_time)
				--game->carriages->waiting_time;
			if (!game->carriages->waiting_time)
			{
				game->carriages->current_command->function(game);
				game->carriages->current_location = (game->carriages->current_location + game->carriages->jump) % MEM_SIZE;
			}
			game->carriages = game->carriages->prev;
			++iter;
			//printf("Carriage_id: %d\n", game->carriages->id);
			//printf("Next_command_step: %d\n", game->carriages->jump);
			//printf("Current_location: %d\n", game->carriages->current_location);
			//printf("Value on this address: %d\n", game->arena->field[game->carriages->current_location]);
		}
		++game->arena->cycle_amount;
		if (game->arena->cycle_amount == 5000)
		{
			//system("clear");
			print_arena(game);
			//usleep(30000);
			exit(1);
		}
		if (!(game->arena->cycle_amount % game->arena->cycle_to_die) || game->arena->cycle_to_die <= 0)
			start_checking(game);
		if (!game->carriages)
		{
			printf("Player %s number %d is WIN!!!\n", game->arena->last_survivor->name, game->arena->last_survivor->id);
			break;
		}
	}
}