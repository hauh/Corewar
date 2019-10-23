/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/23 20:23:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cwMergeQueueToList(corewar_t *pGameInstance)
{
	carriage_t	*pTempCarriage;
	int			iter;

	iter = 0;
	while (iter < pGameInstance->queueSize)
	{
		pTempCarriage = pGameInstance->pWaitingQueue->pNext;
		pGameInstance->cwAddCarriageToList(pGameInstance, pGameInstance->pWaitingQueue);
		pGameInstance->carriagesAmount += 1;
		pGameInstance->pWaitingQueue = pTempCarriage;
		++iter;
	}
	pGameInstance->pWaitingQueue	= NULL;
	pGameInstance->queueSize		= 0;
}

static void		cwPushToQueue(corewar_t *pGameInstance, carriage_t *pAddingCarriage)
{
	pGameInstance->queueSize += 1;
	if (!pGameInstance->pWaitingQueue)
	{
		pGameInstance->pWaitingQueue	= pAddingCarriage;
		pAddingCarriage->pNext			= pAddingCarriage;
		pAddingCarriage->pPrev			= pAddingCarriage;
	}
	else
	{
		pAddingCarriage->pNext						= pGameInstance->pWaitingQueue;
		pAddingCarriage->pPrev						= pGameInstance->pWaitingQueue->pPrev;
		pGameInstance->pWaitingQueue->pPrev->pNext	= pAddingCarriage;
		pGameInstance->pWaitingQueue->pPrev			= pAddingCarriage;
	}
}

static void		cwDeleteCarriage(corewar_t *pGameInstance, int *pDeletedCount)
{
	carriage_t	*pTemporaryCarriage;

	pTemporaryCarriage = pGameInstance->pCarriageObj;
	if (pGameInstance->pCarriageObj->pNext == pGameInstance->pCarriageObj)
		pGameInstance->pCarriageObj->cwDestructor(&pGameInstance->pCarriageObj);
	else
	{
		pGameInstance->pCarriageObj->pPrev->pNext	= pGameInstance->pCarriageObj->pNext;
		pGameInstance->pCarriageObj->pNext->pPrev	= pGameInstance->pCarriageObj->pPrev;
		pGameInstance->pCarriageObj					= pGameInstance->pCarriageObj->pNext;
		pTemporaryCarriage->cwDestructor			(&pTemporaryCarriage);
	}
	*pDeletedCount += 1;
}

static void	cwMainChecking(corewar_t *pGameInstance)
{
	int		deletedCount;
	int		iter;

	deletedCount = 0;
	iter		 = CW_BEGIN_FROM_ZERO;
	++pGameInstance->pArenaObj->checkAmount;
	while (iter < pGameInstance->carriagesAmount)
	{
		if (pGameInstance->pArenaObj->cycleAmount - pGameInstance->pCarriageObj->lastSpeakCycle >= pGameInstance->pArenaObj->cycleToDie || pGameInstance->pArenaObj->cycleToDie <= 0)
			pGameInstance->cwDeleteCarriage(pGameInstance, &deletedCount);
		pGameInstance->pCarriageObj ? pGameInstance->pCarriageObj = pGameInstance->pCarriageObj->pNext : CW_FALSE;
		++iter;
	}
	pGameInstance->carriagesAmount -= deletedCount;
	if (pGameInstance->pArenaObj->liveAmount >= NBR_LIVE || pGameInstance->pArenaObj->checkAmount >= MAX_CHECKS)
	{
		pGameInstance->pArenaObj->cycleToDie -= CYCLE_DELTA;
		pGameInstance->pArenaObj->checkAmount = 0;
	}
	pGameInstance->pArenaObj->liveAmount = 0;
}

static void	cwStartGame(corewar_t *pGameInstance)
{
	int				iter;

	while (pGameInstance->pCarriageObj)
	{
		iter = CW_BEGIN_FROM_ZERO;
		while (iter < pGameInstance->carriagesAmount)
		{
			if (!pGameInstance->pCarriageObj->waitingTime)
				pGameInstance->pCarriageObj->cwSetCommandTime(pGameInstance->pCarriageObj, pGameInstance->pArenaObj);
			if (pGameInstance->pCarriageObj->waitingTime > 0)
				pGameInstance->pCarriageObj->cwReduceTime(pGameInstance->pCarriageObj);
			if (!pGameInstance->pCarriageObj->waitingTime)
				pGameInstance->pCarriageObj->cwExecCommand(pGameInstance->pCarriageObj, pGameInstance);
			pGameInstance->pCarriageObj = pGameInstance->pCarriageObj->pNext;
			++iter;
		}
		pGameInstance->cwMergeQueueToList(pGameInstance);
		if (pGameInstance->pArenaObj->cwTimeToCheck(pGameInstance->pArenaObj))
			pGameInstance->cwMainChecking(pGameInstance);
		if (pGameInstance->loadDump == ++pGameInstance->pArenaObj->cycleAmount)
		{
			pGameInstance->pArenaObj->cwPrintField(pGameInstance->pArenaObj);
			exit(1);
		}
	}
}

static void	cwArrangeUnitsOnField(corewar_t *gameInstance)
{
	int		iter;
	int		playerLocation;
	int		memoryStep;
	int		codeIter;

	memoryStep	= MEM_SIZE / gameInstance->playersAmount;
	iter		= CW_BEGIN_FROM_ZERO;
	while (iter < gameInstance->carriagesAmount)
	{
		codeIter = CW_BEGIN_FROM_ZERO;
		playerLocation = memoryStep * iter;
		gameInstance->pCarriageObj->currentLocation = playerLocation;
		while (playerLocation < memoryStep * iter + CHAMP_MAX_SIZE)
			gameInstance->pArenaObj->pField[playerLocation++] = gameInstance->pCarriageObj->pOwnerCarriage->pCode[codeIter++];
		gameInstance->pCarriageObj	= gameInstance->pCarriageObj->pNext;
		++iter;
	}
}

static void	cwCongratulations(corewar_t *pGameInstance)
{
	ft_printf("\t\t\tCongratulations winner!!!\n");
	ft_printf("\t\t\t>>>%s(id: %d)<<<\n", pGameInstance->pArenaObj->pLastSurvivor->pName, pGameInstance->pArenaObj->pLastSurvivor->id);
}

static void	cwIntroducePlayers(corewar_t *gameInstance)
{
	int				iter;

	iter = CW_BEGIN_FROM_ZERO;
	ft_printf("Introducing contestants...\n");
	while (iter < gameInstance->carriagesAmount)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		gameInstance->pCarriageObj->pOwnerCarriage->id,
		gameInstance->pCarriageObj->pOwnerCarriage->codeSize,
		gameInstance->pCarriageObj->pOwnerCarriage->pName,
		gameInstance->pCarriageObj->pOwnerCarriage->pComment);
		gameInstance->pCarriageObj = gameInstance->pCarriageObj->pNext;
		++iter;
	}
}

static void	cwFreeAllCommand(corewar_t *pGameInstance)
{
	int				iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		pGameInstance->paCommands[iter]->cwDestructorCommand(&pGameInstance->paCommands[iter]);
		++iter;
	}
}

static void	cwFreeAllCarriage(corewar_t *pGameInstance)
{
	carriage_t		*tmp;

	if (pGameInstance->pCarriageObj)
	{
		pGameInstance->pCarriageObj->pPrev->pNext	= NULL;
		pGameInstance->pCarriageObj->pPrev			= NULL;
		while (pGameInstance->pCarriageObj)
		{
			tmp = pGameInstance->pCarriageObj;
			pGameInstance->pCarriageObj = pGameInstance->pCarriageObj->pNext;
			tmp->cwDestructor(&tmp);
		}
	}
}

static void	cwFreeAllPlayer(corewar_t *pGameInstance)
{
	player_t		*tmp;

	if (pGameInstance->pPlayerObj)
	{
		pGameInstance->pPlayerObj->pPrev->pNext	= NULL;
		pGameInstance->pPlayerObj->pPrev		= NULL;
		while (pGameInstance->pPlayerObj)
		{
			tmp = pGameInstance->pPlayerObj;
			pGameInstance->pPlayerObj = pGameInstance->pPlayerObj->pNext;
			tmp->cwDestructor(&tmp);
		}
	}
}

static void	cwAddCarriageToList(corewar_t *pGameInstance, carriage_t *pCarriageAdding)
{
	if (!pGameInstance->pCarriageObj)
	{
		pGameInstance->pCarriageObj			= pCarriageAdding;
		pGameInstance->pCarriageObj->pNext	= pCarriageAdding;
		pGameInstance->pCarriageObj->pPrev	= pCarriageAdding;
	}
	else
	{
		pCarriageAdding->pNext						= pGameInstance->pCarriageObj;
		pCarriageAdding->pPrev						= pGameInstance->pCarriageObj->pPrev;
		pGameInstance->pCarriageObj->pPrev->pNext	= pCarriageAdding;
		pGameInstance->pCarriageObj->pPrev			= pCarriageAdding;
	}
}

static void	cwAddPlayerToList(corewar_t *pGameInstance, player_t *pPlayerAdding)
{
	if (!pGameInstance->pPlayerObj)
	{
		pGameInstance->pPlayerObj		 = pPlayerAdding;
		pGameInstance->pPlayerObj->pNext = pPlayerAdding;
		pGameInstance->pPlayerObj->pPrev = pPlayerAdding;
	}
	else
	{
		pPlayerAdding->pNext					= pGameInstance->pPlayerObj;
		pPlayerAdding->pPrev					= pGameInstance->pPlayerObj->pPrev;
		pGameInstance->pPlayerObj->pPrev->pNext	= pPlayerAdding;
		pGameInstance->pPlayerObj->pPrev		= pPlayerAdding;
	}
}

static void	cwCommandObjectInit(corewar_t *pGameInstance)
{
	command_t		*pCommandObj;
	int				iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cw_create_instance_command			(&pCommandObj);
		pCommandObj->cwRecognizeCommand	(pCommandObj, iter);
		pGameInstance->paCommands[iter]	= pCommandObj;
		++iter;
	}
}

static void		cwCarriageObjectInit(corewar_t *pGameInstance)
{
	carriage_t	*pCarriageObj;
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < pGameInstance->playersAmount)
	{
		cw_create_instance_carriage(&pCarriageObj);
		pCarriageObj->id					= -++pGameInstance->carriagesAmount;
		pCarriageObj->ppCommandContainer	= pGameInstance->paCommands;
		pCarriageObj->cwSetOwner			(pCarriageObj, pGameInstance->pPlayerObj, pGameInstance->playersAmount);
		pCarriageObj->cwWriteOwnerIdToReg	(pCarriageObj);
		pCarriageObj->Test					= pGameInstance->pArenaObj->cwPrintField;
		pCarriageObj->test					= pGameInstance->pArenaObj;
		pGameInstance->cwAddCarriageToList	(pGameInstance, pCarriageObj);
		++iter;
	}
	pGameInstance->pArenaObj->cwSetLastSurvivor(pGameInstance->pArenaObj, pGameInstance->pCarriageObj->pPrev->pOwnerCarriage);
}

static void		cwPlayerObjectInit(corewar_t *pGameInstance, int argc, char **argv)
{
	player_t	*pPlayerObj;
	int			standartId;
	int			customId;
	int			iter;
	int			busyByte;

	standartId	= 0;
	customId	= 0;
	busyByte	= CW_ALL_FREE;
	iter		= CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (*(argv[iter]) == CW_KEY)
		{
			while (*++(argv[iter]))
				if (*(argv[iter]) == 'n' && iter + 1 < argc)
					(customId = ft_atoi(argv[iter + 1])) < CW_MIN_PLAYERS
						|| (customId = ft_atoi(argv[iter + 1])) > CW_MAX_PLAYERS ?
							cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid number near -n") :
								CW_FALSE;
				else if (*(argv[iter]) == 'd' && iter + 1 < argc)
					(pGameInstance->loadDump = ft_atoi(argv[iter + 1])) < CW_MIN_DUMP_CYCLE ?
						cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid nubmer near -d") :
							CW_FALSE;
				else if (*(argv[iter]) == 'v')
					pGameInstance->visualizator = CW_TRUE;
				else
					cwErrorCatcher(CW_NOT_VALID_KEY, "Not that place");
			pGameInstance->loadDump || customId ? ++iter : CW_FALSE;
		}
		else if (++pGameInstance->playersAmount)
		{
			cw_create_instance_player		(&pPlayerObj);
			pPlayerObj->cwReadFile		(pPlayerObj, argv[iter]);
			pPlayerObj->cwSelfBuild		(pPlayerObj);
			pPlayerObj->cwSelfValidate	(pPlayerObj);
			if (customId)
				pPlayerObj->cwSetId		(pPlayerObj, &busyByte, customId, CW_TRUE);
			pGameInstance->cwAddPlayerToList(pGameInstance, pPlayerObj);
			customId = 0;
		}
		++iter;
	}
	if (pGameInstance->playersAmount < 1 || pGameInstance->playersAmount > 4)
		cwErrorCatcher(CW_INVALID_PLAYERS, CW_PLAYER);
	iter = 0;
	while (iter < pGameInstance->playersAmount)
	{
		if (pGameInstance->pPlayerObj->id == 0)
			pGameInstance->pPlayerObj->cwSetId(pGameInstance->pPlayerObj, &busyByte, 1, CW_FALSE);
		pGameInstance->pPlayerObj = pGameInstance->pPlayerObj->pNext;
		++iter;
	}
	pGameInstance->pArenaObj->cwSetLastSurvivor(pGameInstance->pArenaObj, pGameInstance->pPlayerObj->pPrev);
}

static void		cwArenaObjectInit(corewar_t *gameInstance)
{
	arena_t		*pArenaObj;

	cw_create_instance_arena(&pArenaObj);
	pArenaObj->cwBufferInit(pArenaObj);
	gameInstance->pArenaObj = pArenaObj;
}

/*
**--------------------------------------------------------------------------------------
*/

static void	cwConstructor(corewar_t **ppGameInstance)
{
	(*ppGameInstance)->playersAmount	= 0;
	(*ppGameInstance)->commandsAmount	= 0;
	(*ppGameInstance)->carriagesAmount	= 0;
	(*ppGameInstance)->queueSize		= 0;
	(*ppGameInstance)->visualizator		= CW_FALSE;
	(*ppGameInstance)->loadDump			= CW_FALSE;
	(*ppGameInstance)->pCarriageObj		= NULL;
	(*ppGameInstance)->pPlayerObj		= NULL;
	(*ppGameInstance)->pArenaObj		= NULL;
	(*ppGameInstance)->pWaitingQueue	= NULL;
}

static void	cwDestructor(corewar_t **ppGameInstance)
{
	(*ppGameInstance)->cwFreeAllCarriages		(*ppGameInstance);
	(*ppGameInstance)->cwFreeAllPlayers			(*ppGameInstance);
	(*ppGameInstance)->cwFreeAllCommand			(*ppGameInstance);
	(*ppGameInstance)->pArenaObj->cwDestructor	(&(*ppGameInstance)->pArenaObj);
	free(*ppGameInstance);
	*ppGameInstance = NULL;
}

extern void	cw_create_instance_game(corewar_t **ppGameObj)
{
	if (!(*ppGameObj = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	(*ppGameObj)->cwConstructor			= cwConstructor;
	(*ppGameObj)->cwDestructor			= cwDestructor;
	(*ppGameObj)->cwCarriageObjInit		= cwCarriageObjectInit;
	(*ppGameObj)->cwCommandObjInit		= cwCommandObjectInit;
	(*ppGameObj)->cwPlayerObjInit		= cwPlayerObjectInit;
	(*ppGameObj)->cwArenaObjInit		= cwArenaObjectInit;
	(*ppGameObj)->cwAddCarriageToList	= cwAddCarriageToList;
	(*ppGameObj)->cwAddPlayerToList		= cwAddPlayerToList;
	(*ppGameObj)->cwFreeAllCarriages	= cwFreeAllCarriage;
	(*ppGameObj)->cwFreeAllPlayers		= cwFreeAllPlayer;
	(*ppGameObj)->cwFreeAllCommand		= cwFreeAllCommand;
	(*ppGameObj)->cwDeleteCarriage		= cwDeleteCarriage;
	(*ppGameObj)->cwMainChecking		= cwMainChecking;
	(*ppGameObj)->cwStartGame			= cwStartGame;
	(*ppGameObj)->cwArrangeUnitsOnField	= cwArrangeUnitsOnField;
	(*ppGameObj)->cwIntroducePlayers	= cwIntroducePlayers;
	(*ppGameObj)->cwCongratulations		= cwCongratulations;
	(*ppGameObj)->cwPushToQueue			= cwPushToQueue;
	(*ppGameObj)->cwMergeQueueToList	= cwMergeQueueToList;
	(*ppGameObj)->cwConstructor			(ppGameObj);
}

/*
**--------------------------------------------------------------------------------------
*/