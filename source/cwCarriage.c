/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/02 20:55:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cwComputJump(carriage_t *self_carriage)
{

}

void			cwSaveLocation(carriage_t *self_carriage)
{
	self_carriage->save_point = self_carriage->current_location;
}

void			cwMoveTo(carriage_t *self_carriage, int step)
{
	self_carriage->current_location += step;
}

void		cwTypeHandler(carriage_t *carriage, arena_t *arena)
{
	carriage->cwSaveLocation	(carriage);
	carriage->cwMoveTo			(carriage, carriage->current_command->availability_types);
	if (carriage->current_command->availability_types)
	{
		carriage->current_command->first_arg	= (arena->field[carriage->current_location] & 0xc0) >> 6;
		carriage->current_command->second_arg	= (arena->field[carriage->current_location] & 0x30) >> 4;
		carriage->current_command->third_arg	= (arena->field[carriage->current_location] & 0x0c) >> 2;
	}
	else
	{
		carriage->current_command->first_arg	= CW_DIR_CODE;
		carriage->current_command->second_arg	= CW_FALSE;
		carriage->current_command->third_arg	= CW_FALSE;
	}
	carriage->cwMoveTo			(carriage, )
}


void			cwReduceWaitingTime(corewar_t *game)
{
	CW_WAITING_TIME -= 1;
	CW_WAITING_TIME < 0 ? cwErrorCatcher(CW_KERNEL_ERROR, CW_CARRIAGE) : CW_FALSE;
}

void			cwExecCommand(corewar_t *game)
{
	if (CW_CURRENT_COMMAND)
	{
		CW_CURRENT_COMMAND->call(game);
		CW_CARRIAGE_LOCATION = (CW_CARRIAGE_LOCATION + game->carriages->jump) % MEM_SIZE;
		if (CW_CARRIAGE_LOCATION < 0)
			CW_CARRIAGE_LOCATION = MEM_SIZE + CW_CARRIAGE_LOCATION;
	}
	else
		CW_CARRIAGE_LOCATION = (CW_CARRIAGE_LOCATION + 1) % MEM_SIZE;
}

void			cwSetCommand(corewar_t *game)
{
	if (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] > 0 && CW_GAME_ARENA[CW_CARRIAGE_LOCATION] < 17)
	{
		CW_CURRENT_COMMAND	= game->commands[CW_GAME_ARENA[CW_CARRIAGE_LOCATION]];
		CW_WAITING_TIME		= CW_CURRENT_COMMAND->waiting_time;
	}
	else
		CW_CURRENT_COMMAND	= NULL;
}

void			cwInitializationCarriage(corewar_t *game, player_t *owner)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	new_carriage->id				= ++game->carriages_amount;
	new_carriage->jump				= CW_FALSE;
	new_carriage->owner				= owner;
	new_carriage->carry				= CW_FALSE;
	new_carriage->last_cycle		= CW_FALSE;
	new_carriage->waiting_time		= CW_FALSE;
	new_carriage->error_occured		= CW_FALSE;
	new_carriage->current_command	= NULL;
	new_carriage->current_location 	= CW_FALSE;
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