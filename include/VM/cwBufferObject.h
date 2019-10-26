/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwBufferObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:23:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 14:09:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_BUFFER_OBJECT_H
# define CW_BUFFER_OBJECT_H

# include "cwTypedefObjects.h"

typedef union		types_u
{
	int				int_value;
	short			short_value;
	char			char_value;
}					types_t;

typedef struct 		buffer_s
{
	types_t			s_types;

	unsigned char	*p_data;

	void			(*cw_constructor)	(buffer_t **);
	void			(*cw_erase_data)	(buffer_t *);
	void			(*cw_destructor)	(buffer_t **);
}					buffer_t;

#endif
