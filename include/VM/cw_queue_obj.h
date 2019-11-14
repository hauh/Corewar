/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:41:47 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 20:09:49 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_QUEUE_OBJ_H
# define CW_QUEUE_OBJ_H

# include "cw_obj_container.h"

# define QU_GAME_OBJ_I		p_queue_instance->p_game_obj
# define QU_ROOT_I			p_queue_instance->p_root
# define QU_HEAD_I			p_queue_instance->p_head

# define QU_GAME_OBJ_O		p_queue_obj->p_game_obj
# define QU_ROOT_O			p_queue_obj->p_root
# define QU_HEAD_O			p_queue_obj->p_head

# define QU_SET_MODE		1
# define QU_GET_MODE		-1
# define QU_SET_MO			1

# define QU_OBJ_NAME		"QUEUE"
# define QU_OBJ_ERROR		"Memory for QUEUE has not been allocated"

# define QU_LEFT			-1
# define QU_RIGHT			1

typedef struct	s_queue
{
	t_corewar	*p_game_obj;

	t_process	*p_root;
	t_process	*p_head;

	t_method	(*cw_constructor)		(struct s_queue **);
	t_imethod	(*cw_get_balance_factor)(struct s_queue *, t_process *);
	t_imethod	(*cw_height)			(struct s_queue *, t_process *, int);
	t_method	(*cw_exec_processes)	(struct s_queue *, t_process *);
	t_method	(*cw_print_content)		(struct s_queue *, t_process *, int);
	t_process	*(*cw_enqueue)	(struct s_queue *, t_process *, t_process *);
	t_process	*(*cw_rotate)			(struct s_queue *, t_process *, int);
	t_process	*(*cw_balance)			(struct s_queue *, t_process *);
	t_method	(*cw_destructor)		(struct s_queue **);
}				t_queue;

void			cw_create_instance_queue(t_queue **pp_queue_obj);
void			cw_queue_functions_linker(t_queue *p_queue_instance);
void			cw_queue_avl_tree_functions_linker(t_queue *p_queue_instance);

#endif
