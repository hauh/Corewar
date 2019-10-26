/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:22:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/26 17:10:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMAND_OBJECT_H
# define CW_COMMAND_OBJECT_H

#include "cwTypedefObjects.h"

typedef struct		command_s
{
	int				id;
	int				args;
	int				dir_size;
	int				change_carry;
	int				waiting_time;
	int				type_byte;

	void			(*cw_constructor)	(command_t **);
	void			(*cw_recognize)		(command_t *, int);
	void			(*cw_put_param)		(command_t *, int, int, int, int, int, int, int, int, void (*f)(corewar_t *));
	void			(*cw_callback)		(corewar_t *);
	void			(*cw_destructor)	(command_t **);
}					command_t;

#endif