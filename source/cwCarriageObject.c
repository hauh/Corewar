/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 19:22:27 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwCopyReg(unsigned char *from, unsigned char *to, int size)
{
	int iter;

	iter = 0;
	while (iter < size)
	{
		to[iter] = from[iter];
		++iter;
	}
}

void	cwCheckCarry(unsigned char *registers, int *carry, int reg_num)
{
	int iter;

	iter = --reg_num * CW_REG_SIZE;
	while (iter < reg_num * CW_REG_SIZE + CW_REG_SIZE)
	{
		if (registers[iter] != 0)
		{
			*carry = 0;
			return ;
		}
		++iter;
	}
	*carry = 1;
}

void	cwConversionIntToBytes(unsigned char *buffer, int *from, int bias)
{
	ft_memset(buffer, 0, CW_REG_SIZE);
	while (bias < REG_SIZE)
	{
		buffer[bias] = (*from << (bias * 8)) >> 24;
		++bias;
	}
}

void	cwConversionBytesToInt(unsigned char *buffer, void *dest, int bias, int type)
{
	char 	*char_value;
	short 	*short_value;
	int		*int_value;

	if (type == CW_CHAR)
	{
		char_value = (char *)dest;
		*char_value = 0;
		while (bias < CW_REG_SIZE)
		{
			*char_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
	else if (type == CW_SHORT)
	{
		short_value = (short *)dest;
		*short_value = 0;
		while (bias < CW_REG_SIZE)
		{
			*short_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
	else if (type == CW_INT)
	{
		int_value = (int *)dest;
		*int_value = 0;
		while (bias < CW_REG_SIZE)
		{
			*int_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
}

void	cwReadFromRegToBuf(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	ft_memset(buffer, 0, CW_REG_SIZE);
	while (bias < CW_REG_SIZE)
	{
		buffer[bias] = registers[bias + ((reg_num - 1) * REG_SIZE)];
		++bias;
	}
}

void	cwReadFromArenaToBuf(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
		buffer[bias++] = field[data_location++];
}

void	cwWriteFromBufToReg(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	while (bias < REG_SIZE)
	{
		registers[bias + ((reg_num - 1) * REG_SIZE)] = buffer[bias];
		++bias;
	}
}

void	cwWriteFromBufToArena(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	while (bias < REG_SIZE)
		field[data_location++] = buffer[bias++];
}

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