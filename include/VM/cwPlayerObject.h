/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwPlayerObject.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:19:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/28 14:21:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_PLAYER_OBJECT_H
# define CW_PLAYER_OBJECT_H

# include "cwTypedefObjects.h"

typedef struct		player_s
{
	int				id;
	int				code_size;
	int				carriage_id;
	int				binary_label;
	int				live_amount;

	unsigned char	*p_code;
	unsigned char	*p_name;
	unsigned char	*p_source;
	unsigned char	*p_comment;

	struct player_s	*p_next;
	struct player_s	*p_prev;

	void			(*cw_constructor)	(player_t **);
	void			(*cw_set_id)		(player_t *, int *, int, int);
	void			(*cw_read_file)		(player_t *, const char *);
	void			(*cw_self_build)	(player_t *);
	void			(*cw_self_validate)	(player_t *);
	void			(*cw_destructor)	(player_t **);
}					player_t;

#endif
