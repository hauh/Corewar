/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:07:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/29 20:04:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ARENA_OBJECT_H
# define CW_ARENA_OBJECT_H

# include "cwTypedefObjects.h"

# define AR_CYCLE_TO_DIE	p_arena_instance->cycle_to_die
# define AR_CYCLE_AMOUNT	p_arena_instance->cycle_amount
# define AR_CHECK_AMOUNT	p_arena_instance->check_amount
# define AR_LIVE_AMOUNT		p_arena_instance->live_amount
# define AR_FIELD			p_arena_instance->p_field

typedef enum		set_buffer_e
{
	CW_VALUE_BUF_1,
	CW_VALUE_BUF_2,
	CW_VALUE_BUF_3,
	CW_SYSTEM_BUF,
	CW_SPARE_BUF,
	CW_BUFFER_AMOUNT
}					set_buffer_t;

typedef struct		arena_s
{
	int				live_amount;
	int				check_amount;
	int				cycle_to_die;
	unsigned long	cycle_amount;

	unsigned char	*p_field;

	player_t		*p_last_survivor;
	buffer_t		*pa_buffer_set[CW_BUFFER_AMOUNT];

	void			(*cw_constructor)		(arena_t **);
	int				(*cw_time_to_check)		(arena_t *, int);
	void			(*cw_buffer_init)		(arena_t *);
	void			(*cw_print_field)		(arena_t *);
	void			(*cw_destructor)		(arena_t **);
}					arena_t;

#endif
