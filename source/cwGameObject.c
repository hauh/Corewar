/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 19:38:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
			gameInstance->pArenaObject->field[playerLocation++] = gameInstance->pPlayerObject->pCode[codeIter++];
		gameInstance->pPlayerObject		= gameInstance->pPlayerObject->pNext;
		gameInstance->pCarriageObject	= gameInstance->pCarriageObject->pNext;
		++iter;
	}
}

static void		cwIntroducePlayers(corewar_t *gameInstance)
{
	int			iter;

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

static void		cwAddCarriageToList(corewar_t *gameInstance, carriage_t *carriageAdding)
{
	if (!gameInstance->pCarriageObject)
	{
		gameInstance->pCarriageObject			= carriageAdding;
		gameInstance->pCarriageObject->pNext	= carriageAdding;
		gameInstance->pCarriageObject->pPrev	= carriageAdding;
	}
	else
	{
		carriageAdding->pNext						= gameInstance->pCarriageObject;
		carriageAdding->pPrev						= gameInstance->pCarriageObject->pPrev;
		gameInstance->pPlayerObject->pPrev->pNext	= carriageAdding;
		gameInstance->pPlayerObject->pPrev			= carriageAdding;
	}
}

static void		cwAddPlayerToList(corewar_t *gameInstance, player_t *playerAdding)
{
	if (!gameInstance->pPlayerObject)
	{
		gameInstance->pPlayerObject				= playerAdding;
		gameInstance->pPlayerObject->next		= playerAdding;
		gameInstance->pPlayerObject->prev		= playerAdding;
	}
	else
	{
		playerAdding->next						= gameInstance->pPlayerObject;
		playerAdding->prev						= gameInstance->pPlayerObject->prev;
		gameInstance->pPlayerObject->prev->next	= playerAdding;
		gameInstance->pPlayerObject->prev		= playerAdding;
	}
}

static void		cwCommandObjectInit(corewar_t *gameInstance)
{
	command_t	*commandObj;
	int			iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cwCreateInstanceCommand(&commandObj);
		commandObj->cwConstructorCommand(commandObj);
		commandObj->cwRecognizeCommand(commandObj, iter);
		gameInstance->paCommands[iter] = commandObj;
		++iter;
	}
}

static void		cwArenaObjectInit	(corewar_t *gameInstance)
{
	arena_t		*arenaObj;

	cwCreateInstanceArena		(&arenaObj);
	arenaObj->cwConstructorArena(arenaObj);
	arenaObj->cwBufferInit		(arenaObj);
	gameInstance->pArenaObject = arenaObj;
}

static void		cwCarriageObjectInit(corewar_t *gameInstance)
{
	carriage_t	*carriageObj;
	int			iter;
	int			owner_id;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < gameInstance->playersAmount)
	{
		cwCreateInstanceCarriage(&carriageObj);
		carriageObj->cwConstructorCarriage(carriageObj);
		owner_id = -gameInstance->pPlayerObject->id;
		gameInstance->pPlayerObject = gameInstance->pPlayerObject->pNext;
		++iter;
	}
}

static void		cwPlayerObjectInit(corewar_t *gameInstance, char **argv, int argc)
{
	player_t	*playerObj;
	int			iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (argv[iter][0] != '*')
		{
			cwCreateInstancePlayer			(&playerObj);
			playerObj->cwConstructorPlayer	(playerObj);
			playerObj->cwReadFile			(playerObj, argv[iter]);
			playerObj->cwBuildPlayer		(playerObj);
			playerObj->cwValidatePlayer		(playerObj);
			playerObj->id					= ++gameInstance->playersAmount;
			gameInstance->cwAddPlayerToList	(gameInstance, playerObj);
		}
		++iter;
	}
	if (gameInstance->playersAmount < 1)
		cwErrorCatcher(CW_INVALID_PLAYERS, CW_PLAYER);
}

static void		cwKeyObjectInit(corewar_t *gameInstance, int argc, char **argv)
{
	key_t		*keyObj;

	cwCreateInstanceKey			(&keyObj);
	keyObj->cwConstructorKey	(keyObj);
	keyObj->cwValidateArgs		(keyObj, argc, argv);
	keyObj->cwReadKeys			(keyObj, argc, argv);
	gameInstance->pKeyObject	= keyObj;
}

static void		cwConstructorGame(corewar_t **gameInstance)
{
	(*gameInstance)->playersAmount			= 0;
	(*gameInstance)->commandsAmount			= 0;
	(*gameInstance)->carriagesAmount		= 0;
	(*gameInstance)->pCarriageObject		= NULL;
	(*gameInstance)->pPlayerObject			= NULL;
	(*gameInstance)->pArenaObject			= NULL;
	(*gameInstance)->pKeyObject				= NULL;
	(*gameInstance)->cwKeyObjectInit		= &cwKeyObjectInit;
	(*gameInstance)->cwPlayerObjectInit		= &cwPlayerObjectInit;
	(*gameInstance)->cwCarraigeObjectInit	= &cwCarriageObjectInit;
	(*gameInstance)->cwCommandObjectInit	= &cwCommandObjectInit;
	(*gameInstance)->cwArenaObjectInit		= &cwArenaObjectInit;
	(*gameInstance)->cwAddPlayerToList		= &cwAddPlayerToList;
	(*gameInstance)->cwAddCarriageToList	= &cwAddCarriageToList;
	(*gameInstance)->cwIntroducePlayers		= &cwIntroducePlayers;
	(*gameInstance)->cwStartGame			= &cwStartGame;
}

static void		cwDestructorGame(corewar_t **gameInstance)
{
	(*gameInstance)->cwFreeAllCarriages					(gameInstance);
	(*gameInstance)->cwFreeAllPlayers					(gameInstance);
	(*gameInstance)->pArenaObject->cwDestructorArena	((*gameInstance)->pArenaObject);
	(*gameInstance)->pKeyObject->cwDestructorKey		((*gameInstance)->pKeyObject);
	free(*gameInstance);
	*gameInstance = NULL;
}

void			cwCreateInstanceGame(corewar_t **gameObj)
{
	if (!(*gameObj = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	(*gameObj)->cwConstructorGame	= &cwConstructorGame;
	(*gameObj)->cwDestructorGame	= &cwDestructorGame;
}