/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 18:47:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObject)
{
	ft_printf("Live executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	if (pGameObject->pCarriageObject->id == pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue)
		pGameObject->pCarriageObject->lastSpeakCycle = pGameObject->pArenaObject->cycleAmount;
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	ldExec(corewar_t *pGameObject)
{
	ft_printf("Ld executing now.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwCarriageReturn	(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	stExec(corewar_t *pGameObject)
{
	ft_printf("St executing now.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwCarriageReturn	(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	addExec(corewar_t *pGameObject)
{
	ft_printf("Add executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue + pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObject->pCarriageObject->cwConversionValueToBytes(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], pGameObject->pCarriageObject->thirdArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	subExec(corewar_t *pGameObject)
{
	ft_printf("Sub executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue - pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObject->pCarriageObject->cwConversionValueToBytes(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], pGameObject->pCarriageObject->thirdArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	andExec(corewar_t *pGameObject)
{
	ft_printf("And executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue & pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObject->pCarriageObject->cwConversionValueToBytes(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], pGameObject->pCarriageObject->thirdArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	orExec(corewar_t *pGameObject)
{
	ft_printf("Or executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue | pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObject->pCarriageObject->cwConversionValueToBytes(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], pGameObject->pCarriageObject->thirdArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	xorExec(corewar_t *pGameObject)
{
	ft_printf("Xor executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2], pGameObject->pCarriageObject->secondArg);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3]->sTypes.intValue = pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue ^ pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_2]->sTypes.intValue;
	pGameObject->pCarriageObject->cwConversionValueToBytes(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], CW_INT);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_3], pGameObject->pCarriageObject->thirdArg);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	zjmpExec(corewar_t *pGameObject)
{
	ft_printf("Zjmp executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg);
	if (pGameObject->pCarriageObject->carry)
		pGameObject->pCarriageObject->cwMoveTo		(pGameObject->pCarriageObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	ldiExec(corewar_t *pGameObject)
{
	ft_printf("Ldi executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	stiExec(corewar_t *pGameObject)
{
	ft_printf("Sti executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	forkExec(corewar_t *pGameObject)
{
	ft_printf("Fork executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	lldExec(corewar_t *pGameObject)
{
	ft_printf("Lld executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	lldiExec(corewar_t *pGameObject)
{
	ft_printf("Lldi executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	lforkExec(corewar_t *pGameObject)
{
	ft_printf("Lfork executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}

void	affExec(corewar_t *pGameObject)
{
	ft_printf("Aff executing.../ | \\\n");
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject, pGameObject->pArenaObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	if (pGameObject->pCarriageObject->pCurrentCommand->changeCarry)
		pGameObject->pCarriageObject->cwCheckCarry(pGameObject->pCarriageObject);
}