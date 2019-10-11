/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/11 20:00:37 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwConversionIntToBytes(unsigned char *buffer, int *from, int bias)
{
	ft_memset(buffer, 0, CW_REG_SIZE);
	//while (bias < REG_SIZE)
	//{
	//	buffer[bias] = (*from << (bias * 8)) >> 24;
	//	++bias;
	//}
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

void	cwReadFromRegToBuf(carriage_t *pCarriageInstance, unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	ft_memset(buffer, 0, CW_REG_SIZE);
	while (bias < CW_REG_SIZE)
	{
		buffer[bias] = registers[bias + ((reg_num - 1) * CW_REG_SIZE)];
		++bias;
	}
}

void	cwReadFromArenaToBuf(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	//ft_memset(buffer, 0, REG_SIZE);
	//while (bias < REG_SIZE)
	//	buffer[bias++] = field[data_location++];
	;
}

void	cwWriteFromBufToReg(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	//while (bias < REG_SIZE)
	//{
	//	registers[bias + ((reg_num - 1) * REG_SIZE)] = buffer[bias];
	//	++bias;
	//}
	;
}

void	cwWriteFromBufToArena(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	//while (bias < REG_SIZE)
	//	field[data_location++] = buffer[bias++];
	;
}

void		cwWriteOperation(corewar_t *game, buffer_t *buffer, int idx_mod, int input_arg)
{
	int		save_point;

	if (input_arg == CW_REG_CODE)
	{
		if (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] > 0 && CW_GAME_ARENA[CW_CARRIAGE_LOCATION] < 17)
			CW_REQUESTING_REGISTER = CW_GAME_ARENA[CW_CARRIAGE_LOCATION];
		else
			cwErrorCatcher(CW_CHEAT_DETECT, CW_EXEC_ERROR);
		cwWriteFromBufToReg(buffer->data, CW_CARRIAGE_REGISTERS, CW_REQUESTING_REGISTER, CW_INT_BIAS);
		CW_CARRIAGE_LOCATION += CW_REGISTER_SIZE;
	}
	else if (input_arg == CW_DIR_CODE)
	{
		cwWriteFromBufToReg(buffer->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, CW_DYNAMIC_SIZE_DIR);
		CW_CARRIAGE_LOCATION += CW_CURRENT_COMMAND->dir_size;
	}
	else if (input_arg == CW_IND_CODE)
	{
		save_point = CW_CARRIAGE_LOCATION;
		cwReadFromArenaToBuf(CW_BUFFER_SET[CW_SYSTEM_BUF]->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, CW_SHORT_BIAS);
		cwConversionBytesToInt(CW_BUFFER_SET[CW_SYSTEM_BUF]->data, &CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value, CW_SHORT_BIAS, CW_SHORT);
		if (idx_mod == TRUE)
			CW_CARRIAGE_LOCATION = (CW_CARRIAGE_SAVE_POINT + (CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value % IDX_MOD)) % MEM_SIZE;
		else
			CW_CARRIAGE_LOCATION = (CW_CARRIAGE_SAVE_POINT + CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value) % MEM_SIZE;
		if (CW_CARRIAGE_LOCATION < 0)
			CW_CARRIAGE_LOCATION = MEM_SIZE + CW_CARRIAGE_LOCATION;
		cwWriteFromBufToArena(buffer->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, 0);
		CW_CARRIAGE_LOCATION = save_point + CW_IND_SIZE;
	}
}

void		cwReadOperation(carriage_t *pCarraigeInstance, arena_t *pArenaObject, buffer_t *pBufferObject, int whereTo, int inputArg)
{
	if (whereTo == CW_ON_FIELD)
	{
		if (inputArg == CW_REG_CODE)
		{
			if (pArenaObject->pField[pCarraigeInstance->currentLocation] > 0 && pArenaObject->pField[pCarraigeInstance->currentLocation] < 17)
				pCarraigeInstance->currentRegister = pArenaObject->pField[pCarraigeInstance->currentLocation];
			else
				pCarraigeInstance->errorOcurred = CW_TRUE;
			pCarraigeInstance->cwReadFromRegToBuf()
			cwConversionBytesToInt(buffer->data, &buffer->int_value, CW_INT_BIAS, CW_INT);
			CW_CARRIAGE_LOCATION += CW_REGISTER_SIZE;
		}
		else if (inputArg == CW_DIR_CODE)
		{
			cwReadFromArenaToBuf(buffer->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, CW_DYNAMIC_SIZE_DIR);
			if (CW_CURRENT_COMMAND->dir_size == SHORT_DIR_SIZE)
				cwConversionBytesToInt(buffer->data, &buffer->short_value, CW_SHORT_BIAS, CW_SHORT);
			else
				cwConversionBytesToInt(buffer->data, &buffer->int_value, CW_INT_BIAS, CW_INT);
			CW_CARRIAGE_LOCATION += CW_CURRENT_COMMAND->dir_size;
		}
		else if (inputArg == CW_IND_CODE)
		{
			cwReadFromArenaToBuf(CW_BUFFER_SET[CW_SYSTEM_BUF]->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, CW_SHORT_BIAS);
			cwConversionBytesToInt(CW_BUFFER_SET[CW_SYSTEM_BUF]->data, &CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value, CW_SHORT_BIAS, CW_SHORT);
			if (idx_mod == CW_TRUE)
				CW_CARRIAGE_LOCATION = (CW_CARRIAGE_SAVE_POINT + (CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value % IDX_MOD)) % MEM_SIZE;
			else
				CW_CARRIAGE_LOCATION = (CW_CARRIAGE_SAVE_POINT + CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value) % MEM_SIZE;
			if (CW_CARRIAGE_LOCATION < 0)
				CW_CARRIAGE_LOCATION = MEM_SIZE + CW_CARRIAGE_LOCATION;
			cwReadFromArenaToBuf(buffer->data, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, 0);
			cwConversionBytesToInt(buffer->data, &buffer->int_value, CW_SHORT_BIAS, CW_SHORT);
			CW_CARRIAGE_LOCATION = save_point + CW_IND_SIZE;
		}
	}
	else if (whereTo == CW_ON_REGISTER)
	{

	}
}

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
		carraigeInstance->errorOcurred = CW_TRUE;
}

void			cwExecCommand(carriage_t *carriageInstance, corewar_t *gameInstance)
{
	if (carriageInstance->pCurrentCommand)
		carriageInstance->pCurrentCommand->cwCallback(gameInstance);
	else
		carriageInstance->errorOcurred = CW_TRUE;
}

void			cwSetCommandTime(carriage_t *pCarriageInstance, arena_t *pArenaInstance)
{
	if (pArenaInstance->pField[pCarriageInstance->currentLocation] > 0 && pArenaInstance->pField[pCarriageInstance->currentLocation] < 17)
	{
		pCarriageInstance->pCurrentCommand	= pCarriageInstance->ppCommandContainer[pArenaInstance->pField[pCarriageInstance->currentLocation]];
		pCarriageInstance->waitingTime		= pCarriageInstance->pCurrentCommand->waitingTime;
		pCarriageInstance->offset			= pCarriageInstance->pCurrentCommand->typeByte;
	}
	else
		pCarriageInstance->errorOcurred		= CW_TRUE;
}

static void cwMoveTo(carriage_t *pCarraigeInstance, int distance)
{
	pCarraigeInstance->currentLocation = (pCarraigeInstance->currentLocation + distance) % MEM_SIZE;
	if (pCarraigeInstance->currentLocation < 0)
		pCarraigeInstance->currentLocation = MEM_SIZE + pCarraigeInstance->currentLocation;
}

static void	cwComputeJump(carriage_t *pCarriageInstance)
{
	pCarriageInstance->jump = pCarriageInstance->currentLocation - pCarriageInstance->savePoint;
}

static void	cwSavePos(carriage_t *carriageInstance)
{
	carriageInstance->savePoint = carriageInstance->currentLocation;
}























/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructorCarriage(carriage_t **ppCarriageInstance)
{
	if (!((*ppCarriageInstance)->pRegisters = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset((*ppCarriageInstance)->pRegisters, 0, REG_NUMBER * CW_REG_SIZE);
	(*ppCarriageInstance)->jump				= 0;
	(*ppCarriageInstance)->carry			= CW_FALSE;
	(*ppCarriageInstance)->offset			= 0;
	(*ppCarriageInstance)->waitingTime		= 0;
	(*ppCarriageInstance)->lastSpeakCycle	= 0;
	(*ppCarriageInstance)->currentLocation 	= 0;
	(*ppCarriageInstance)->pCurrentCommand	= NULL;
	(*ppCarriageInstance)->pOwnerCarriage	= NULL;
	(*ppCarriageInstance)->pNext			= NULL;
	(*ppCarriageInstance)->pPrev			= NULL;
}

static void	cwDestructorCarriage(carriage_t **ppCarriageInstance)
{
	free((*ppCarriageInstance)->pRegisters);
	free((*ppCarriageInstance));
	*ppCarriageInstance = NULL;
}

void	cwCreateInstanceCarriage(carriage_t **ppCarriageObj)
{
	if (!(*ppCarriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*ppCarriageObj)->cwConstructorCarriage	= (const void *)&cwConstructorCarriage;
	(*ppCarriageObj)->cwDestructorCarriage	= (const void *)&cwDestructorCarriage;
	(*ppCarriageObj)->cwSavePos				= (const void *)&cwSavePos;
	(*ppCarriageObj)->cwMoveTo				= (const void *)&cwMoveTo;
	//(*ppCarriageObj)->cwParseTypes		= &cwParseTypes;
	(*ppCarriageObj)->cwComputeJump			= (const void *)&cwComputeJump;
	(*ppCarriageObj)->cwExecCommand			= (const void *)&cwExecCommand;
	//(*ppCarriageObj)->cwValidateTypes		= &cwValidateTypes;
	//(*ppCarriageObj)->cwReadOperation		= &cwReadOperation;
	//(*ppCarriageObj)->cwWriteOperation	= &cwWriteOperation;
	(*ppCarriageObj)->cwSetCommandTime		= (const void *)&cwSetCommandTime;
	(*ppCarriageObj)->cwReduceWaitingTime	= (const void *)&cwReduceWaitingTime;
}

/*
**--------------------------------------------------------------------------------------
*/