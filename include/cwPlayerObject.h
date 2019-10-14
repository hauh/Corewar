/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayerObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:19:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/14 17:40:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_PLAYER_OBJECT_H
# define CW_PLAYER_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct		player_s
{
	int				id;
	int				codeSize;
	int				carriageId;
	int				binaryLabel;

	unsigned char	*pCode;
	unsigned char	*pName;
	unsigned char	*pSource;
	unsigned char	*pComment;

	struct player_s	*pNext;
	struct player_s	*pPrev;

	const void		(*cwConstructor)	(player_t **);
	const void		(*cwSetId)			(player_t *, int);
	const void		(*cwReadFile)		(player_t *, const char *);
	const void		(*cwSelfBuild)		(player_t *);
	const void		(*cwSelfValidate)	(player_t *);
	const void		(*cwDestructor)		(player_t **);
}					player_t;

#endif
