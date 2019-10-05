/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/04 20:01:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cwComputeJump(carriage_t *carriageInstance)
{
	carriageInstance->jump = carriageInstance->currentLocation - carriageInstance->savePoint;
}

void			cwSavePos(carriage_t *carriageInstance)
{
	carriageInstance->savePoint = carriageInstance->currentLocation;
}

void			cwMoveTo(carriage_t *carriageInstance, int step)
{
	carriageInstance->currentLocation += step;
}

void			cwTypeHandler(carriage_t *carriageInstance, unsigned char *field)
{
	if (carriageInstance->currentCommand->availability_types)
	{
		carriageInstance->currentCommand->first_arg		= (field[carriageInstance->currentLocation] & 0xc0) >> 6;
		carriageInstance->currentCommand->second_arg	= (field[carriageInstance->currentLocation] & 0x30) >> 4;
		carriageInstance->currentCommand->third_arg		= (field[carriageInstance->currentLocation] & 0x0c) >> 2;
	}
	else
	{
		carriageInstance->currentCommand->first_arg		= CW_DIR_CODE;
		carriageInstance->currentCommand->second_arg	= CW_FALSE;
		carriageInstance->currentCommand->third_arg		= CW_FALSE;
	}
}


void			cwReduceWaitingTime(carriage_t *carraigeInstance)
{
	carraigeInstance->waitingTime -= 1;
	if (carraigeInstance->waitingTime < 0)
		cwErrorCatcher(CW_KERNEL_ERROR, CW_CARRIAGE);
}

void			cwExecCommand(corewar_t *game)
{
	if (CW_currentCommand)
	{
		CW_currentCommand->call(game);
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
		CW_currentCommand	= game->commands[CW_GAME_ARENA[CW_CARRIAGE_LOCATION]];
		CW_WAITING_TIME		= CW_currentCommand->waiting_time;
	}
	else
		CW_currentCommand = NULL;
}

void	cwDestructorCarriage(carriage_t *carriageInstance)
{
	free(carriageInstance->registers);
	free(carriageInstance);
}

void	cwConstructorCarriage(carriage_t *carriageInstance)
{
	if (!(carriageInstance->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset(carriageInstance->registers, 0, REG_NUMBER * REG_SIZE);
	carriageInstance->jump				= CW_FALSE;
	carriageInstance->carry				= CW_FALSE;
	carriageInstance->waitingTime		= CW_FALSE;
	carriageInstance->currentCommand	= NULL;
	carriageInstance->lastSpeakCycle	= CW_FALSE;
	carriageInstance->currentLocation 	= CW_FALSE;
}

void	cwCreateInstanceCarriage(carriage_t **carriageObj)
{
	if (!(*carriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*carriageObj)->cwConstructorCarriage	= &cwConstructorCarriage;
	(*carriageObj)->cwDestructorCarriage	= &cwDestructorCarriage;
}