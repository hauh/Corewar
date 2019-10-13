/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwGameObject.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 15:35:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

#include "cwTypedefObjects.h"

#define	CW_COMMAND_AMOUNT	16 + 1

typedef struct				corewar_s
{
	int						playersAmount;
	int						commandsAmount;
	int						carriagesAmount;

	carriage_t				*pCarriageObject;
	command_t				*paCommands[CW_COMMAND_AMOUNT];
	player_t				*pPlayerObject;
	arena_t					*pArenaObject;
	key_t					*pKeyObject;

	const void				(*cwConstructorGame)	(corewar_t **);
	const void				(*cwCarraigeObjectInit)	(corewar_t *);
	const void				(*cwCommandObjectInit)	(corewar_t *);
	const void				(*cwPlayerObjectInit)	(corewar_t *, int, char **);
	const void				(*cwArenaObjectInit)	(corewar_t *);
	const void				(*cwKeyObjectInit)		(corewar_t *, int, char **);
	const void				(*cwAddCarriageToList)	(corewar_t *, carriage_t *);
	const void				(*cwAddPlayerToList)	(corewar_t *, player_t *);
	const void				(*cwFreeAllCarriages)	(corewar_t *);
	const void				(*cwFreeAllPlayers)		(corewar_t *);
	const void 				(*cwFreeAllCommand)		(corewar_t *);
	const void				(*cwArrangeUnitsOnField)(corewar_t *);
	const void				(*cwIntroducePlayers)	(corewar_t *);
	const void				(*cwCongratulations)	(corewar_t *);
	const void				(*cwDeleteCarriage)		(corewar_t *, int *);
	const void				(*cwMainChecking)		(corewar_t *);
	const void				(*cwStartGame)			(corewar_t *);
	const void				(*cwDestructorGame)		(corewar_t **);
}							corewar_t;

#endif
