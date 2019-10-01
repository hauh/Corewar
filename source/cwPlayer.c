/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 18:58:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** In this chapter we are handling players. To this action we need to read the name,
** comment, code and some small bytes between it. Players writes in list that
** biconnected and looped. It is made for convenience and compatibility with
** carriage list that similar at players list.
*/

void			cwValidatePlayer(player_t *player)
{
	int			check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (player->binary_label != COREWAR_EXEC_MAGIC)
		cwErrorCatcher(CW_INCORRECT_BINARY, CW_PLAYER);
	if (player->code_size > CHAMP_MAX_SIZE)
		cwErrorCatcher(CW_TOO_BIG_SIZE, CW_PLAYER);
	while (!player->code[check_size])
		--check_size;
	if (player->code_size != check_size + 1)
		cwErrorCatcher(CW_CHEAT_DETECT, CW_PLAYER);
}

void		cwBuildPlayer(player_t *player)
{
	int		global_iter;
	int		local_iter;

	global_iter	= 0;
	while (global_iter < BINARY_LABEL)
	{
		player->binary_label |= player->source[global_iter] << ((sizeof(int) - global_iter - 1) * 8);
		++global_iter;
	}
	local_iter	= 0;
	while (global_iter < NAME)
		player->name[local_iter++] = player->source[global_iter++];
	player->name[local_iter] = 0;
	global_iter += NULL_SEPARATOR;
	local_iter	= 0;
	while (global_iter < CODE_SIZE)
		player->code_size |= player->source[global_iter++] << ((sizeof(int) - ++local_iter) * 8);
	local_iter	= 0;
	while (global_iter < COMMENT)
		player->comment[local_iter++] = player->source[global_iter++];
	player->comment[local_iter] = 0;
	global_iter	+= NULL_SEPARATOR;
	local_iter	= 0;
	while (global_iter < CODE)
		player->code[local_iter++] = player->source[global_iter++];
}

void			cwInitializationPlayer(corewar_t *game)
{
	player_t	*new_player;

	if (!(new_player			= (player_t *)malloc(sizeof(player_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(new_player->source	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(new_player->code		= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(new_player->comment	= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(new_player->name		= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset(new_player->source, 0, CODE);
	ft_memset(new_player->code, 0, CHAMP_MAX_SIZE);
	ft_memset(new_player->comment, 0, COMMENT_LENGTH);
	ft_memset(new_player->name, 0, PROG_NAME_LENGTH);
	new_player->binary_label	= 0;
	new_player->carriage_id		= 0;
	new_player->code_size		= 0;
	new_player->id				= ++game->players_amount;
	if (!game->players)
	{
		game->players = new_player;
		game->players->next = game->players;
		game->players->prev = game->players;
	}
	else
	{
		new_player->prev = game->players->prev;
		new_player->next = game->players;
		game->players->prev->next = new_player;
		game->players->prev = new_player;
	}
}

void			cwInitializationPlayers(corewar_t *game, char **argv, int argc)
{
	int			iter;
	int			fd;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < argc)
	{
		if (argv[iter][0] != '*')
		{
			cwInitializationPlayer(game);
			if ((fd = open(argv[iter], O_RDONLY)) < 0)
				cwErrorCatcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
			if (read(fd, game->players->prev->source, CODE) < 0)
				cwErrorCatcher(CW_READ_FILE_ERROR, CW_PLAYER);
			cwBuildPlayer(game->players->prev);
			cwValidatePlayer(game->players->prev);
			close(fd);
		}
		++iter;
	}
	if (game->players_amount < 1)
		cwErrorCatcher(CW_INVALID_PLAYERS, CW_PLAYER);
	game->destructor->players_detect = CW_TRUE;
}