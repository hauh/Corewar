/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:20:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	cwCheckConditions(arena_t *pArenaInstance)
{
	if (pArenaInstance->cycleToDie <= 0 || pArenaInstance->cycleAmount % pArenaInstance->cycleToDie == 0)
		return (CW_TRUE);
	else
		return (CW_FALSE);
}

static void	cwPrintField(arena_t *pArenaInstance)
{
	int	border;
	int	i;

	border	= sqrt(MEM_SIZE);
	i		= CW_BEGIN_FROM_ZERO;
	printf("%4d: ", 0);
	while (i < MEM_SIZE)
	{
		printf("%.2x ", pArenaInstance->pField[i]);
		if ((i + 1) % border == 0)
			printf("\n%4x: ", i + 1);
		++i;
	}
	printf("\n");
}

static void	cwBuffersInit(arena_t *pArenaInstance)
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

static void	cwConstructorArena(arena_t **ppArenaInstance)
{
	if (!((*ppArenaInstance)->pField = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset((*ppArenaInstance)->pField, 0, MEM_SIZE);
	(*ppArenaInstance)->cycleAmount = 0;
	(*ppArenaInstance)->checkAmount	= 0;
	(*ppArenaInstance)->liveAmount	= 0;
	(*ppArenaInstance)->cycleToDie	= CYCLE_TO_DIE;
}

static void	cwDestructorArena(arena_t **ppArenaInstance)
{
	free((*ppArenaInstance)->pField);
	free(*ppArenaInstance);
	*ppArenaInstance = NULL;
}

void	cwCreateInstanceArena(arena_t **ppArenaObj)
{
	if (!(*ppArenaObj = (arena_t *)malloc(sizeof(arena_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppArenaObj)->cwConstructorArena	= (const void *)&cwConstructorArena;
	(*ppArenaObj)->cwDestructorArena	= (const void *)&cwDestructorArena;
	(*ppArenaObj)->cwCheckConditions	= (const void *)&cwCheckConditions;
	(*ppArenaObj)->cwBufferInit			= (const void *)&cwBuffersInit;
	(*ppArenaObj)->cwPrintField			= (const void *)&cwPrintField;
	(*ppArenaObj)->cwConstructorArena	(ppArenaObj);
}