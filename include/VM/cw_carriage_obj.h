/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_obj.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 17:05:49 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_CARRIAGE_OBJECT_H
# define CW_CARRIAGE_OBJECT_H

# include "cw_obj_container.h"

typedef struct			s_carriage
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

	struct s_carriage	*p_next;
	struct s_carriage	*p_prev;

	t_command			**pp_command_container;
	t_command			*p_current_command;
	t_player			*p_owner;

	void				(*cw_constructor)				(t_carriage **);
	void				(*cw_save_pos)					(t_carriage *, t_flag);
	void				(*cw_exec_command)				(t_carriage *, t_corewar *);
	void				(*cw_set_command_time)			(t_carriage *, t_arena *);
	void				(*cw_reduce_time)				(t_carriage *);
	void				(*cw_parse_types)				(t_carriage *, t_arena *);
	void				(*cw_move_to)					(t_carriage *, int);
	void 				(*cw_carriage_return)			(t_carriage *, int);
	void				(*cw_skip_damaged_command)		(t_carriage *, t_arena *);
	void				(*cw_set_owner)					(t_carriage *, t_player *, int);
	void				(*cw_conversion_value_to_bytes)	(t_carriage *, t_buffer *, int);
	void				(*cw_conversion_bytes_to_value)	(t_carriage *, t_buffer *, int);
	void				(*cw_write_operation)			(t_carriage *, t_arena *, t_buffer *, int);
	void				(*cw_read_operation)			(t_carriage *, t_arena *, t_buffer *, int);
	void				(*cw_check_carry)				(t_carriage *);
	void 				(*cw_write_owner_id_to_reg)		(t_carriage *);
	void				(*cw_copy_reg)					(t_carriage *, t_carriage *);
	void				(*cw_reg_check)					(t_carriage *, t_arena *, int);
	void				(*cw_destructor)				(t_carriage **);
}						t_carriage;

void	cw_reg_check(t_carriage *p_carriage_instance, t_arena *p_arena_obj, int type);
void	cw_copy_reg(t_carriage *p_carriage_instance, t_carriage *p_copying_carriage);
void	cw_write_owner_id_to_reg(t_carriage *p_carriage_instance);
void	cw_check_carry(t_carriage *p_carriage_instance);
void	cw_conversion_value_to_bytes(t_carriage *pCarraigeInstance, t_buffer *pBufferObj, int type);
void	cw_conversion_bytes_to_value(t_carriage *pCarraigeInstance, t_buffer *pBufferObj, int type);
void	cw_write_operation(t_carriage *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg);
void	cw_read_operation(t_carriage *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg);
void	cw_parse_types(t_carriage *p_carriage_instance, t_arena *p_arena_obj);
void	cw_carriage_return(t_carriage *p_carriage_instance, int whereExactly);
void	cw_move_to(t_carriage *pCarraigeInstance, int distance);
void	cw_save_pos(t_carriage *p_carriage_instance, int whichExactly);
void	cw_reduce_waiting_time(t_carriage *pCarraigeInstance);
void	cw_exec_command(t_carriage *p_carriage_instance, t_corewar *pGameInstance);
void	cw_set_t_commandime(t_carriage *p_carriage_instance, t_arena *pArenaInstance);
void	cw_set_owner(t_carriage *p_carriage_instance, t_player *pPlayerList, int playersAmount);
void	cw_skip_damaged_command(t_carriage *p_carriage_instance, t_arena *p_arena_obj);

#endif
