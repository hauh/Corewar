/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/05 18:48:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwCommandInit(corewar_t *gameInstance)
{
	command_t	*commandObj;
	size_t		option;
	int			iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		option = 0;
		cwCreateInstanceCommand(&commandObj);
		gameInstance->paCommands[iter] = commandObj;
		if (iter == LIVE)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, LIVE, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &live_exec);
		}
		else if (iter == LD)
		{
			cwPutOption(&option, 5, DIRECTION_SIZE, LD, TRUE, TRUE, FALSE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &ld_exec);
		}
		else if (iter == ST)
		{
			cwPutOption(&option, 5, DIRECTION_SIZE, ST, TRUE, TRUE, FALSE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &st_exec);
		}
		else if (iter == ADD)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, ADD, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &add_exec);
		}
		else if (iter == SUB)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, SUB, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &sub_exec);
		}
		else if (iter == AND)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, AND, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &and_exec);
		}
		else if (iter == OR)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, OR, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &or_exec);
		}
		else if (iter == XOR)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, XOR, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &xor_exec);
		}
		else if (iter == ZJMP)
		{
			cwPutOption(&option, 20, SHORT_DIR_SIZE, ZJMP, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &zjmp_exec);
		}
		else if (iter == LDI)
		{
			cwPutOption(&option, 25, SHORT_DIR_SIZE, LDI, TRUE, TRUE, TRUE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &ldi_exec);
		}
		else if (iter == STI)
		{
			cwPutOption(&option, 25, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &sti_exec);
		}
		else if (iter == FORK)
		{
			cwPutOption(&option, 800, SHORT_DIR_SIZE, FORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &fork_exec);
		}
		else if (iter == LLD)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, LLD, TRUE, TRUE, FALSE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &lld_exec);
		}
		else if (iter == LLDI)
		{
			cwPutOption(&option, 50, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &lldi_exec);
		}
		else if (iter == LFORK)
		{
			cwPutOption(&option, 1000, SHORT_DIR_SIZE, LFORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &lfork_exec);
		}
		else if (iter == AFF)
		{
			cwPutOption(&option, 2, DIRECTION_SIZE, AFF, TRUE, FALSE, FALSE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &aff_exec);
		}
		++iter;
	}
	}
}

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