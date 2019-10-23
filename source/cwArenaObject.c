/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/23 18:41:05 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cwTimeToCheck(arena_t *pArenaInstance)
{
	if (pArenaInstance->cycleToDie <= 0 || !(pArenaInstance->cycleAmount % pArenaInstance->cycleToDie))
		return (CW_TRUE);
	else
		return (CW_FALSE);
}

static void		cwPrintField(arena_t *pArenaInstance)
{
	int			border;
	int			iter;

	border	= sqrt(MEM_SIZE);
	iter	= CW_BEGIN_FROM_ZERO;
	ft_printf("0x0000 : ");
	while (iter < MEM_SIZE)
	{
		if (iter == *pArenaInstance->test)
			ft_printf("@{red}%.2x @{eoc}", pArenaInstance->pField[iter]);
		else
			ft_printf("%.2x ", pArenaInstance->pField[iter]);
		if ((iter + 1) % border == 0 && iter != MEM_SIZE - 1)
			ft_printf("\n%#06x : ", iter + 1);
		++iter;
	}
	ft_printf("\n");
}

static void		cwBuffersInit(arena_t *pArenaInstance)
{
	buffer_t	*bufferObj;
	int			bufIter;

	bufIter = CW_BEGIN_FROM_ZERO;
	while (bufIter < CW_BUFFER_AMOUNT)
	{
		cwCreateInstanceBuffer(&bufferObj);
		pArenaInstance->paBufferSet[bufIter] = bufferObj;
		++bufIter;
	}
}

static void		cwSetLastSurvivor(arena_t *pArenaInstance, player_t *pLastSurvivor)
{
	pArenaInstance->pLastSurvivor = pLastSurvivor;
}

/*
** Low level function for initialization object;
**-----------------------------------------------------------------------------
*/

static void		cwConstructor(arena_t **ppArenaInstance)
{
	if (!((*ppArenaInstance)->pField = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset((*ppArenaInstance)->pField, 0, MEM_SIZE);
	(*ppArenaInstance)->cycleAmount		= 0;
	(*ppArenaInstance)->checkAmount		= 0;
	(*ppArenaInstance)->liveAmount		= 0;
	(*ppArenaInstance)->cycleToDie		= CYCLE_TO_DIE;
	(*ppArenaInstance)->pLastSurvivor	= NULL;
}

static void		cwDestructor(arena_t **ppArenaInstance)
{
	int			iter;

	iter = 0;
	while (iter < CW_BUFFER_AMOUNT)
		(*ppArenaInstance)->paBufferSet[iter]->cwDestructor(&(*ppArenaInstance)->paBufferSet[iter]);
	free((*ppArenaInstance)->pField);
	free(*ppArenaInstance);
	*ppArenaInstance = NULL;
}

extern void		cwCreateInstanceArena(arena_t **ppArenaObj)
{
	if (!(*ppArenaObj = (arena_t *)malloc(sizeof(arena_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppArenaObj)->cwConstructor		= cwConstructor;
	(*ppArenaObj)->cwDestructor			= cwDestructor;
	(*ppArenaObj)->cwSetLastSurvivor	= cwSetLastSurvivor;
	(*ppArenaObj)->cwTimeToCheck		= cwTimeToCheck;
	(*ppArenaObj)->cwBufferInit			= cwBuffersInit;
	(*ppArenaObj)->cwPrintField			= cwPrintField;
	(*ppArenaObj)->cwConstructor		(ppArenaObj);
}

/*
**--------------------------------------------------------------------------------------
*/