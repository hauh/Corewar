/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_obj.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:23:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:29:51 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_BUFFER_OBJ_H
# define CW_BUFFER_OBJ_H

# include "cw_obj_container.h"

# define BU_SHORT_VALUE	p_buffer_instance->s_types.short_value
# define BU_CHAR_VALUE	p_buffer_instance->s_types.char_value
# define BU_INT_VALUE	p_buffer_instance->s_types.int_value
# define BU_DATA		p_buffer_instance->p_data

typedef union		u_types
{
	int				int_value;
	short			short_value;
	char			char_value;
}					t_types;

typedef struct		s_buffer
{
	t_types			s_types;

	t_byte			*p_data;

	void			(*cw_constructor)	(struct s_buffer **);
	void			(*cw_erase_data)	(struct s_buffer *);
	void			(*cw_destructor)	(struct s_buffer **);
}					t_buffer;

void				cw_buffer_functions_linker(t_buffer *p_buffer_instance);

#endif
