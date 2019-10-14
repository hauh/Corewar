/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 19:00:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void cwWriteOwnerIdToReg(carriage_t *pSelfCarriage)
{
	int iter;

	iter = 0;
	while (iter < CW_REG_SIZE)
	{
		pSelfCarriage->pRegisters[iter] = (pSelfCarriage->pOwnerCarriage->id << (iter * 8)) >> 24;
		++iter;
	}
}

static void	cwCheckCarry(carriage_t *pCarriageInstance)
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

void	cwConversionValueToBytes(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->pData[type] = (pBufferObj->sTypes.intValue << (type * 8)) >> 24;
		++type;
	}
}

void	cwConversionBytesToValue(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
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

void		cwWriteOperation(carriage_t *pCarriageInstance, arena_t *pArenaObject, buffer_t *pBufferObject, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObject->pField[pCarriageInstance->currentLocation] > 0 && pArenaObject->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister		= pArenaObject->pField[pCarriageInstance->currentLocation];
		else
		{
			pCarriageInstance->errorOcurred			= CW_TRUE;
			return ;
		}
		pCarriageInstance->cwWriteFromBufToReg		(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->offset					= CW_REG_CODE_SIZE;
		pCarriageInstance->accumOffset				+= CW_REG_CODE_SIZE;
	}
	else if (inputArg == CW_DIR_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwWriteFromBufToArena	(pCarriageInstance, pBufferObject, pArenaObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->offset					= pCarriageInstance->pCurrentCommand->dirSize;
		pCarriageInstance->accumOffset				+= pCarriageInstance->pCurrentCommand->dirSize;
	}
	else if (inputArg == CW_IND_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_SHORT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_SHORT);
		if (pCarriageInstance->pCurrentCommand->id != CW_LLD)
			pBufferObject->sTypes.shortValue %= IDX_MOD;
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pCarriageInstance->currentLocation - pCarriageInstance->odometer + pBufferObject->sTypes.shortValue);
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwWriteFromBufToArena	(pCarriageInstance, pBufferObject, pArenaObject, CW_INT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwCarriageReturn			(pCarriageInstance);
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pCarriageInstance->accumOffset);
		pCarriageInstance->offset					= CW_IND_CODE_SIZE;
		pCarriageInstance->accumOffset				+= CW_IND_CODE_SIZE;
	}
}

void		cwReadOperation(carriage_t *pCarriageInstance, arena_t *pArenaObject, buffer_t *pBufferObject, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObject->pField[pCarriageInstance->currentLocation] > 0 && pArenaObject->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister		= pArenaObject->pField[pCarriageInstance->currentLocation];
		else
		{
			pCarriageInstance->errorOcurred			= CW_TRUE;
			return ;
		}
		pCarriageInstance->cwReadFromRegToBuf		(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->offset					= CW_REG_CODE_SIZE;
		pCarriageInstance->accumOffset				+= CW_REG_CODE_SIZE;
	}
	else if (inputArg == CW_DIR_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, 4 - pCarriageInstance->pCurrentCommand->dirSize);
		pCarriageInstance->offset					= pCarriageInstance->pCurrentCommand->dirSize;
		pCarriageInstance->accumOffset				+= pCarriageInstance->pCurrentCommand->dirSize;
	}
	else if (inputArg == CW_IND_CODE)
	{
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_SHORT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_SHORT);
		if (pCarriageInstance->pCurrentCommand->id != CW_LLD)
			pBufferObject->sTypes.shortValue %= IDX_MOD;
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pCarriageInstance->currentLocation - pCarriageInstance->odometer + pBufferObject->sTypes.shortValue);
		pBufferObject->sTypes.intValue				= pCarriageInstance->currentLocation;
		pCarriageInstance->cwReadFromArenaToBuf		(pCarriageInstance, pBufferObject, pArenaObject, CW_INT);
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObject, CW_INT);
		pCarriageInstance->cwCarriageReturn			(pCarriageInstance);
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pCarriageInstance->accumOffset);
		pCarriageInstance->offset					= CW_IND_CODE_SIZE;
		pCarriageInstance->accumOffset				+= CW_IND_CODE_SIZE;
	}
}

void		cwParseTypes(carriage_t *pCarriageInstance, arena_t *pArenaObj)
{
	int input;
	int reference;
	int i;

	if (pCarriageInstance->pCurrentCommand->typeByte)
	{
		input = pArenaObj->pField[pCarriageInstance->currentLocation] >> 6;
		if (pCarriageInstance->pCurrentCommand->firstArg && !((input << 2) & pCarriageInstance->pCurrentCommand->firstArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->firstArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->firstArg))
		{
			pCarriageInstance->errorOcurred = CW_TRUE;
			ft_printf("%08b\n%08b\n%x\n", input, pArenaObj->pField[pCarriageInstance->currentLocation], pArenaObj->pField[pCarriageInstance->currentLocation]);
			ft_printf("%d\n", pCarriageInstance->currentLocation);
			ft_printf("What1?\n");
			return ;
		}
		input = (pArenaObj->pField[pCarriageInstance->currentLocation] << 2) >> 6;
		if (pCarriageInstance->pCurrentCommand->secondArg && !((input << 2) & pCarriageInstance->pCurrentCommand->secondArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->secondArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->secondArg))
		{
			pCarriageInstance->errorOcurred = CW_TRUE;
			ft_printf("%08b\n%08b\n%x\n", input, pArenaObj->pField[pCarriageInstance->currentLocation], pArenaObj->pField[pCarriageInstance->currentLocation]);
			ft_printf("What2?\n");
			return ;
		}
		input = (pArenaObj->pField[pCarriageInstance->currentLocation] << 4) >> 6;
		if (pCarriageInstance->pCurrentCommand->thirdArg && !((input << 2) & pCarriageInstance->pCurrentCommand->thirdArg) && !((input << 4) & pCarriageInstance->pCurrentCommand->thirdArg) && !((input << 6) & pCarriageInstance->pCurrentCommand->thirdArg))
		{
			pCarriageInstance->errorOcurred = CW_TRUE;
			ft_printf("%08b\n%08b\n%x\n", input, pArenaObj->pField[pCarriageInstance->currentLocation], pArenaObj->pField[pCarriageInstance->currentLocation]);
			return;
		}
	}
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
	pCarriageInstance->offset		= pCarriageInstance->pCurrentCommand->typeByte;
	pCarriageInstance->accumOffset	+= pCarriageInstance->pCurrentCommand->typeByte;
}

static void cwCarriageReturn(carriage_t *pCarriageInstance)
{
	pCarriageInstance->currentLocation = pCarriageInstance->savePoint;
}

static void cwMoveTo(carriage_t *pCarraigeInstance, int distance)
{
	ft_printf("Before: %d\n", pCarraigeInstance->currentLocation);
	pCarraigeInstance->currentLocation		= (pCarraigeInstance->currentLocation + distance) % MEM_SIZE;
	if (pCarraigeInstance->currentLocation < 0)
		pCarraigeInstance->currentLocation	= MEM_SIZE + pCarraigeInstance->currentLocation;
	pCarraigeInstance->odometer += (distance % MEM_SIZE);
	ft_printf("After: %d\n", pCarraigeInstance->currentLocation);
}

static void	cwComputeJump(carriage_t *pCarriageInstance)
{
	pCarriageInstance->jump = pCarriageInstance->accumOffset;
}

static void	cwSavePos(carriage_t *pCarriageInstance)
{
	pCarriageInstance->savePoint = pCarriageInstance->currentLocation;
}

static void	cwReduceWaitingTime(carriage_t *pCarraigeInstance)
{
	pCarraigeInstance->waitingTime -= 1;
	if (pCarraigeInstance->waitingTime < 0)
		cwErrorCatcher(CW_NOT_ALLOCATED, "Error in time reduce\n");
}

static void	cwExecCommand(carriage_t *pCarriageInstance, corewar_t *pGameInstance)
{
	pCarriageInstance->pCurrentCommand->cwCallback(pGameInstance);
	if (pCarriageInstance->errorOcurred == CW_TRUE)
		cwErrorCatcher(CW_NOT_ALLOCATED, "Error ocured at the code, not good...\n");
	if (pCarriageInstance->pCurrentCommand->id != CW_ZJMP || !pCarriageInstance->carry)
		pCarriageInstance->cwMoveTo(pCarriageInstance, pCarriageInstance->jump);
	pCarriageInstance->pCurrentCommand = NULL;
}

static void	cwSetCommandTime(carriage_t *pCarriageInstance, arena_t *pArenaInstance)
{
	int		errorCount;

	errorCount = 0;
	while (pArenaInstance->pField[pCarriageInstance->currentLocation] < 1 || pArenaInstance->pField[pCarriageInstance->currentLocation] > 16)
	{
		pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		if (++errorCount > MEM_SIZE)
			cwErrorCatcher(CW_NOT_ALLOCATED, "Error occured while trying to find needed command, it just is'n\n");
	}
	pCarriageInstance->pCurrentCommand	= pCarriageInstance->ppCommandContainer[pArenaInstance->pField[pCarriageInstance->currentLocation]];
	pCarriageInstance->waitingTime		= pCarriageInstance->pCurrentCommand->waitingTime;
	pCarriageInstance->offset			= 1;
	pCarriageInstance->accumOffset		= 1;
	pCarriageInstance->odometer			= 0;
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructor(carriage_t **ppCarriageInstance)
{
	if (!((*ppCarriageInstance)->pRegisters = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset((*ppCarriageInstance)->pRegisters, 0, REG_NUMBER * CW_REG_SIZE);
	(*ppCarriageInstance)->id					= 0;
	(*ppCarriageInstance)->jump					= 0;
	(*ppCarriageInstance)->carry				= CW_FALSE;
	(*ppCarriageInstance)->offset				= 0;
	(*ppCarriageInstance)->waitingTime			= 0;
	(*ppCarriageInstance)->lastSpeakCycle		= 0;
	(*ppCarriageInstance)->currentLocation 		= 0;
	(*ppCarriageInstance)->firstArg				= 0;
	(*ppCarriageInstance)->secondArg			= 0;
	(*ppCarriageInstance)->thirdArg				= 0;
	(*ppCarriageInstance)->odometer				= 0;
	(*ppCarriageInstance)->accumOffset			= 0;
	(*ppCarriageInstance)->pCurrentCommand		= NULL;
	(*ppCarriageInstance)->pOwnerCarriage		= NULL;
	(*ppCarriageInstance)->pNext				= NULL;
	(*ppCarriageInstance)->pPrev				= NULL;
}

static void	cwDestructor(carriage_t **ppCarriageInstance)
{
	free((*ppCarriageInstance)->pRegisters);
	free((*ppCarriageInstance));
	*ppCarriageInstance = NULL;
}

void	cwCreateInstanceCarriage(carriage_t **ppCarriageObj)
{
	if (!(*ppCarriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*ppCarriageObj)->cwConstructor				= (const void *)&cwConstructor;
	(*ppCarriageObj)->cwDestructor				= (const void *)&cwDestructor;
	(*ppCarriageObj)->cwConversionValueToBytes	= (const void *)&cwConversionValueToBytes;
	(*ppCarriageObj)->cwConversionBytesToValue	= (const void *)&cwConversionBytesToValue;
	(*ppCarriageObj)->cwReadFromRegToBuf		= (const void *)&cwReadFromRegToBuf;
	(*ppCarriageObj)->cwReadFromArenaToBuf		= (const void *)&cwReadFromArenaToBuf;
	(*ppCarriageObj)->cwWriteFromBufToReg		= (const void *)&cwWriteFromBufToReg;
	(*ppCarriageObj)->cwWriteFromBufToArena		= (const void *)&cwWriteFromBufToArena;
	(*ppCarriageObj)->cwReadOperation			= (const void *)&cwReadOperation;
	(*ppCarriageObj)->cwWriteOperation			= (const void *)&cwWriteOperation;
	(*ppCarriageObj)->cwParseTypes				= (const void *)&cwParseTypes;
	(*ppCarriageObj)->cwCheckCarry				= (const void *)&cwCheckCarry;
	(*ppCarriageObj)->cwComputeJump				= (const void *)&cwComputeJump;
	(*ppCarriageObj)->cwSavePos					= (const void *)&cwSavePos;
	(*ppCarriageObj)->cwMoveTo					= (const void *)&cwMoveTo;
	(*ppCarriageObj)->cwExecCommand				= (const void *)&cwExecCommand;
	(*ppCarriageObj)->cwSetCommandTime			= (const void *)&cwSetCommandTime;
	(*ppCarriageObj)->cwReduceTime				= (const void *)&cwReduceWaitingTime;
	(*ppCarriageObj)->cwWriteOwnerIdToReg		= (const void *)&cwWriteOwnerIdToReg;
	(*ppCarriageObj)->cwCarriageReturn			= (const void *)&cwCarriageReturn;
	(*ppCarriageObj)->cwConstructor				(ppCarriageObj);
}

/*
**--------------------------------------------------------------------------------------
*/