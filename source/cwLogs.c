/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwLogs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:27:58 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 18:05:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	logging(corewar_t *game, flag_t flag)
{
	char in;

	in = '0';
	if (flag == 0)
	{
		printf("Common information about game:\n     \
			live_amount: %d\n     \
			check_amount: %d\n     \
			cycle_to_die: %d\n     \
			cycle_amount: %d\n     \
			players_amount: %d\n     \
			carriages_amount: %d\n     \
			last_survivor: %d %s\n     \
			last_carriage: %d\n",
			game->arena->live_amount, game->arena->check_amount, game->arena->cycle_to_die,
			game->arena->cycle_amount, game->players_amount, game->carriages_amount,
			game->arena->last_survivor->id, game->arena->last_survivor->name,
			game->arena->last_carriage->id);
		printf("Current time information:\n     \
			current_command: %d\n     \
			carriage_location before: %d\n", game->carriages->current_command->id,
			game->carriages->current_location);
		cwPrintArena(game);
	}
	else if (flag == 1)
	{
		printf("carriage_location after: %d\n", game->carriages->current_location);
		cwPrintArena(game);
		while (in != '1')
			read(0, &in, 0);
	}
}