/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_on.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:56:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/21 21:33:36 by vrichese         ###   ########.fr       */
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

void	delete_carriage(corewar_t *game, carriage_t **tmp)
{
	if (game->carriages)
	{
		if (game->carriages->prev)
		{
			if (game->carriages->next)
			{
				game->carriages->prev->next = game->carriages->next;
				game->carriages->next->prev = game->carriages->prev;
				game->carriages = game->carriages->next;
			}
			else
				game->carriages->prev->next = NULL;
		}
		else
		{
			if (game->carriages->next)
			{
				game->carriages = game->carriages->next;
				game->carriages->prev = NULL;
				*tmp = game->carriages;
			}
			else
			{
				game->carriages = NULL;
				*tmp = NULL;
			}
		}
	}
}

void			start_checking(corewar_t *game)
{
	carriage_t	*tmp;

	tmp = game->carriages;
	while (game->carriages)
	{
		if (game->arena->loop_amount - game->carriages->last_live_loop >= game->arena->cycle_to_die)
			delete_carriage(game, &tmp);
		if (game->arena->cycle_to_die <= 0)
			delete_carriage(game, &tmp);
		if (game->carriages)
			game->carriages = game->carriages->next;
	}
	if (game->arena->live_amount_in_ctd >= NBR_LIVE)
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
}

void			here_we_go(corewar_t *game)
{
	carriage_t	*tmp;

	while (TRUE)
	{
		tmp = game->carriages;
		if (!(game->arena->loop_amount % game->arena->cycle_to_die) || game->arena->cycle_to_die <= 0)
			start_checking(game);
		while (game->carriages)
		{
			if (!game->carriages->waiting_time)
			{
				game->carriages->current_command = game->commands[game->arena->field[game->carriages->current_location]];
				game->carriages->waiting_time = game->carriages->current_command->waiting_time;
			}
			if (game->carriages->waiting_time)
				--game->carriages->waiting_time;
			if (!game->carriages->waiting_time)
				game->carriages->current_command->function(game);
			game->carriages = game->carriages->next;
		}
		++game->arena->loop_amount;
		game->carriages = tmp;
		if (!game->carriages)
			break;
		usleep(100000);
		system("clear");
		print_arena(game);
	}
	exit(1);
}