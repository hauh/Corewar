/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/04 20:01:41 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** In this chapter we are handling players. To this action we need to read the name,
** comment, code and some small bytes between it. Players writes in list that
** biconnected and looped. It is made for convenience and compatibility with
** carriage list that similar at players list.
*/

void	cwReadFile(player_t *playerInstance, const char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		cwErrorCatcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
	if (read(fd, playerInstance->source, CODE) < 0)
		cwErrorCatcher(CW_READ_FILE_ERROR, CW_PLAYER);
	close(fd);
}

void		cwValidatePlayer(player_t *player)
{
	int		check_size;

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

void		cwBuildPlayer(player_t *playerInstane)
{
	int		global_iter;
	int		local_iter;

	global_iter	= 0;
	while (global_iter < BINARY_LABEL)
	{
		playerInstane->binary_label |= playerInstane->source[global_iter] << ((sizeof(int) - global_iter - 1) * 8);
		++global_iter;
	}
	local_iter	= 0;
	while (global_iter < NAME)
		playerInstane->name[local_iter++] = playerInstane->source[global_iter++];
	playerInstane->name[local_iter] = 0;
	global_iter += NULL_SEPARATOR;
	local_iter	= 0;
	while (global_iter < CODE_SIZE)
		playerInstane->code_size |= playerInstane->source[global_iter++] << ((sizeof(int) - ++local_iter) * 8);
	local_iter	= 0;
	while (global_iter < COMMENT)
		playerInstane->comment[local_iter++] = playerInstane->source[global_iter++];
	playerInstane->comment[local_iter] = 0;
	global_iter	+= NULL_SEPARATOR;
	local_iter	= 0;
	while (global_iter < CODE)
		playerInstane->code[local_iter++] = playerInstane->source[global_iter++];
}

void	cwDestructorPlayer(player_t *playerInstance)
{
	free(playerInstance->source);
	free(playerInstance->code);
	free(playerInstance->comment);
	free(playerInstance->name);
	free(playerInstance);
}

void	cwConstructorPlayer(player_t *playerInstance)
{
	if (!(playerInstance->source	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->code		= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->comment	= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->name		= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset(playerInstance->source, 0, CODE);
	ft_memset(playerInstance->code, 0, CHAMP_MAX_SIZE);
	ft_memset(playerInstance->comment, 0, COMMENT_LENGTH);
	ft_memset(playerInstance->name, 0, PROG_NAME_LENGTH);
	playerInstance->binary_label		= 0;
	playerInstance->carriage_id			= 0;
	playerInstance->code_size			= 0;
	playerInstance->cwBuildPlayer		= &cwBuildPlayer;
	playerInstance->cwValidatePlayer	= &cwValidatePlayer;
	playerInstance->cwReadFile			= &cwReadFile;
	playerInstance->next				= NULL;
	playerInstance->prev				= NULL;
}

void	cwCreateInstancePlayer(player_t **playerObj)
{
	if (!(*playerObj = (player_t *)malloc(sizeof(player_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	(*playerObj)->cwConstructorPlayer	= &cwConstructorPlayer;
	(*playerObj)->cwDestructorPlayer	= &cwDestructorPlayer;
}