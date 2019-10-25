/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/25 13:48:23 by vrichese         ###   ########.fr       */
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
	int					savePoint;
	int					waitingTime;
	int					additOdometer;
	int					lastSpeakCycle;
	int					additSavePoint;
	int					currentLocation;
	char				currentRegister;
	int					errorOcurred;
	int					firstArg;
	int					secondArg;
	int					thirdArg;
	int					offset;

	unsigned char		*pRegisters;

	struct carriage_s	*pNext;
	struct carriage_s	*pPrev;

	command_t			**ppCommandContainer;
	command_t			*pCurrentCommand;
	player_t			*pOwnerCarriage;

	void				(*cwConstructor)			(carriage_t **);
	void				(*cwSavePos)				(carriage_t *, flag_t);
	void				(*cwExecCommand)			(carriage_t *, corewar_t *);
	void				(*cwSetCommandTime)			(carriage_t *, arena_t *);
	void				(*cwReduceTime)				(carriage_t *);
	void				(*cwParseTypes)				(carriage_t *, arena_t *);
	void				(*cwMoveTo)					(carriage_t *, int);
	void 				(*cwCarriageReturn)			(carriage_t *, int);
	void				(*cwReturnProtocolActivate)	(carriage_t *, arena_t *);
	void				(*cwSetOwner)				(carriage_t *, player_t *, int);
	void				(*cwConversionValueToBytes)	(carriage_t *, buffer_t *, int);
	void				(*cwConversionBytesToValue)	(carriage_t *, buffer_t *, int);
	void				(*cwWriteOperation)			(carriage_t *, arena_t *, buffer_t *, int);
	void				(*cwReadOperation)			(carriage_t *, arena_t *, buffer_t *, int);
	void				(*cwCheckCarry)				(carriage_t *);
	void 				(*cwWriteOwnerIdToReg)		(carriage_t *);
	void				(*cwCopyReg)				(carriage_t *, carriage_t *);
	void				(*cwRegCheck)				(carriage_t *, arena_t *, int);
	void				(*cwDestructor)				(carriage_t **);
}						carriage_t;

#endif
