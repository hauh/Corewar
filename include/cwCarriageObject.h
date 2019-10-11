/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/11 20:00:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_CARRIAGE_OBJECT_H
# define CW_CARRIAGE_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct			carriage_s
{
	int					id;
	int					jump;
	int					carry;
	int					offset;
	int					savePoint;
	int					waitingTime;
	int					lastSpeakCycle;
	int					currentLocation;
	int					errorOcurred;
	char				currentRegister;

	unsigned char		*pRegisters;

	struct carriage_s	*pNext;
	struct carriage_s	*pPrev;

	command_t			**ppCommandContainer;
	command_t			*pCurrentCommand;
	player_t			*pOwnerCarriage;

	const void			(*cwConstructorCarriage)(carriage_t **);
	const void			(*cwSavePos)			(carriage_t *);
	const void			(*cwExecCommand)		(carriage_t *);
	const void			(*cwReadOperation)		(carriage_t *);
	const void			(*cwSetCommandTime)		(carriage_t *, arena_t *);
	const void			(*cwWriteOperation)		(carriage_t *);
	const void			(*cwReduceWaitingTime)	(carriage_t *);
	const void			(*cwValidateTypes)		(carriage_t *);
	const void			(*cwComputeJump)		(carriage_t *);
	const void			(*cwParseTypes)			(carriage_t *);
	const void			(*cwMoveTo)				(carriage_t *, int);
	const void			(*cwReadFromRegToBuf)	(carriage_t *, );
	const void			(*cwWriteFromBufToReg)	(carriage_t *);
	const void			(*cwDestructorCarriage) (carriage_t **);
}						carriage_t;

#endif
