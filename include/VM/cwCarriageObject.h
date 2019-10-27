/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 17:51:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_CARRIAGE_OBJECT_H
# define CW_CARRIAGE_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct			carriage_s
{
	int					id;
	int					carry;
	int					odometer;
	int					save_point;
	int					waiting_time;
	int					addit_odometer;
	int					last_speak_cycle;
	int					addit_save_point;
	int					current_location;
	char				current_register;
	int					error_ocurred;
	int					first_arg;
	int					second_arg;
	int					third_arg;
	int					offset;
	int					checked;

	unsigned char		*p_registers;

	struct carriage_s	*p_next;
	struct carriage_s	*p_prev;

	command_t			**pp_command_container;
	command_t			*p_current_command;
	player_t			*p_owner;

	void				(*cw_constructor)				(carriage_t **);
	void				(*cw_save_pos)					(carriage_t *, flag_t);
	void				(*cw_exec_command)				(carriage_t *, corewar_t *);
	void				(*cw_set_command_time)			(carriage_t *, arena_t *);
	void				(*cw_reduce_time)				(carriage_t *);
	void				(*cw_parse_types)				(carriage_t *, arena_t *);
	void				(*cw_move_to)					(carriage_t *, int);
	void 				(*cw_carriage_return)			(carriage_t *, int);
	void				(*cw_return_protocol_activate)	(carriage_t *, arena_t *);
	void				(*cw_set_owner)					(carriage_t *, player_t *, int);
	void				(*cw_conversion_value_to_bytes)	(carriage_t *, buffer_t *, int);
	void				(*cw_conversion_bytes_to_value)	(carriage_t *, buffer_t *, int);
	void				(*cw_write_operation)			(carriage_t *, arena_t *, buffer_t *, int);
	void				(*cw_read_operation)			(carriage_t *, arena_t *, buffer_t *, int);
	void				(*cw_check_carry)				(carriage_t *);
	void 				(*cw_write_owner_id_to_reg)		(carriage_t *);
	void				(*cw_copy_reg)					(carriage_t *, carriage_t *);
	void				(*cw_reg_check)					(carriage_t *, arena_t *, int);
	void				(*cw_destructor)				(carriage_t **);
}						carriage_t;

#endif
