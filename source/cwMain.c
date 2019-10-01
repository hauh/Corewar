/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 17:18:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Program entry point. All Corewars's modules initialized here.
** In corewar_t structure is all players, carriages, arena, keys, visualizator,
** desturctor (for detect memory alloc and free it later), some int variable
** for destignation of amount players and carriages.
** Further the game is starting.
*/

void			cwInitializationGame(corewar_t **game)
{
	corewar_t	*new_game;

	if (!(new_game = (corewar_t *)malloc(sizeof(corewar_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_GAME);
	new_game->players_amount	= 0;
	new_game->carriages_amount	= 0;
	new_game->commands_amount	= 0;
	new_game->destructor		= NULL;
	new_game->carriages			= NULL;
	new_game->players			= NULL;
	new_game->arena				= NULL;
	new_game->keys				= NULL;
	new_game->vis				= NULL;
	*game						= new_game;
}

int				main(int argc, char **argv)
{
	corewar_t	*game;

	cwInitializationGame		(&game);
	cwInitializationDestructor	(game);
	cwInitializationKeys		(game, argv, argc);
	cwInitializationPlayers		(game, argv, argc);
	cwInitializationCarriages	(game);
	cwInitializationArena		(game);
	cwInitializationCommands	(game);
	cwIntroducePlayers			(game);
	cwHereWeGo					(game);
	return (0);
}
