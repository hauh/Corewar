/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayerObject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 18:13:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwReadFile(player_t *playerInstance, const char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		cwErrorCatcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
	if (read(fd, playerInstance->pSource, CODE) < 0)
		cwErrorCatcher(CW_READ_FILE_ERROR, CW_PLAYER);
	close(fd);
}

void		cwValidatePlayer(player_t *player)
{
	int		checkSize;

	checkSize = CHAMP_MAX_SIZE - 1;
	if (player->binaryLabel != COREWAR_EXEC_MAGIC)
		cwErrorCatcher(CW_INCORRECT_BINARY, CW_PLAYER);
	if (player->codeSize > CHAMP_MAX_SIZE)
		cwErrorCatcher(CW_TOO_BIG_SIZE, CW_PLAYER);
	while (!player->pCode[checkSize])
		--checkSize;
	if (player->codeSize != checkSize + 1)
		cwErrorCatcher(CW_CHEAT_DETECT, CW_PLAYER);
}

void		cwBuildPlayer(player_t *playerInstane)
{
	int		globalIter;
	int		localIter;

	globalIter = 0;
	while (globalIter < BINARY_LABEL)
	{
		playerInstane->binaryLabel |= playerInstane->pSource[globalIter] << ((sizeof(int) - globalIter - 1) * 8);
		++globalIter;
	}
	localIter = 0;
	while (globalIter < NAME)
		playerInstane->pName[localIter++] = playerInstane->pSource[globalIter++];
	playerInstane->pName[localIter] = 0;
	globalIter += NULL_SEPARATOR;
	localIter = 0;
	while (globalIter < CODE_SIZE)
		playerInstane->codeSize |= playerInstane->pSource[globalIter++] << ((sizeof(int) - ++localIter) * 8);
	localIter = 0;
	while (globalIter < COMMENT)
		playerInstane->pComment[localIter++] = playerInstane->pSource[globalIter++];
	playerInstane->pComment[localIter] = 0;
	globalIter += NULL_SEPARATOR;
	localIter = 0;
	while (globalIter < CODE)
		playerInstane->pCode[localIter++] = playerInstane->pSource[globalIter++];
}

void	cwDestructorPlayer(player_t *playerInstance)
{
	free(playerInstance->pSource);
	free(playerInstance->pCode);
	free(playerInstance->pComment);
	free(playerInstance->pName);
	free(playerInstance);
}

void	cwConstructorPlayer(player_t *playerInstance)
{
	if (!(playerInstance->pSource	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->pCode		= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->pComment	= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!(playerInstance->pName		= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset(playerInstance->pSource, 0, CODE);
	ft_memset(playerInstance->pCode, 0, CHAMP_MAX_SIZE);
	ft_memset(playerInstance->pComment, 0, COMMENT_LENGTH);
	ft_memset(playerInstance->pName, 0, PROG_NAME_LENGTH);
	playerInstance->binaryLabel			= 0;
	playerInstance->carriageId			= 0;
	playerInstance->codeSize			= 0;
	playerInstance->cwBuildPlayer		= &cwBuildPlayer;
	playerInstance->cwValidatePlayer	= &cwValidatePlayer;
	playerInstance->cwReadFile			= &cwReadFile;
	playerInstance->pNext				= NULL;
	playerInstance->pPrev				= NULL;
}

void	cwCreateInstancePlayer(player_t **playerObj)
{
	if (!(*playerObj = (player_t *)malloc(sizeof(player_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	(*playerObj)->cwConstructorPlayer	= &cwConstructorPlayer;
	(*playerObj)->cwDestructorPlayer	= &cwDestructorPlayer;
}