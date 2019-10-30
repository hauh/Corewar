/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_obj.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:19:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 15:57:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_PLAYER_OBJECT_H
# define CW_PLAYER_OBJECT_H

# include "cw_obj_container.h"

typedef struct		s_player
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

	struct s_player	*p_next;
	struct s_player	*p_prev;

	void			(*cw_constructor)	(t_player **);
	void			(*cw_set_id)		(t_player *, int *, int, int);
	void			(*cw_read_file)		(t_player *, const char *);
	void			(*cw_self_build)	(t_player *);
	void			(*cw_self_validate)	(t_player *);
	void			(*cw_destructor)	(t_player **);
}					t_player;

void	cw_set_id(t_player *p_player_instance, int *p_busy_byte, int id, int custom_id);
void	cw_read_file(t_player *p_player_instance, const char *p_file);
void	cw_self_validate(t_player *p_player_instance);
void	cw_self_build(t_player *p_player_instance);

#endif
