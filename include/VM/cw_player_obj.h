/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_obj.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:19:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 17:16:29 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_PLAYER_OBJ_H
# define CW_PLAYER_OBJ_H

# include "cw_obj_container.h"

# define PL_ID_I			p_player_instance->id
# define PL_CODE_SIZE_I		p_player_instance->code_size
# define PL_BINARY_LABEL_I	p_player_instance->binary_label
# define PL_LIVE_AMOUNT_I	p_player_instance->live_amount
# define PL_CODE_I			p_player_instance->p_code
# define PL_NAME_I			p_player_instance->p_name
# define PL_SOURCE_I		p_player_instance->p_source
# define PL_COMMENT_I		p_player_instance->p_comment
# define PL_NEXT_I			p_player_instance->p_next
# define PL_PREV_I			p_player_instance->p_prev

# define PL_ID_O			p_player_obj->id
# define PL_CODE_SIZE_O		p_player_obj->code_size
# define PL_BINARY_LABEL_O	p_player_obj->binary_label
# define PL_LIVE_AMOUNT_O	p_player_obj->live_amount
# define PL_CODE_O			p_player_obj->p_code
# define PL_NAME_O			p_player_obj->p_name
# define PL_SOURCE_O		p_player_obj->p_source
# define PL_COMMENT_O		p_player_obj->p_comment
# define PL_NEXT_O			p_player_obj->p_next
# define PL_PREV_O			p_player_obj->p_prev

# define PL_OBJECT_NAME		"PLAYER"
# define PL_OBJECT_ERROR	"Memory for PLAYER has not been allocated"
# define PL_SOURCE_ERROR	"Memory for PLAYER->SOURCE has not been allocated"
# define PL_SET_ID_ERROR	"While trying to set customd id with -n flag"
# define PL_OPEN_FILE_ERR	"While trying to open file from argument"
# define PL_READ_FILE_ERR	"While trying to read file from argument"
# define PL_BINARY_ERROR	"While reading file binary mark not found"
# define PL_TOO_BIG_SIZE	"While reading file too big champoin has been found"
# define PL_INCONSISTENCY	"While reading file inconsistency sizes"

# define S					__LINE__

typedef struct				s_player
{
	t_attribute		id;
	t_attribute		code_size;
	t_attribute		binary_label;
	t_attribute		live_amount;

	t_byte			*p_code;
	t_byte			*p_name;
	t_byte			*p_source;
	t_byte			*p_comment;

	struct s_player	*p_next;
	struct s_player	*p_prev;

	t_method		(*cw_constructor)	(struct s_player **);
	t_method		(*cw_set_id)		(struct s_player *, int *, int, int);
	t_method		(*cw_read_file)		(struct s_player *, const char *);
	t_method		(*cw_self_build)	(struct s_player *);
	t_method		(*cw_self_validate)	(struct s_player *);
	t_method		(*cw_destructor)	(struct s_player **);
}							t_player;

void						cw_create_instance_player
							(t_player **pp_player_obj);
void						cw_player_functions_linker
							(t_player *p_player_instance);

#endif
