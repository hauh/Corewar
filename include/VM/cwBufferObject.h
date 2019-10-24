/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:23:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/20 17:30:02 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_BUFFER_OBJECT_H
# define CW_BUFFER_OBJECT_H

# include "cwTypedefObjects.h"

typedef union		types_u
{
	int				intValue;
	short			shortValue;
	char			charValue;
}					types_t;

typedef struct 		buffer_s
{
	types_t			sTypes;

	unsigned char	*pData;

	void			(*cwConstructor)	(buffer_t **);
	void			(*cwDestructor)		(buffer_t **);
}					buffer_t;

#endif
