/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:20:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwConstructorBuffer(buffer_t **ppBufferInstance)
{
	if (!((*ppBufferInstance)->pData = (unsigned char *)malloc(sizeof(unsigned char) * CW_REG_AMOUNT)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppBufferInstance)->intValue	= 0;
	(*ppBufferInstance)->charValue	= 0;
	(*ppBufferInstance)->shortValue	= 0;
}

void	cwDestructorBuffer(buffer_t **ppBufferInstance)
{
	free((*ppBufferInstance)->pData);
	free(*ppBufferInstance);
	*ppBufferInstance = NULL;
}

void	cwCreateInstanceBuffer(buffer_t **ppBufferObj)
{
	if (!(*ppBufferObj = (buffer_t *)malloc(sizeof(buffer_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppBufferObj)->cwConstructorBuffer	= (const void *)&cwConstructorBuffer;
	(*ppBufferObj)->cwDestructorBuffer	= (const void *)&cwDestructorBuffer;
	(*ppBufferObj)->cwConstructorBuffer	(ppBufferObj);
}