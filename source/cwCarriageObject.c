/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 18:19:19 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwCheckCarry(carriage_t *pCarriageInstance)
{
	int iter;

	iter = (pCarriageInstance->currentRegister - 1) * CW_REG_SIZE;
	while (iter < (pCarriageInstance->currentRegister - 1) * REG_NUMBER + CW_REG_SIZE)
	{
		if (pCarriageInstance->pRegisters[iter] != 0)
		{
			pCarriageInstance->carry = 0;
			return ;
		}
		++iter;
	}
	pCarriageInstance->carry = 1;
}

void	cwConversionIntToBytes(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->pData[type] = (pBufferObj->sTypes.intValue << (type * 8)) >> 24;
		++type;
	}
}

void	cwConversionBytesToInt(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	pBufferObj->sTypes.intValue = 0;
	while (type < CW_REG_SIZE)
	{
		pBufferObj->sTypes.intValue |= pBufferObj->pData[type] << ((3 - type) * 8);
		++type;
	}
}

void	cwReadFromRegToBuf(carriage_t *pCarriageInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->pData[type] = pCarriageInstance->pRegisters[type + ((pCarriageInstance->currentRegister - 1) * CW_REG_SIZE)];
		++type;
	}
}

void	cwReadFromArenaToBuf(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, arena_t *pArenaObj, int type)
{
	ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
		pBufferObj->pData[type++] = pArenaObj->pField[pBufferObj->sTypes.intValue++];
}

void	cwWriteFromBufToReg(carriage_t *pCarriageInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pCarriageInstance->pRegisters + (pCarriageInstance->currentRegister - 1), 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pCarriageInstance->pRegisters[type + ((pCarriageInstance->currentRegister - 1) * CW_REG_SIZE)] = pBufferObj->pData[type];
		++type;
	}
}

void	cwWriteFromBufToArena(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, arena_t *pArenaObj, int type)
{
	while (type < CW_REG_SIZE)
		pArenaObj->pField[pBufferObj->sTypes.intValue++] = pBufferObj->pData[type++];
}

void		cwWriteOperation(carriage_t *pCarriageInstance, arena_t *pArenaObject, buffer_t *pBufferObject, int inputArg, int idxMod)
{
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObject->pField[pCarriageInstance->currentLocation] > 0 && pArenaObject->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister = pArenaObject->pField[pCarriageInstance->currentLocation];
		else
			pCarriageInstance->errorOcurred = CW_TRUE;
		pCarriageInstance->cwReadFromRegToBuf		(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_INT);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
	}
	else if (inputArg == CW_IND_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_SHORT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_SHORT);
		if (idxMod)
			pBufferObject->sTypes.shortValue %= IDX_MOD;
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pBufferObject->sTypes.shortValue);
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_INT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_INT);
	}
}

void		cwReadOperation(carriage_t *pCarriageInstance, arena_t *pArenaObject, buffer_t *pBufferObject, int inputArg, int idxMod)
{
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObject->pField[pCarriageInstance->currentLocation] > 0 && pArenaObject->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister		= pArenaObject->pField[pCarriageInstance->currentLocation];
		else
			pCarriageInstance->errorOcurred			= CW_TRUE;
		pCarriageInstance->cwReadFromRegToBuf		(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_INT);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
	}
	else if (inputArg == CW_IND_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_SHORT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_SHORT);
		if (idxMod)
			pBufferObject->sTypes.shortValue %= IDX_MOD;
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pBufferObject->sTypes.shortValue);
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_INT);
		pCarriageInstance->cwConversionBytesToInt	(pCarriageInstance, pBufferObject, CW_INT);
	}
}

void		cwParseTypes(carriage_t *pCarriageInstance, arena_t *pArenaObj)
{
	int input;
	int reference;
	int i;

	input = pArenaObj->pField[pCarriageInstance->currentLocation] >> 6;
	if (!((input << 2) & pCarriageInstance->pCurrentCommand->firstArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->firstArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->firstArg))
		pCarriageInstance->errorOcurred = CW_TRUE;
	input = (pArenaObj->pField[pCarriageInstance->currentLocation] << 2) >> 6;
	if (!((input << 2) & pCarriageInstance->pCurrentCommand->secondArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->secondArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->secondArg))
		pCarriageInstance->errorOcurred = CW_TRUE;
	input = (pArenaObj->pField[pCarriageInstance->currentLocation] << 4) >> 6;
	if (!((input << 2) & pCarriageInstance->pCurrentCommand->thirdArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->thirdArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->thirdArg))
		pCarriageInstance->errorOcurred = CW_TRUE;
	if (pCarriageInstance->pCurrentCommand->typeByte)
	{
		pCarriageInstance->firstArg		= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0xc0) >> 6;
		pCarriageInstance->secondArg	= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0x30) >> 4;
		pCarriageInstance->thirdArg		= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0x0c) >> 2;
	}
	else
	{
		pCarriageInstance->firstArg		= CW_DIR_CODE;
		pCarriageInstance->secondArg	= CW_FALSE;
		pCarriageInstance->thirdArg		= CW_FALSE;
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

static void cwCarriageReturn(carriage_t *pCarriageInstance)
{
	pCarriageInstance->currentLocation = pCarriageInstance->savePoint;
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
	(*ppCarriageInstance)->firstArg			= 0;
	(*ppCarriageInstance)->secondArg		= 0;
	(*ppCarriageInstance)->thirdArg			= 0;
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
	(*ppCarriageObj)->cwConversionIntToBytes = (const void *)&cwConversionIntToBytes;
	(*ppCarriageObj)->cwConversionBytesToInt = (const void *)&cwConversionBytesToInt;
	(*ppCarriageObj)->cwReadFromRegToBuf	= (const void *)&cwReadFromRegToBuf;
	(*ppCarriageObj)->cwReadFromArenaToBuf	= (const void *)&cwReadFromArenaToBuf;
	(*ppCarriageObj)->cwWriteFromBufToReg	= (const void *)&cwWriteFromBufToReg;
	(*ppCarriageObj)->cwWriteFromBufToArena	= (const void *)&cwWriteFromBufToArena;
	(*ppCarriageObj)->cwReadOperation		= (const void *)&cwReadOperation;
	(*ppCarriageObj)->cwWriteOperation		= (const void *)&cwWriteOperation;
	(*ppCarriageObj)->cwParseTypes			= (const void *)&cwParseTypes;
	(*ppCarriageObj)->cwCheckCarry			= (const void *)&cwCheckCarry;
	(*ppCarriageObj)->cwComputeJump			= (const void *)&cwComputeJump;
	(*ppCarriageObj)->cwSavePos				= (const void *)&cwSavePos;
	(*ppCarriageObj)->cwMoveTo				= (const void *)&cwMoveTo;
	(*ppCarriageObj)->cwExecCommand			= (const void *)&cwExecCommand;
	(*ppCarriageObj)->cwSetCommandTime		= (const void *)&cwSetCommandTime;
	(*ppCarriageObj)->cwReduceWaitingTime	= (const void *)&cwReduceWaitingTime;
}

/*
**--------------------------------------------------------------------------------------
*/