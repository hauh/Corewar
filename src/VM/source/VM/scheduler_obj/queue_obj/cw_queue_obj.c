/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_queue_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:13:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 20:10:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		kill_all_process(t_queue *p_queue_instance,
									t_process *p_process_obj)
{
	t_process	*p_left;
	t_process	*p_right;

	if (p_process_obj)
	{
		p_left = p_process_obj->p_left;
		p_right = p_process_obj->p_right;
		kill_all_process(p_queue_instance, p_right);
		p_process_obj->cw_destructor(&p_process_obj);
		kill_all_process(p_queue_instance, p_left);
	}
}

static void		cw_constructor(t_queue **pp_queue_instance)
{
	(*pp_queue_instance)->p_root = NULL;
}

static void		cw_destructor(t_queue **pp_queue_instance)
{
	if ((*pp_queue_instance)->p_root)
		kill_all_process(*pp_queue_instance, (*pp_queue_instance)->p_root);
	free(*pp_queue_instance);
	*pp_queue_instance = NULL;
}

extern void		cw_create_instance_queue(t_queue **pp_queue_obj)
{
	if (!(*pp_queue_obj = (t_queue *)malloc(sizeof(t_queue))))
		cw_error_catcher(QU_OBJ_NAME, QU_OBJ_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_queue_obj, 0, sizeof(t_queue));
	(*pp_queue_obj)->cw_constructor = cw_constructor;
	(*pp_queue_obj)->cw_destructor = cw_destructor;
	(*pp_queue_obj)->cw_constructor(pp_queue_obj);
	cw_queue_functions_linker(*pp_queue_obj);
	cw_queue_avl_tree_functions_linker(*pp_queue_obj);
}
