/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArena.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/05 17:55:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwPrintField(arena_t *arenaInstance)
{
	int	border;
	int	i;

	border	= sqrt(MEM_SIZE);
	i		= CW_BEGIN_FROM_ZERO;
	printf("%4d: ", 0);
	while (i < MEM_SIZE)
	{
		printf("%.2x ", arenaInstance->field[i]);
		if ((i + 1) % border == 0)
			printf("\n%4d: ", i + 1);
		++i;
	}
	printf("\n");
}

void	cwBuffersInit(arena_t *arenaInstance)
{
	buffer_t	*bufferObj;
	int			bufIter;

	bufIter = CW_BEGIN_FROM_ZERO;
	while (bufIter < CW_BUFFER_AMOUNT)
	{
		cwCreateInstanceBuffer(&bufferObj);
		bufferObj->cwConstructorBuffer;
		arenaInstance->bufferSet[bufIter] = bufferObj;
		++bufIter;
	}
}

void	cwConstructorArena(arena_t *arenaInstance)
{
	if (!(arenaInstance->field = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset(arenaInstance->field, 0, MEM_SIZE);
	arenaInstance->cycle_amount 	= 0;
	arenaInstance->live_amount		= 0;
	arenaInstance->check_amount		= 0;
	arenaInstance->cycle_to_die		= CYCLE_TO_DIE;
	arenaInstance->cwPrintField		= &cwPrintField;
	arenaInstance->cwBufferInit		= &cwBuffersInit;
}

void	cwDestructorArena(arena_t *arenaInstance)
{
	free(arenaInstance->field);
	free(arenaInstance);
}

void	cwCreateInstanceArena(arena_t **arenaObj)
{
	if (!(*arenaObj = (arena_t *)malloc(sizeof(arena_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*arenaObj)->cwConstructorArena	= &cwConstructorArena;
	(*arenaObj)->cwDestructorArena	= &cwDestructorArena;
}