/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:22:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/20 18:56:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_COMMAND_OBJECT_H
# define CW_COMMAND_OBJECT_H

#include "cwTypedefObjects.h"

typedef struct		command_s
{
	int				id;
	int				args;
	int				dirSize;
	int				changeCarry;
	int				waitingTime;
	int				typeByte;

	void			(*cwConstructorCommand)	(command_t **);
	void			(*cwRecognizeCommand)	(command_t *, int);
	void			(*cwPutParam)			(command_t *, int, int, int, int, int, int, int, int, void (*f)(corewar_t *));
	void			(*cwCallback)			(corewar_t *);
	void			(*cwDestructorCommand)	(command_t **);
}					command_t;

#endif