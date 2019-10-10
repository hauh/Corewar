/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:22:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:01:08 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMAND_OBJECT_H
# define CW_COMMAND_OBJECT_H

#include "cwTypedefObjects.h"

typedef struct		command_s
{
	unsigned int	id;
	unsigned int	firstArg;
	unsigned int	secondArg;
	unsigned int	thirdArg;
	unsigned int	dirSize;
	unsigned int	changeCarry;
	unsigned int	waitingTime;
	unsigned int	typeByte;

	const void		(*cwConstructorCommand)	(command_t **);
	const void		(*cwRecognizeCommand)	(command_t *, int);
	const void		(*cwPutParam)			(command_t *, int, int, int , int , int , int , int , int , const void *);
	const void		(*cwCallback)			(corewar_t *);
	const void		(*cwDestructorCommand)	(command_t **);
}					command_t;

#endif