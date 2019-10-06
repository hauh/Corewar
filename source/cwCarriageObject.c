/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 17:58:54 by vrichese         ###   ########.fr       */
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
	if (carriageInstance->pCurrentCommand->typeByte)
	{
		carriageInstance->pCurrentCommand->firstArg		= (field[carriageInstance->currentLocation] & 0xc0) >> 6;
		carriageInstance->pCurrentCommand->secondArg	= (field[carriageInstance->currentLocation] & 0x30) >> 4;
		carriageInstance->pCurrentCommand->thirdArg		= (field[carriageInstance->currentLocation] & 0x0c) >> 2;
	}
	else
	{
		carriageInstance->pCurrentCommand->firstArg		= CW_DIR_CODE;
		carriageInstance->pCurrentCommand->secondArg	= CW_FALSE;
		carriageInstance->pCurrentCommand->thirdArg		= CW_FALSE;
	}
}


void			cwReduceWaitingTime(carriage_t *carraigeInstance)
{
	carraigeInstance->waitingTime -= 1;
	if (carraigeInstance->waitingTime < 0)
		carraigeInstance->errorOcurred;
}

void			cwExecCommand(carriage_t *carriageInstance, corewar_t *gameInstance)
{
	if (carriageInstance->pCurrentCommand)
		carriageInstance->pCurrentCommand->cwCallBack(gameInstance);
	else
		carriageInstance->errorOcurred = CW_TRUE;
}

void			cwSetCommand(carriage_t *carriageInstance, arena_t *arenaInstance)
{
	if (arenaInstance->field[carriageInstance->currentLocation] > 0 &&
		arenaInstance->field[carriageInstance->currentLocation] < 17)
		carriageInstance->pCurrentCommand = arenaInstance->field[carriageInstance->currentLocation];
	else
		carriageInstance->errorOcurred = CW_TRUE;
}

void	cwConstructorCarriage(carriage_t *carriageInstance)
{
	if (!(carriageInstance->pRegisters = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset(carriageInstance->pRegisters, 0, REG_NUMBER * CW_REG_SIZE);
	carriageInstance->jump				= 0;
	carriageInstance->carry				= CW_FALSE;
	carriageInstance->waitingTime		= 0;
	carriageInstance->lastSpeakCycle	= 0;
	carriageInstance->currentLocation 	= 0;
	carriageInstance->pCurrentCommand	= NULL;
	carriageInstance->pOwnerCarriage	= NULL;
	carriageInstance->pNext				= NULL;
	carriageInstance->pPrev				= NULL;
}

void	cwDestructorCarriage(carriage_t *carriageInstance)
{
	free(carriageInstance->pRegisters);
	free(carriageInstance);
}

void	cwCreateInstanceCarriage(carriage_t **carriageObj)
{
	if (!(*carriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*carriageObj)->cwConstructorCarriage	= &cwConstructorCarriage;
	(*carriageObj)->cwDestructorCarriage	= &cwDestructorCarriage;
}