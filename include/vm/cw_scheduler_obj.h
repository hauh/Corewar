/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:27:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 19:37:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_SCHEDULER_OBJ_H
# define CW_SCHEDULER_OBJ_H

# include "cw_obj_container.h"

# define SC_PLAYERS_AMOUNT_I	p_scheduler_instance->players_amount
# define SC_PROCESSES_AMOUNT_I	p_scheduler_instance->processes_amount
# define SC_PLAYERS_LIST_I		p_scheduler_instance->p_players_list
# define SC_PROCESSES_LIST_I	p_scheduler_instance->p_processes_list
# define SC_AVL_I				p_scheduler_instance->avl_tree_timeline_on
# define SC_LIST_I				p_scheduler_instance->list_timeline_on
# define SC_TREE_TIME_I(X)		p_scheduler_instance->pa_avl_tree_timeline[X]
# define SC_LIST_TIME_I(X)		p_scheduler_instance->pa_list_timeline[X]

# define SC_PLAYERS_AMOUNT_O	p_scheduler_obj->players_amount
# define SC_PROCESSES_AMOUNT_O	p_scheduler_obj->processes_amount
# define SC_PLAYERS_LIST_O		p_scheduler_obj->p_players_list
# define SC_PROCESSES_LIST_O	p_scheduler_obj->p_processes_list
# define SC_AVL_O				p_scheduler_obj->avl_tree_timeline_on
# define SC_LIST_O				p_scheduler_obj->list_timeline_on

# define SC_END_GAME			-777
# define SC_MAX_CYCLE_SUPPORT	50000

# define SC_OBJ_NAME			"SCHEDULER"
# define SC_OBJ_ERROR			"Memory for SCHEDULER has not been allocated"
# define SC_TREE_ERROR			"Memory for AVL_TREE has not been allocated"
# define SC_TRACE				ft_printf("Proc %d has been killed\n", iter->id)

typedef struct		s_scheduler
{
	t_mark			nearest_cycle;

	t_flag			avl_tree_timeline_on;
	t_flag			list_timeline_on;

	t_counter		players_amount;
	t_counter		processes_amount;

	t_mark			*p_cycle_to_die;
	t_player		*p_players_list;
	t_process		*p_processes_list;

	t_queue			**pa_timeline;

	t_method		(*cw_constructor)	(struct s_scheduler **);
	t_method		(*cw_insert_process)
					(struct s_scheduler *, t_process *, int);
	t_method		(*cw_delete_process)
					(struct s_scheduler *, t_process **, int);
	t_method		(*cw_insert_player)	(struct s_scheduler *, t_player *);
	t_method		(*cw_timeline_init)	(struct s_scheduler *, t_corewar *);
	t_method		(*cw_execution_processes)
					(struct s_scheduler *, t_corewar *, int);
	t_method		(*cw_deadline)		(struct s_scheduler *, t_corewar *);
	t_method		(*cw_destructor)	(struct s_scheduler **);
}					t_scheduler;

void				cw_create_instance_scheduler
					(t_scheduler **pp_scheduler_obj);
void				cw_scheduler_insertion_linker
					(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref);
void				cw_scheduler_functions_linker
					(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref);

#endif
