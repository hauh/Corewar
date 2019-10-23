/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/23 20:28:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObj)
{
	ft_printf("Live executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->pOwnerCarriage->id == pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue)
		pGameObj->pArenaObj->pLastSurvivor = pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->pCarriageObj->lastSpeakCycle = pGameObj->pArenaObj->cycleAmount;
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	ldExec(corewar_t *pGameObj)
{
	ft_printf("Ld executing now.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	stExec(corewar_t *pGameObj)
{
	ft_printf("St executing now.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	addExec(corewar_t *pGameObj)
{
	ft_printf("Add executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("Add left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue);
	ft_printf("Add left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("Add result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	subExec(corewar_t *pGameObj)
{
	ft_printf("Sub executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("sub left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue);
	ft_printf("sub left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("sub result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	andExec(corewar_t *pGameObj)
{
	ft_printf("And executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("and left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue);
	ft_printf("and left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("and result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	orExec(corewar_t *pGameObj)
{
	ft_printf("Or executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("or left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue);
	ft_printf("or left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("or result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	xorExec(corewar_t *pGameObj)
{
	ft_printf("Xor executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("Xor left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue);
	ft_printf("Xor left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("Xor result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	pGameObj->pCarriageObj->cwConversionValueToBytes(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObj->pCarriageObj->cwWriteOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3], pGameObj->pCarriageObj->thirdArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwCheckCarry	(pGameObj->pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	zjmpExec(corewar_t *pGameObj)
{
	ft_printf("Zjmp executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	if (pGameObj->pCarriageObj->carry)
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue - pGameObj->pCarriageObj->odometer);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	ldiExec(corewar_t *pGameObj)
{
	ft_printf("Ldi executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("Ldi left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue);
	ft_printf("Ldi right_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue);
	ft_printf("Ldi result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
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
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	stiExec(corewar_t *pGameObj)
{
	ft_printf("Sti executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("sti left_r: %d %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue);
	ft_printf("sti right_r: %d %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.shortValue, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
	ft_printf("Sti result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_SPARE_BUF]->sTypes.intValue);
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
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	forkExec(corewar_t *pGameObj)
{
	carriage_t *pCarriageObj;

	ft_printf("Fork executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	ft_printf("%d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue);
	cw_create_instance_carriage(&pCarriageObj);
	pGameObj->pCarriageObj->cwCopyReg(pGameObj->pCarriageObj, pCarriageObj);
	pCarriageObj->carry					= pGameObj->pCarriageObj->carry;
	pCarriageObj->lastSpeakCycle		= pGameObj->pCarriageObj->lastSpeakCycle;
	pCarriageObj->currentLocation		= (pGameObj->pCarriageObj->currentLocation + pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue % IDX_MOD) % MEM_SIZE;
	pCarriageObj->ppCommandContainer	= pGameObj->pCarriageObj->ppCommandContainer;
	pCarriageObj->pOwnerCarriage		= pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->cwPushToQueue(pGameObj, pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	lldExec(corewar_t *pGameObj)
{
	ft_printf("Lld executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	lldiExec(corewar_t *pGameObj)
{
	ft_printf("Lldi executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
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
	ft_printf("Lldi left_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue);
	ft_printf("Lldi right_r: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2]->sTypes.shortValue);
	ft_printf("Lldi result: %d\n", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue);
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
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	lforkExec(corewar_t *pGameObj)
{
	carriage_t *pCarriageObj;
	ft_printf("Lfork executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	cw_create_instance_carriage(&pCarriageObj);
	pGameObj->pCarriageObj->cwCopyReg(pGameObj->pCarriageObj, pCarriageObj);
	pCarriageObj->carry					= pGameObj->pCarriageObj->carry;
	pCarriageObj->lastSpeakCycle		= pGameObj->pCarriageObj->lastSpeakCycle;
	pCarriageObj->currentLocation		= (pGameObj->pCarriageObj->currentLocation + pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue % IDX_MOD) % MEM_SIZE;
	pCarriageObj->ppCommandContainer	= pGameObj->pCarriageObj->ppCommandContainer;
	pCarriageObj->pOwnerCarriage		= pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->cwPushToQueue(pGameObj, pCarriageObj);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}

void	affExec(corewar_t *pGameObj)
{
	ft_printf("Aff executing.../ | \\\n");
	ft_printf("Cycle: %d\n", pGameObj->pArenaObj->cycleAmount);
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	ft_printf("%c", pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.charValue);
	// pGameObj->pArenaObj->cwPrintField(pGameObj->pArenaObj);
}