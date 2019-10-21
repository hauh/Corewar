/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/20 17:52:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwConstructor(buffer_t **ppBufferInstance)
{
	if (!((*ppBufferInstance)->pData = (unsigned char *)malloc(sizeof(unsigned char) * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppBufferInstance)->sTypes.intValue	= 0;
	(*ppBufferInstance)->sTypes.charValue	= 0;
	(*ppBufferInstance)->sTypes.shortValue	= 0;
}

static void	cwDestructor(buffer_t **ppBufferInstance)
{
	free((*ppBufferInstance)->pData);
	free(*ppBufferInstance);
	*ppBufferInstance = NULL;
}

extern void	cwCreateInstanceBuffer(buffer_t **ppBufferObj)
{
	if (!(*ppBufferObj = (buffer_t *)malloc(sizeof(buffer_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*ppBufferObj)->cwConstructor		= &cwConstructor;
	(*ppBufferObj)->cwDestructor		= &cwDestructor;
	(*ppBufferObj)->cwConstructor		(ppBufferObj);
}