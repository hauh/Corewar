/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 14:14:05 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			validate_player(player_t *player)
{
	int			check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (player->binary_label != COREWAR_EXEC_MAGIC)
		error_catcher(INCORRECT_BINARY, PLAYER);
	if (player->code_size > CHAMP_MAX_SIZE)
		error_catcher(TOO_BIG_SIZE, PLAYER);
	while (!player->code[check_size])
		--check_size;
	if (player->code_size != check_size + 1)
		error_catcher(CHEAT_DETECT, PLAYER);
}

void		initialization_player(corewar_t *game)
{
	player_t	*new_player;

	if (!(new_player			= (player_t *)malloc(sizeof(player_t))))
		error_catcher(MEMORY_ALLOC_ERROR, PLAYER);
	if (!(new_player->source	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		error_catcher(MEMORY_ALLOC_ERROR, PLAYER);
	ft_memset(new_player->source, 0, CODE);
	if (!(new_player->code		= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, PLAYER);
	ft_memset(new_player->code, 0, CHAMP_MAX_SIZE);
	if (!(new_player->comment	= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		error_catcher(MEMORY_ALLOC_ERROR, PLAYER);
	ft_memset(new_player->comment, 0, COMMENT_LENGTH);
	if (!(new_player->name		= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		error_catcher(MEMORY_ALLOC_ERROR, PLAYER);
	ft_memset(new_player->name, 0, PROG_NAME_LENGTH);
	new_player->id				= ++game->players_amount;
	new_player->code_size		= 0;
	new_player->carriage_id		= 0;
	new_player->binary_label	= 0;
	new_player->next			= NULL;
	new_player->prev			= NULL;
	if (!game->players)
		game->players = new_player;
	else
	{
		game->players->prev = new_player;
		game->players->prev->next = game->players;
		game->players = game->players->prev;
	}
}

void		build_player(player_t *player)
{
	int		global_iter;
	int		local_iter;

	global_iter	= 0;
	while (global_iter < BINARY_LABEL)
		player->binary_label |= player->source[global_iter] << ((sizeof(int) - ++global_iter) * 8);
	local_iter = 0;
	while (global_iter < NAME)
		player->name[local_iter++] = player->source[global_iter++];
	player->name[local_iter] = 0;
	global_iter += NULL_SEPARATOR;
	local_iter = 0;
	while (global_iter < CODE_SIZE)
		player->code_size |= player->source[global_iter++] << ((sizeof(int) - ++local_iter) * 8);
	local_iter = 0;
	while (global_iter < COMMENT)
		player->comment[local_iter++] = player->source[global_iter++];
	player->comment[local_iter] = 0;
	global_iter += NULL_SEPARATOR;
	local_iter = 0;
	while (global_iter < CODE)
		player->code[local_iter++]	= player->source[global_iter++];
}

void			initialization_players(corewar_t *game, char **argv, int argc)
{
	int			iter;
	int			fd;

	iter = 1;
	while (iter < argc)
	{
		if (argv[iter][0] != '*')
		{
			initialization_player(game);
			if ((fd = open(argv[iter], O_RDONLY)) < 0)
				error_catcher(OPEN_FILE_ERROR, PLAYER);
			if (read(fd, game->players->source, CODE) < 0)
				error_catcher(READ_FILE_ERROR, PLAYER);
			build_player(game->players);
			validate_player(game->players);
			close(fd);
		}
		++iter;
	}
	if (game->players_amount < 1)
		error_catcher(INVALID_PLAYERS, PLAYER);
	game->destructor->players_detect = TRUE;
}