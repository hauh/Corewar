/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:23:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 19:36:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_BUFFER_OBJECT_H
# define CW_BUFFER_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct 				buffer_s
{
	int						intValue;
	char					charValue;
	short					shortValue;

	unsigned char			*pData;

	const void				(*cwConstructorBuffer)	(buffer_t *);
	const void				(*cwDestructorBuffer)	(buffer_t *);
}							buffer_t;

#endif
