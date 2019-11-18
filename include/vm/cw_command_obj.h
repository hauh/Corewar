/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_obj.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:22:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 17:09:54 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMAND_OBJ_H
# define CW_COMMAND_OBJ_H

# include "cw_obj_container.h"

# define CO_ID_I			p_command_instance->id
# define CO_ARGS_I			p_command_instance->args
# define CO_DIR_SIZE_I		p_command_instance->dir_size
# define CO_CALLBACK_I		p_command_instance->cw_callback
# define CO_TYPE_BYTE_I		p_command_instance->type_byte
# define CO_CHANGE_CARRY_I	p_command_instance->change_carry
# define CO_WAITING_TIME_I	p_command_instance->waiting_time

# define CO_ID_O			p_command_obj->id
# define CO_ARGS_O			p_command_obj->args
# define CO_DIR_SIZE_O		p_command_obj->dir_size
# define CO_CALLBACK_O		p_command_obj->cw_callback
# define CO_TYPE_BYTE_O		p_command_obj->type_byte
# define CO_CHANGE_CARRY_O	p_command_obj->change_carry
# define CO_WAITING_TIME_O	p_command_obj->waiting_time

# define CO_LIVE			0x01L
# define CO_LD				0x02L
# define CO_ST				0x03L
# define CO_ADD				0x04L
# define CO_SUB				0x05L
# define CO_AND				0x06L
# define CO_OR				0x07L
# define CO_XOR				0x08L
# define CO_ZJMP			0x09L
# define CO_LDI				0x0aL
# define CO_STI				0x0bL
# define CO_FORK			0x0cL
# define CO_LLD				0x0dL
# define CO_LLDI			0x0eL
# define CO_LFORK			0x0fL
# define CO_AFF				0x10L

# define CO_OBJECT_NAME		"COMMAND"
# define CO_OBJECT_ERROR	"Memory for COMMAND has not been allocated"

# define CO_NAMELESS		-7

typedef struct				s_command
{
	t_attribute	id;
	t_attribute	args;
	t_attribute	dir_size;
	t_attribute	change_carry;
	t_attribute	waiting_time;
	t_attribute	type_byte;

	void		(*cw_callback)(t_corewar *);

	t_method	(*cw_constructor)
				(struct s_command **);
	t_method	(*cw_recognize)
				(struct s_command *, int);
	t_method	(*cw_put_param)
				(struct s_command *, size_t, void (*f)(t_corewar *));
	t_method	(*cw_destructor)
				(struct s_command **);
}							t_command;

void						cw_create_instance_command
							(t_command **pp_command_obj);
void						cw_command_functions_linker
							(t_command *p_command_instance);

#endif
