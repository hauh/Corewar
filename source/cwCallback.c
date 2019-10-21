/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/21 19:27:54 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObj)
{
	ft_printf("Live executing.../ | \\\n");
	pGameObj->pCarriageObj->cwParseTypes	(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation	(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->pOwnerCarriage->id == pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.intValue)
		pGameObj->pArenaObj->pLastSurvivor = pGameObj->pCarriageObj->pOwnerCarriage;
	pGameObj->pCarriageObj->lastSpeakCycle = pGameObj->pArenaObj->cycleAmount;
}

void	ldExec(corewar_t *pGameObj)
{
	ft_printf("Ld executing now.../ | \\\n");
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

void	stExec(corewar_t *pGameObj)
{
	ft_printf("St executing now.../ | \\\n");
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
	ft_printf("Add executing.../ | \\\n");
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
	ft_printf("Sub executing.../ | \\\n");
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
	ft_printf("And executing.../ | \\\n");
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
	ft_printf("Or executing.../ | \\\n");
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
	ft_printf("Xor executing.../ | \\\n");
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
	ft_printf("Zjmp executing.../ | \\\n");
	pGameObj->pCarriageObj->cwParseTypes(pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	if (pGameObj->pCarriageObj->carry)
		pGameObj->pCarriageObj->cwMoveTo(pGameObj->pCarriageObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1]->sTypes.shortValue);
}

void	ldiExec(corewar_t *pGameObj)
{
	ft_printf("Ldi executing.../ | \\\n");
	pGameObj->pCarriageObj->cwParseTypes (pGameObj->pCarriageObj, pGameObj->pArenaObj);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_1], pGameObj->pCarriageObj->firstArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
	pGameObj->pCarriageObj->cwReadOperation(pGameObj->pCarriageObj, pGameObj->pArenaObj, pGameObj->pArenaObj->paBufferSet[CW_VALUE_BUF_2], pGameObj->pCarriageObj->secondArg);
	if (pGameObj->pCarriageObj->errorOcurred)
		return ;
}

void	stiExec(corewar_t *pGameObj)
{
	ft_printf("Sti executing.../ | \\\n");

}

void	forkExec(corewar_t *pGameObj)
{
	ft_printf("Fork executing.../ | \\\n");

}

void	lldExec(corewar_t *pGameObj)
{
	ft_printf("Lld executing.../ | \\\n");

}

void	lldiExec(corewar_t *pGameObj)
{
	ft_printf("Lldi executing.../ | \\\n");

}

void	lforkExec(corewar_t *pGameObj)
{
	ft_printf("Lfork executing.../ | \\\n");

}

void	affExec(corewar_t *pGameObj)
{
	ft_printf("Aff executing.../ | \\\n");

}