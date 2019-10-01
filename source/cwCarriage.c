/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 17:17:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** In this file we are continue to initialization of game part. These functions
** need to handle and attach every players to carraige. Cause every players must
** have one(ore more) carriage at least in the beginning. List for storage carriages
** very similiar(or same) with players list and it biconnected and looped too(convenience :))
*/

void			cwInitializationCarriage(corewar_t *game, player_t *owner)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	new_carriage->id					= ++game->carriages_amount;
	new_carriage->jump					= CW_FALSE;
	new_carriage->owner					= owner;
	new_carriage->carry					= CW_FALSE;
	new_carriage->last_cycle			= CW_FALSE;
	new_carriage->waiting_time			= CW_FALSE;
	new_carriage->error_occured			= CW_FALSE;
	new_carriage->current_command		= NULL;
	new_carriage->current_location 		= CW_FALSE;
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

void			cwInitializationCarriages(corewar_t *game)
{
	int			iter;
	int			owner_id;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < game->players_amount)
	{
		owner_id = -game->players->id;
		cwInitializationCarriage(game, game->players);
		cwConversionIntToBytes(game->carriages->prev->registers, &owner_id, 0);
		game->players = game->players->next;
		++iter;
	}
	game->destructor->carriages_detect = CW_TRUE;
}