/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 20:02:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	liveExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwValidateTypes	(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->offset);
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	ft_printf("Hellolive\n");
}

void	ldExec(corewar_t *pGameObject)
{
	ft_printf("Hellold\n");
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
	pGameObject->pCarriageObject->cwComputeJump		(pGameObject->pCarriageObject);
	ft_printf("Hellost\n");
}

void	addExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloadd\n");
}

void	subExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellosub\n");
}

void	andExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloand\n");
}

void	orExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloor\n");
}

void	xorExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloxor\n");
}

void	zjmpExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellozj\n");
}

void	ldiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloldi\n");
}

void	stiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellosti\n");
}

void	forkExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellofork\n");
}

void	lldExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellolld\n");
}

void	lldiExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellolldi\n");
}

void	lforkExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Hellolfork\n");
}

void	affExec(corewar_t *pGameObject)
{
	pGameObject->pCarriageObject->cwSavePos			(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->id > 0);
	pGameObject->pCarriageObject->cwParseTypes		(pGameObject->pCarriageObject);
	pGameObject->pCarriageObject->cwMoveTo			(pGameObject->pCarriageObject, pGameObject->pCarriageObject->pCurrentCommand->typeByte);
	pGameObject->pCarriageObject->cwComputeJump	(pGameObject->pCarriageObject);
	ft_printf("Helloaff\n");
}