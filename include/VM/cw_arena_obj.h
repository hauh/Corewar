/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_arena_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:07:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:29:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ARENA_OBJ_H
# define CW_ARENA_OBJ_H

# include "cw_obj_container.h"

# define AR_LAST_SURVIVOR	p_arena_instance->p_last_survivor
# define AR_CYCLE_TO_DIE	p_arena_instance->cycle_to_die
# define AR_CYCLE_AMOUNT	p_arena_instance->cycle_amount
# define AR_CHECK_AMOUNT	p_arena_instance->check_amount
# define AR_LIVE_AMOUNT		p_arena_instance->live_amount
# define AR_BUFFERS			p_arena_instance->pa_buffer_set
# define AR_FIELD			p_arena_instance->p_field

# define AR_DUMP_EXIT		1

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
	int				cycle_to_die;

	t_counter		live_amount;
	t_counter		check_amount;
	t_lcounter		cycle_amount;

	t_byte			*p_field;

	t_player		*p_last_survivor;

	t_buffer		*pa_buffer_set[CW_BUFFER_AMOUNT];

	void			(*cw_constructor)	(struct s_arena **);
	int				(*cw_time_to_check)	(struct s_arena *, int);
	void			(*cw_print_field)	(struct s_arena *);
	void			(*cw_buffer_init)	(struct s_arena *);
	void			(*cw_destructor)	(struct s_arena **);
}					t_arena;

void				cw_arena_functions_linker(t_arena *p_arena_instance);

#endif
