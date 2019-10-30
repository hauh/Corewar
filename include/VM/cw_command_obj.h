/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_obj.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:22:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 15:40:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMAND_OBJECT_H
# define CW_COMMAND_OBJECT_H

#include "cw_obj_container.h"

typedef struct		s_command
{
	int				id;
	int				args;
	int				dir_size;
	int				change_carry;
	int				waiting_time;
	int				type_byte;

	void			(*cw_constructor)	(t_command **);
	void			(*cw_recognize)		(t_command *, int);
	void			(*cw_put_param)		(t_command *, int, int, int, int, int, int, int, int, void (*f)(t_corewar *));
	void			(*cw_callback)		(t_corewar *);
	void			(*cw_destructor)	(t_command **);
}					t_command;

void	cw_put_param(t_command *p_command_instance, int id, int first_arg, int second_arg, int third_arg, int dir_size, int change_carry, int waiting_time, int type_byte, void (*f)(t_corewar *));
void	cw_recognize_command(t_command *p_command_instance, int command);

#endif