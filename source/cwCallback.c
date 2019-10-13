/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 18:20:11 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwValidateTypes	(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
}

void	ldExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwReadOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->firstArg, CW_TRUE);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwWriteOperation	(pGameObject->pCarriageObject, pGameObject->pArenaObject, pGameObject->pArenaObject->paBufferSet[CW_VALUE_BUF_1], pGameObject->pCarriageObject->secondArg, CW_TRUE);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwCarriageReturn	(pGameObject->pCarriageObject);
}

void	stExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	addExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	subExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	andExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	orExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	xorExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	zjmpExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	ldiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	stiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	forkExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	lldExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	lldiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	lforkExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}

void	affExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
}