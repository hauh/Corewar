/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/24 19:36:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (-pGameObj->pCarriageObj->pOwnerCarriage->id == pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue)
		pGameObj->pArenaObj->pLastSurvivor = pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->pCarriageObj->lastSpeakCycle = pGameObj->pArenaObj->cycleAmount;
	pGameObj->pArenaObj->liveAmount += 1;
}

void	ldExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry(pGameObj->pCarriageObj);
}

void	stExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
}

void	addExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue
																			+ pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	subExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue
																			- pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	andExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue
																			& pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	orExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue
																			| pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	xorExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue
																			^ pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	zjmpExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	if (pGameObj->pCarriageObj->carry)
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue - pGameObj->pCarriageObj->odometer);
}

void	ldiExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = ((pGameObj->pCarriageObj->firstArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue) + (pGameObj->pCarriageObj->secondArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue)) % IDX_MOD;
	pGameObj->pCarriageObj->cwSavePos(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue - pGameObj->pCarriageObj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i)
	{
		pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->pData[i] = pGameObj->pArenaObj->pField[pGameObj->pCarriageObj->currentLocation];
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, 1);
	}
	pGameObj->pCarriageObj->cwCarriageReturn(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
}

void	stiExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_SPARE_BUF]->sTypes.intValue = ((pGameObj->pCarriageObj->secondArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue) + (pGameObj->pCarriageObj->thirdArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue)) % IDX_MOD;
	pGameObj->pCarriageObj->cwSavePos(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_SPARE_BUF]->sTypes.intValue - pGameObj->pCarriageObj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i)
	{
		pGameObj->pArenaObj->pField[pGameObj->pCarriageObj->currentLocation] = pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->pData[i];
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, 1);
	}
	pGameObj->pCarriageObj->cwCarriageReturn(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
}

void	forkExec(corewar_t *pGameObj)
{
	carriage_t *pCarriageObj;

	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	cwCreateInstanceCarriage(&pCarriageObj);
	pGameObj->pCarriageObj->cwCopyReg(pGameObj->pCarriageObj, pCarriageObj);
	pCarriageObj->carry					= pGameObj->pCarriageObj->carry;
	pCarriageObj->lastSpeakCycle		= pGameObj->pCarriageObj->lastSpeakCycle;
	pCarriageObj->currentLocation		= (pGameObj->pCarriageObj->currentLocation + pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue % IDX_MOD) % MEM_SIZE;
	pCarriageObj->ppCommandContainer	= pGameObj->pCarriageObj->ppCommandContainer;
	pCarriageObj->pOwnerCarriage		= pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->cwPushToQueue(pGameObj, pCarriageObj);
}

void	lldExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
}

void	lldiExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = ((pGameObj->pCarriageObj->firstArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue) + (pGameObj->pCarriageObj->secondArg == CW_DIR_CODE ? pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue :
	pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue));
	pGameObj->pCarriageObj->cwSavePos(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue - pGameObj->pCarriageObj->odometer);
	for (int i = CW_INT; i < CW_REG_SIZE; ++i)
	{
		pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->pData[i] = pGameObj->pArenaObj->pField[pGameObj->pCarriageObj->currentLocation];
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, 1);
	}
	pGameObj->pCarriageObj->cwCarriageReturn(pGameObj->pCarriageObj, CW_ADDIT_SAVE);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
}

void	lforkExec(corewar_t *pGameObj)
{
	carriage_t *pCarriageObj;

	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	cwCreateInstanceCarriage(&pCarriageObj);
	pGameObj->pCarriageObj->cwCopyReg(pGameObj->pCarriageObj, pCarriageObj);
	pCarriageObj->carry					= pGameObj->pCarriageObj->carry;
	pCarriageObj->lastSpeakCycle		= pGameObj->pCarriageObj->lastSpeakCycle;
	pCarriageObj->currentLocation		= (pGameObj->pCarriageObj->currentLocation + pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue) % MEM_SIZE;
	pCarriageObj->ppCommandContainer	= pGameObj->pCarriageObj->ppCommandContainer;
	pCarriageObj->pOwnerCarriage		= pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->cwPushToQueue(pGameObj, pCarriageObj);
}

void	affExec(corewar_t *pGameObj)
{
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	ft_printf("%c", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.charValue);
}