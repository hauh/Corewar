/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/04 20:01:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cwAddCarriageToList(corewar_t *gameInstance, carriage_t *carriageAdding)
{
	if (!gameInstance->pCarriageObject)
	{
		gameInstance->pCarriageObject			= carriageAdding;
		gameInstance->pCarriageObject->next		= carriageAdding;
		gameInstance->pCarriageObject->prev		= carriageAdding;
	}
	else
	{
		carriageAdding->next					= gameInstance->pCarriageObject;
		carriageAdding->prev					= gameInstance->pCarriageObject->prev;
		gameInstance->pPlayerObject->prev->next	= carriageAdding;
		gameInstance->pPlayerObject->prev		= carriageAdding;
	}
}

void	cwAddPlayerToList(corewar_t *gameInstance, player_t *playerAdding)
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

void			cwCarriageObjectInit(corewar_t *gameInstance)
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
		cwConversionIntToBytes(game->carriages->prev->registers, &owner_id, 0);
		game->players = game->players->next;
		++iter;
	}
	game->destructor->carriages_detect = CW_TRUE;
}

void			cwPlayerObjectInit(corewar_t *gameInstance, char **argv, int argc)
{
	player_t	*playerObj;
	int			iter;

	iter			= CW_BEGIN_FROM_ONE;
	playerObj		= NULL;
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

void			cwKeyObjectInit(corewar_t *gameInstance, int argc, char **argv)
{
	key_t		*keyObj;

	cwCreateInstanceKey			(&keyObj);
	keyObj->cwConstructorKey	(keyObj);
	keyObj->cwValidateArgs		(keyObj, argc, argv);
	keyObj->cwReadKeys			(keyObj, argc, argv);
	gameInstance->pKeyObject	= keyObj;
}

void			cwConstructorGame(corewar_t *gameInstance)
{
	gameInstance->playersAmount			= 0;
	gameInstance->commandsAmount		= 0;
	gameInstance->carriagesAmount		= 0;
	gameInstance->pCarriageObject		= NULL;
	gameInstance->pPlayerObject			= NULL;
	gameInstance->pArenaObject			= NULL;
	gameInstance->pKeyObject			= NULL;
	gameInstance->cwAddPlayerToList		= &cwAddPlayerToList;
	gameInstance->cwAddCarriageToList	= &cwAddCarriageToList;
	gameInstance->cwKeyObjectInit		= &cwKeyObjectInit;
	gameInstance->cwPlayerObjectInit	= &cwPlayerObjectInit;
	gameInstance->cwCarraigeObjectInit	= NULL;
	gameInstance->cwArenaObjectInit		= NULL;
	gameInstance->cwCommandObjectInit	= NULL;
	gameInstance->cwIntroducePlayers	= NULL;
	gameInstance->cwStartGame			= NULL;
}

void			cwDestructorGame(corewar_t *gameInstance)
{
	free(gameInstance);
}

void			cwCreateInstanceGame(corewar_t **gameObj)
{
	if (!(*gameObj = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	(*gameObj)->cwConstructorGame	= &cwConstructorGame;
	(*gameObj)->cwDestructorGame	= &cwDestructorGame;
}