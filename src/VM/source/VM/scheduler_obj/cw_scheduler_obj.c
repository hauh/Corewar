/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:54:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/16 17:21:43 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(t_scheduler **pp_scheduler_instance)
{
	(*pp_scheduler_instance)->nearest_cycle = 1;
}

static void		cw_destructor(t_scheduler **pp_scheduler_instance)
{
	t_iterator	iter;
	t_player	*tmp;

	iter = CW_ITERATOR;
	while (++iter < (*pp_scheduler_instance)->players_amount)
	{
		tmp = (*pp_scheduler_instance)->p_players_list->p_next;
		(*pp_scheduler_instance)->p_players_list->
			cw_destructor(&(*pp_scheduler_instance)->p_players_list);
		(*pp_scheduler_instance)->p_players_list = tmp;
	}
	iter = CW_ITERATOR;
	if ((*pp_scheduler_instance)->avl_tree_timeline_on ||
	(*pp_scheduler_instance)->list_timeline_on)
	{
		while (++iter < SC_MAX_CYCLE_SUPPORT)
			(*pp_scheduler_instance)->pa_timeline[iter]->
		cw_destructor(&(*pp_scheduler_instance)->pa_timeline[iter]);
		free((*pp_scheduler_instance)->pa_timeline);
	}
	free(*pp_scheduler_instance);
	*pp_scheduler_instance = NULL;
}

extern void		cw_create_instance_scheduler(t_scheduler **pp_scheduler_obj)
{
	if (!(*pp_scheduler_obj = (t_scheduler *)malloc(sizeof(t_scheduler))))
		cw_error_catcher(SC_OBJ_NAME, SC_OBJ_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_scheduler_obj, 0, sizeof(t_scheduler));
	(*pp_scheduler_obj)->cw_constructor = cw_constructor;
	(*pp_scheduler_obj)->cw_destructor = cw_destructor;
	(*pp_scheduler_obj)->cw_constructor(pp_scheduler_obj);
	cw_scheduler_functions_linker(*pp_scheduler_obj, NULL);
	cw_scheduler_insertion_linker(*pp_scheduler_obj, NULL);
}
