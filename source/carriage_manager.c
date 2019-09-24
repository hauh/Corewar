/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 21:03:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			initialization_carriage(corewar_t *game, player_t *owner)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	new_carriage->id					= ++game->carriages_amount;
	new_carriage->jump					= FALSE;
	new_carriage->owner					= owner;
	new_carriage->carry					= FALSE;
	new_carriage->last_cycle			= FALSE;
	new_carriage->waiting_time			= FALSE;
	new_carriage->error_occured			= FALSE;
	new_carriage->current_command		= NULL;
	new_carriage->current_location 		= FALSE;
	if (!game->carriages)
	{
		game->carriages = new_carriage;
		game->carriages->next = game->carriages;
		game->carriages->prev = game->carriages;
	}
	else
	{
		new_carriage->prev = game->carriages->prev;
		new_carriage->next = game->carriages;
		game->carriages->prev->next = new_carriage;
		game->carriages->prev =	new_carriage;
	}
}

void			initialization_carriages(corewar_t *game)
{
	int			iter;
	int			owner_id;

	iter = 0;
	while (iter < game->players_amount)
	{
		owner_id = game->players->id;
		initialization_carriage(game, game->players);
		cwConversionIntToBytes(game->carriages->prev->registers, &owner_id, 0);
		game->players = game->players->next;
		++iter;
	}
	game->destructor->carriages_detect = TRUE;
}