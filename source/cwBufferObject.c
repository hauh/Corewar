/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:41:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/05 17:50:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwConstructorBuffer(buffer_t *bufferInstance)
{
	if (!(bufferInstance->data = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	bufferInstance->intValue = 0;
	bufferInstance->charValue = 0;
	bufferInstance->shortValue = 0;
}

void	cwDestructorBuffer(buffer_t *bufferInstance)
{
	free(bufferInstance->data);
	free(bufferInstance);
}

void	cwCreateInstanceBuffer(buffer_t **bufferObj)
{
	if (!(*bufferObj = (buffer_t *)malloc(sizeof(buffer_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*bufferObj)->cwConstructorBuffer	= &cwConstructorBuffer;
	(*bufferObj)->cwDestructorBuffer	= &cwDestructorBuffer;
}