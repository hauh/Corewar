/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArenaObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:07:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/21 20:04:22 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ARENA_OBJECT_H
# define CW_ARENA_OBJECT_H

# include "cwTypedefObjects.h"

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
	int				liveAmount;
	int				checkAmount;
	int				cycleToDie;
	unsigned long	cycleAmount;
	int				*test;

	unsigned char	*pField;

	carriage_t		*pLastCarriage;
	player_t		*pLastSurvivor;
	buffer_t		*paBufferSet[CW_BUFFER_AMOUNT];

	void			(*cwConstructor)		(arena_t **);
	void			(*cwSetLastSurvivor)	(arena_t *, player_t *);
	void			(*cwSetLastCarriage)	(arena_t *, carriage_t *);
	int				(*cwTimeToCheck)		(arena_t *);
	void			(*cwBufferInit)			(arena_t *);
	void			(*cwPrintField)			(arena_t *);
	void			(*cwDestructor)			(arena_t **);
}					arena_t;

#endif
