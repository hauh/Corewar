/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwStackObject.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:20:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/25 19:34:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_STACK_OBJECT_H
# define CW_STACK_OBJECT_H

#include "cwTypedefObjects.h"

typedef struct	stack_s
{
	carriage_t	*pCurrentCarriage;
	carriage_t	*pNextCarriage;
	carriage_t	*pPrevCarriage;

	void		(*cwConstructor)	(stack_t *);
	void		(*cwEnqueue)		(stack_t *, carriage_t *);
	void		(*cwDequeue)		(stack_t *, carriage_t *);
	void		(*cwCount)			(stack_t *, int *);
	void		(*cwPeek)			(stack_t *, carriage_t *);
	void		(*cwDestructor)		(stack_t *);
}				stack_t;

#endif