/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_arena_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:07:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/15 17:45:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ARENA_OBJ_H
# define CW_ARENA_OBJ_H

# include "cw_obj_container.h"

# define AR_CYCLE_I			p_arena_instance->cycle
# define AR_WINNER_I		p_arena_instance->p_winner
# define AR_CYCLE_TO_DIE_I	p_arena_instance->cycle_to_die
# define AR_CHECK_AMOUNT_I	p_arena_instance->check_amount
# define AR_LIVE_AMOUNT_I	p_arena_instance->live_amount
# define AR_BUFFERS_I		p_arena_instance->pa_buffer_set
# define AR_FIELD_I			p_arena_instance->p_field
# define AR_NCURSES_I		p_arena_instance->ncurses
# define AR_STEALTH_I		p_arena_instance->stealth
# define AR_SPARE_BUF_I		AR_BUFFERS_I[CW_SPARE_BUF]
# define AR_SYSTEM_BUF_I	AR_BUFFERS_I[CW_SYSTEM_BUF]
# define AR_VALUE_BUF_1_I	AR_BUFFERS_I[CW_VALUE_BUF_1]
# define AR_VALUE_BUF_2_I	AR_BUFFERS_I[CW_VALUE_BUF_2]
# define AR_VALUE_BUF_3_I	AR_BUFFERS_I[CW_VALUE_BUF_3]

# define AR_CYCLE_O			p_arena_obj->cycle
# define AR_WINNER_O		p_arena_obj->p_winner
# define AR_CYCLE_TO_DIE_O	p_arena_obj->cycle_to_die
# define AR_CHECK_AMOUNT_O	p_arena_obj->check_amount
# define AR_LIVE_AMOUNT_O	p_arena_obj->live_amount
# define AR_BUFFERS_O		p_arena_obj->pa_buffer_set
# define AR_FIELD_O			p_arena_obj->p_field
# define AR_NCURSES_O		p_arena_obj->ncurses
# define AR_STEALTH_O		p_arena_obj->stealth
# define AR_SYSTEM_BUF_O	AR_BUFFERS_O[CW_SYSTEM_BUF]
# define AR_SPARE_BUF_O		AR_BUFFERS_O[CW_SPARE_BUF]
# define AR_SYSTEM_BUF_O	AR_BUFFERS_O[CW_SYSTEM_BUF]
# define AR_VALUE_BUF_1_O	AR_BUFFERS_O[CW_VALUE_BUF_1]
# define AR_VALUE_BUF_2_O	AR_BUFFERS_O[CW_VALUE_BUF_2]
# define AR_VALUE_BUF_3_O	AR_BUFFERS_O[CW_VALUE_BUF_3]

# define AR_DUMP_EXIT		1

# define AR_FIELD_ERROR		"Memory for ARENA->FIELD has not been allocated"
# define AR_OBJECT_ERROR	"Memory for ARENA has not been allocated"
# define AR_OBJECT_NAME		"ARENA"

# define G					AR_STEALTH_O ? VPS : VPN

typedef enum		e_set_buffer
{
	CW_VALUE_BUF_1,
	CW_VALUE_BUF_2,
	CW_VALUE_BUF_3,
	CW_SYSTEM_BUF,
	CW_SPARE_BUF,
	CW_BUFFER_AMOUNT
}					t_set_buffer;

typedef struct		s_arena
{
	t_flag			ncurses;
	t_flag			stealth;

	t_mark			cycle_to_die;
	t_counter		live_amount;
	t_counter		check_amount;
	t_counter		cycle;

	t_byte			*p_field;
	t_player		*p_winner;
	t_buffer		*pa_buffer_set[CW_BUFFER_AMOUNT];

	t_method		(*cw_constructor)	(struct s_arena **);
	t_method		(*cw_print_field)	(struct s_arena *, int);
	t_method		(*cw_buffer_init)	(struct s_arena *);
	t_mark			(*cw_time_to_check)	(struct s_arena *, int);
	t_method		(*cw_destructor)	(struct s_arena **);
}					t_arena;

void				cw_create_instance_arena(t_arena **pp_arena_obj);
void				cw_arena_functions_linker(t_arena *p_arena_instance);

#endif
