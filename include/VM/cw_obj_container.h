/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_obj_container.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:08:56 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:24:43 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_TYPEDEF_OBJECT_H
# define CW_TYPEDEF_OBJECT_H

typedef struct s_corewar	t_corewar;
typedef struct s_arena		t_arena;
typedef struct s_player		t_player;
typedef struct s_carriage	t_carriage;
typedef struct s_command	t_command;
typedef struct s_buffer		t_buffer;
typedef	struct s_queue		t_queue;
typedef struct s_stack		t_stack;
typedef struct s_vis		t_vis;
typedef int					t_flag;
typedef int					t_mark;
typedef	int					t_counter;
typedef unsigned long		t_lcounter;
typedef int					t_iterator;
typedef unsigned char		t_byte;

# include "cw_arena_obj.h"
# include "cw_buffer_obj.h"
# include "cw_carriage_obj.h"
# include "cw_command_obj.h"
# include "cw_game_obj.h"
# include "cw_player_obj.h"
# include "cw_queue_obj.h"
# include "cw_stack_obj.h"

#endif