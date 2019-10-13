/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayerObject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/13 15:46:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwReadFile(player_t *pPlayerInstance, const char *pFile)
{
	int fd;

	if ((fd = open(pFile, O_RDONLY)) < 0)
		cwErrorCatcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
	if (read(fd, pPlayerInstance->pSource, CODE) < 0)
		cwErrorCatcher(CW_READ_FILE_ERROR, CW_PLAYER);
	close(fd);
}

static void	cwValidatePlayer(player_t *pPlayerInstance)
{
	int		checkSize;

	checkSize = CHAMP_MAX_SIZE - 1;
	if (pPlayerInstance->binaryLabel != COREWAR_EXEC_MAGIC)
		cwErrorCatcher(CW_INCORRECT_BINARY, CW_PLAYER);
	if (pPlayerInstance->codeSize > CHAMP_MAX_SIZE)
		cwErrorCatcher(CW_TOO_BIG_SIZE, CW_PLAYER);
	while (!pPlayerInstance->pCode[checkSize])
		--checkSize;
	if (pPlayerInstance->codeSize != checkSize + 1)
		cwErrorCatcher(CW_CHEAT_DETECT, CW_PLAYER);
}

static void	cwBuildPlayer(player_t *pPlayerInstane)
{
	int		globalIter;
	int		localIter;

	globalIter = 0;
	while (globalIter < BINARY_LABEL)
	{
		pPlayerInstane->binaryLabel |= pPlayerInstane->pSource[globalIter] << ((sizeof(int) - globalIter - 1) * 8);
		++globalIter;
	}
	localIter = 0;
	while (globalIter < NAME)
		pPlayerInstane->pName[localIter++] = pPlayerInstane->pSource[globalIter++];
	pPlayerInstane->pName[localIter] = 0;
	globalIter += NULL_SEPARATOR;
	localIter = 0;
	while (globalIter < CODE_SIZE)
		pPlayerInstane->codeSize |= pPlayerInstane->pSource[globalIter++] << ((sizeof(int) - ++localIter) * 8);
	localIter = 0;
	while (globalIter < COMMENT)
		pPlayerInstane->pComment[localIter++] = pPlayerInstane->pSource[globalIter++];
	pPlayerInstane->pComment[localIter] = 0;
	globalIter += NULL_SEPARATOR;
	localIter = 0;
	while (globalIter < CODE)
		pPlayerInstane->pCode[localIter++] = pPlayerInstane->pSource[globalIter++];
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructorPlayer(player_t **ppPlayerInstance)
{
	if (!((*ppPlayerInstance)->pSource	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*ppPlayerInstance)->pCode	= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*ppPlayerInstance)->pComment	= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*ppPlayerInstance)->pName	= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset((*ppPlayerInstance)->pSource, 0, CODE);
	ft_memset((*ppPlayerInstance)->pCode, 0, CHAMP_MAX_SIZE);
	ft_memset((*ppPlayerInstance)->pComment, 0, COMMENT_LENGTH);
	ft_memset((*ppPlayerInstance)->pName, 0, PROG_NAME_LENGTH);
	(*ppPlayerInstance)->binaryLabel	= 0;
	(*ppPlayerInstance)->carriageId		= 0;
	(*ppPlayerInstance)->codeSize		= 0;
	(*ppPlayerInstance)->pNext			= NULL;
	(*ppPlayerInstance)->pPrev			= NULL;
}

static void	cwDestructorPlayer(player_t **ppPlayerInstance)
{
	free((*ppPlayerInstance)->pSource);
	free((*ppPlayerInstance)->pCode);
	free((*ppPlayerInstance)->pComment);
	free((*ppPlayerInstance)->pName);
	free((*ppPlayerInstance));
	*ppPlayerInstance = NULL;
}

void		cwCreateInstancePlayer(player_t **ppPlayerObj)
{
	if (!(*ppPlayerObj = (player_t *)malloc(sizeof(player_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	(*ppPlayerObj)->cwConstructorPlayer	= (const void *)&cwConstructorPlayer;
	(*ppPlayerObj)->cwDestructorPlayer	= (const void *)&cwDestructorPlayer;
	(*ppPlayerObj)->cwBuildPlayer		= (const void *)&cwBuildPlayer;
	(*ppPlayerObj)->cwValidatePlayer	= (const void *)&cwValidatePlayer;
	(*ppPlayerObj)->cwReadFile			= (const void *)&cwReadFile;
	(*ppPlayerObj)->cwConstructorPlayer	(ppPlayerObj);
}

/*
**--------------------------------------------------------------------------------------
*/