/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 15:56:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwDeleteCarriage(corewar_t *pGameInstance, int *pDeletedCount)
{
	carriage_t *temporaryCarriage;

	temporaryCarriage = pGameInstance->pCarriageObject;
	if (pGameInstance->pCarriageObject->pNext == pGameInstance->pCarriageObject)
		pGameInstance->pCarriageObject->cwDestructorCarriage(&pGameInstance->pCarriageObject);
	else
	{
		if (pGameInstance->pCarriageObject == pGameInstance->pArenaObject->pLastCarriage)
			pGameInstance->pArenaObject->pLastCarriage	= pGameInstance->pCarriageObject->pPrev;
		pGameInstance->pCarriageObject->pPrev->pNext	= pGameInstance->pCarriageObject->pNext;
		pGameInstance->pCarriageObject->pNext->pPrev	= pGameInstance->pCarriageObject->pPrev;
		pGameInstance->pCarriageObject					= pGameInstance->pCarriageObject->pNext;
		temporaryCarriage->cwDestructorCarriage			(&temporaryCarriage);
	}
	*pDeletedCount += 1;
}

static void	cwMainChecking(corewar_t *pGameInstance)
{
	int		deletedCount;
	int		iter;

	deletedCount	= 0;
	iter			= CW_BEGIN_FROM_ZERO;
	++pGameInstance->pArenaObject->checkAmount;
	while (iter < pGameInstance->carriagesAmount)
	{
		if (pGameInstance->pArenaObject->cycleAmount - pGameInstance->pCarriageObject->lastSpeakCycle >= pGameInstance->pArenaObject->cycleToDie || pGameInstance->pArenaObject->cycleToDie <= 0)
			pGameInstance->cwDeleteCarriage(pGameInstance, &deletedCount);
		if (pGameInstance->pCarriageObject)
			pGameInstance->pCarriageObject = pGameInstance->pCarriageObject->pNext;
		++iter;
	}
	pGameInstance->carriagesAmount					-= deletedCount;
	if (pGameInstance->pArenaObject->liveAmount		>= NBR_LIVE)
	{
		pGameInstance->pArenaObject->cycleToDie		-= CYCLE_DELTA;
		pGameInstance->pArenaObject->checkAmount	= 0;
	}
	if (pGameInstance->pArenaObject->checkAmount	>= MAX_CHECKS)
	{
		pGameInstance->pArenaObject->checkAmount	= 0;
		pGameInstance->pArenaObject->cycleToDie		-= CYCLE_DELTA;
	}
	pGameInstance->pArenaObject->liveAmount			= 0;
}

static void	cwStartGame(corewar_t *pGameInstance)
{
	int		iter;

	while (pGameInstance->pCarriageObject)
	{
		iter = CW_BEGIN_FROM_ZERO;
		while (iter < pGameInstance->carriagesAmount)
		{
			if (pGameInstance->pCarriageObject->pCurrentCommand	== NULL)
				;//pGameInstance->pCarriageObject->cwSetCommandTime	(pGameInstance->pCarriageObject, pGameInstance->pArenaObject);
			if (pGameInstance->pCarriageObject->waitingTime > 0)
				;//pGameInstance->pCarriageObject->cwReduceWaitingTime	(pGameInstance->pCarriageObject);
			if (pGameInstance->pCarriageObject->pCurrentCommand != NULL)
				;//pGameInstance->pCarriageObject->cwExecCommand		(pGameInstance->pCarriageObject);
			pGameInstance->pCarriageObject = pGameInstance->pCarriageObject->pNext;
			++iter;
		}
		if (pGameInstance->pArenaObject->cwCheckConditions(pGameInstance->pArenaObject) == CW_TRUE)
			pGameInstance->cwMainChecking(pGameInstance);
		++pGameInstance->pArenaObject->cycleAmount;
	}
}

static void		cwArrangeUnitsOnField(corewar_t *gameInstance)
{
	int			iter;
	int			playerLocation;
	int			memoryStep;
	int			codeIter;

	memoryStep = MEM_SIZE / gameInstance->playersAmount;
	iter = CW_BEGIN_FROM_ZERO;
	while (iter < gameInstance->playersAmount)
	{
		codeIter = CW_BEGIN_FROM_ZERO;
		playerLocation = memoryStep * iter;
		gameInstance->pCarriageObject->currentLocation = playerLocation;
		while (playerLocation < memoryStep * iter + CHAMP_MAX_SIZE)
			gameInstance->pArenaObject->pField[playerLocation++] = gameInstance->pPlayerObject->pCode[codeIter++];
		gameInstance->pPlayerObject		= gameInstance->pPlayerObject->pNext;
		gameInstance->pCarriageObject	= gameInstance->pCarriageObject->pNext;
		++iter;
	}
}

static void cwCongratulations(corewar_t *pGameInstance)
{
	ft_printf("\t\t\tCongratulations winner!!!\n");
	ft_printf("\t\t\t>>>%s(id: %d)<<<\n", pGameInstance->pArenaObject->pLastSurvivor->pName, pGameInstance->pArenaObject->pLastSurvivor->id);
}

static void	cwIntroducePlayers(corewar_t *gameInstance)
{
	int		iter;

	iter = CW_BEGIN_FROM_ZERO;
	ft_printf("Introducing contestants...\n");
	while (iter < gameInstance->playersAmount)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		gameInstance->pPlayerObject->id,
		gameInstance->pPlayerObject->codeSize,
		gameInstance->pPlayerObject->pName,
		gameInstance->pPlayerObject->pComment);
		gameInstance->pPlayerObject = gameInstance->pPlayerObject->pNext;
		++iter;
	}
}

static void cwFreeAllCommand(corewar_t *pGameInstance)
{
	;
}

static void cwFreeAllCarriage(corewar_t *pGameInstance)
{
	;
}

static void	cwFreeAllPlayer(corewar_t *pGameInstance)
{
	;
}

static void	cwAddCarriageToList(corewar_t *pGameInstance, carriage_t *pCarriageAdding)
{
	if (!pGameInstance->pCarriageObject)
	{
		pGameInstance->pCarriageObject			= pCarriageAdding;
		pGameInstance->pCarriageObject->pNext	= pCarriageAdding;
		pGameInstance->pCarriageObject->pPrev	= pCarriageAdding;
	}
	else
	{
		pCarriageAdding->pNext							= pGameInstance->pCarriageObject;
		pCarriageAdding->pPrev							= pGameInstance->pCarriageObject->pPrev;
		pGameInstance->pCarriageObject->pPrev->pNext	= pCarriageAdding;
		pGameInstance->pCarriageObject->pPrev			= pCarriageAdding;
	}
}

static void	cwAddPlayerToList(corewar_t *pGameInstance, player_t *pPlayerAdding)
{
	if (!pGameInstance->pPlayerObject)
	{
		pGameInstance->pPlayerObject		= pPlayerAdding;
		pGameInstance->pPlayerObject->pNext	= pPlayerAdding;
		pGameInstance->pPlayerObject->pPrev	= pPlayerAdding;
	}
	else
	{
		pPlayerAdding->pNext						= pGameInstance->pPlayerObject;
		pPlayerAdding->pPrev						= pGameInstance->pPlayerObject->pPrev;
		pGameInstance->pPlayerObject->pPrev->pNext	= pPlayerAdding;
		pGameInstance->pPlayerObject->pPrev			= pPlayerAdding;
	}
}

static void	cwCommandObjectInit(corewar_t *pGameInstance)
{
	command_t	*pCommandObj;
	int			iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cwCreateInstanceCommand(&pCommandObj);
		pCommandObj->cwRecognizeCommand(pCommandObj, iter);
		pGameInstance->paCommands[iter] = pCommandObj;
		++iter;
	}
}

static void	cwArenaObjectInit	(corewar_t *gameInstance)
{
	arena_t	*arenaObj;

	cwCreateInstanceArena		(&arenaObj);
	arenaObj->cwBufferInit		(arenaObj);
	arenaObj->pLastSurvivor		= gameInstance->pPlayerObject->pPrev;
	arenaObj->pLastCarriage		= gameInstance->pCarriageObject->pPrev;
	gameInstance->pArenaObject	= arenaObj;
}

static void	cwCarriageObjectInit(corewar_t *pGameInstance)
{
	carriage_t	*pCarriageObj;
	int		iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < pGameInstance->playersAmount)
	{
		cwCreateInstanceCarriage(&pCarriageObj);
		pCarriageObj->id = ++pGameInstance->carriagesAmount;
		pCarriageObj->pOwnerCarriage = pGameInstance->pPlayerObject;
		pGameInstance->cwAddCarriageToList(pGameInstance, pCarriageObj);
		pGameInstance->pPlayerObject = pGameInstance->pPlayerObject->pNext;
		++iter;
	}
}

static void	cwPlayerObjectInit(corewar_t *pGameInstance, int argc, char **argv)
{
	player_t	*pPlayerObj;
	int		iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (argv[iter][0] != CW_CHECK_SEAL)
		{
			cwCreateInstancePlayer			(&pPlayerObj);
			pPlayerObj->cwReadFile			(pPlayerObj, argv[iter]);
			pPlayerObj->cwBuildPlayer		(pPlayerObj);
			pPlayerObj->cwValidatePlayer	(pPlayerObj);
			pPlayerObj->id					= ++pGameInstance->playersAmount;
			pGameInstance->cwAddPlayerToList(pGameInstance, pPlayerObj);
		}
		++iter;
	}
	if (pGameInstance->playersAmount < 1 || pGameInstance->playersAmount > 4)
		cwErrorCatcher(CW_INVALID_PLAYERS, CW_PLAYER);
}

static void	cwKeyObjectInit(corewar_t *pGameInstance, int argc, char **argv)
{
	key_t	*pKeyObj;

	cwCreateInstanceKey			(&pKeyObj);
	pKeyObj->cwValidateArgs		(pKeyObj, argc, argv);
	pKeyObj->cwReadKeys			(pKeyObj, argc, argv);
	pGameInstance->pKeyObject	= pKeyObj;
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructorGame(corewar_t **ppGameInstance)
{
	(*ppGameInstance)->playersAmount	= 0;
	(*ppGameInstance)->commandsAmount	= 0;
	(*ppGameInstance)->carriagesAmount	= 0;
	(*ppGameInstance)->pCarriageObject	= NULL;
	(*ppGameInstance)->pPlayerObject	= NULL;
	(*ppGameInstance)->pArenaObject		= NULL;
	(*ppGameInstance)->pKeyObject		= NULL;
}

static void	cwDestructorGame(corewar_t **ppGameInstance)
{
	(*ppGameInstance)->cwFreeAllCarriages				(*ppGameInstance);
	(*ppGameInstance)->cwFreeAllPlayers					(*ppGameInstance);
	(*ppGameInstance)->cwFreeAllCommand					(*ppGameInstance);
	(*ppGameInstance)->pArenaObject->cwDestructorArena	(&(*ppGameInstance)->pArenaObject);
	(*ppGameInstance)->pKeyObject->cwDestructorKey		(&(*ppGameInstance)->pKeyObject);
	free(*ppGameInstance);
	*ppGameInstance = NULL;
}

void		cwCreateInstanceGame(corewar_t **ppGameObj)
{
	if (!(*ppGameObj = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	(*ppGameObj)->cwConstructorGame		= (const void *)&cwConstructorGame;
	(*ppGameObj)->cwDestructorGame		= (const void *)&cwDestructorGame;
	(*ppGameObj)->cwCarraigeObjectInit	= (const void *)&cwCarriageObjectInit;
	(*ppGameObj)->cwCommandObjectInit	= (const void *)&cwCommandObjectInit;
	(*ppGameObj)->cwPlayerObjectInit	= (const void *)&cwPlayerObjectInit;
	(*ppGameObj)->cwArenaObjectInit		= (const void *)&cwArenaObjectInit;
	(*ppGameObj)->cwKeyObjectInit		= (const void *)&cwKeyObjectInit;
	(*ppGameObj)->cwAddCarriageToList	= (const void *)&cwAddCarriageToList;
	(*ppGameObj)->cwFreeAllCarriages	= (const void *)&cwFreeAllCarriage;
	(*ppGameObj)->cwAddPlayerToList		= (const void *)&cwAddPlayerToList;
	(*ppGameObj)->cwFreeAllPlayers		= (const void *)&cwFreeAllPlayer;
	(*ppGameObj)->cwFreeAllCommand		= (const void *)&cwFreeAllCommand;
	(*ppGameObj)->cwArrangeUnitsOnField	= (const void *)&cwArrangeUnitsOnField;
	(*ppGameObj)->cwIntroducePlayers	= (const void *)&cwIntroducePlayers;
	(*ppGameObj)->cwCongratulations		= (const void *)&cwCongratulations;
	(*ppGameObj)->cwDeleteCarriage		= (const void *)&cwDeleteCarriage;
	(*ppGameObj)->cwMainChecking		= (const void *)&cwMainChecking;
	(*ppGameObj)->cwStartGame			= (const void *)&cwStartGame;
	(*ppGameObj)->cwConstructorGame		(ppGameObj);
}

/*
**--------------------------------------------------------------------------------------
*/