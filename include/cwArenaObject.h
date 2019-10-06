/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:07:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 17:50:05 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ARENA_OBJECT_H
# define CW_ARENA_OBJECT_H

# include "cwTypedefObjects.h"

typedef enum				set_buffer_e
{
	CW_VALUE_BUF_1,
	CW_VALUE_BUF_2,
	CW_VALUE_BUF_3,
	CW_SYSTEM_BUF,
	CW_SPARE_BUF,
	CW_BUFFER_AMOUNT
}							set_buffer_t;

typedef struct				arena_s
{
	int						live_amount;
	int						check_amount;
	int						cycle_to_die;
	unsigned long			cycle_amount;

	unsigned char			*field;

	carriage_t				*lastCarriage;
	player_t				*lastSurvivor;
	buffer_t				*bufferSet[CW_BUFFER_AMOUNT];

	const void				(*cwConstructorArena)	(arena_t *);
	const void				(*cwPrintField)			(arena_t *);
	const void				(*cwBufferInit)			(arena_t *);
	const void				(*cwDestructorArena)	(arena_t *);
}							arena_t;

#endif
