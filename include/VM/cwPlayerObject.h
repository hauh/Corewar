/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayerObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:19:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/21 15:46:44 by vrichese         ###   ########.fr       */
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

	void			(*cwConstructor)	(player_t **);
	void			(*cwSetId)			(player_t *, int *, int, int);
	void			(*cwReadFile)		(player_t *, const char *);
	void			(*cwSelfBuild)		(player_t *);
	void			(*cwSelfValidate)	(player_t *);
	void			(*cwDestructor)		(player_t **);
}					player_t;

#endif
