/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/24 15:03:15 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

#include "cwTypedefObjects.h"

#define	CW_COMMAND_AMOUNT	16 + 1

typedef struct			corewar_s
{
	flag_t				loadDump;
	flag_t				visualizator;

	int					playersAmount;
	int					commandsAmount;
	int					carriagesAmount;
	int					queueSize;

	carriage_t			*pCarriageObj;
	carriage_t			*pWaitingQueue;
	command_t			*paCommands[CW_COMMAND_AMOUNT];
	player_t			*pPlayerObj;
	arena_t				*pArenaObj;

	void				(*cwConstructor)		(corewar_t **);
	void				(*cwCarriageObjInit)	(corewar_t *);
	void				(*cwCommandObjInit)		(corewar_t *);
	void				(*cwPlayerObjInit)		(corewar_t *, int, char **);
	void				(*cwArenaObjInit)		(corewar_t *);
	void				(*cwAddCarriageToList)	(corewar_t *, carriage_t *);
	void				(*cwAddPlayerToList)	(corewar_t *, player_t *);
	void				(*cwFreeAllCarriages)	(corewar_t *);
	void				(*cwFreeAllPlayers)		(corewar_t *);
	void 				(*cwFreeAllCommand)		(corewar_t *);
	void				(*cwArrangeUnitsOnField)(corewar_t *);
	void				(*cwIntroducePlayers)	(corewar_t *);
	void				(*cwCongratulations)	(corewar_t *);
	void				(*cwDeleteCarriage)		(corewar_t *, int *);
	void				(*cwMainChecking)		(corewar_t *);
	void				(*cwStartGame)			(corewar_t *);
	void				(*cwPushToQueue)		(corewar_t *, carriage_t *);
	void				(*cwMergeQueueToList)	(corewar_t *);
	void				(*cwDestructor)			(corewar_t **);
}						corewar_t;

#endif
