/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_arena_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:29:52 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_constructor(t_arena **pp_arena_instance)
{
	if (!((*pp_arena_instance)->p_field =
	(unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset((*pp_arena_instance)->p_field, 0, MEM_SIZE);
	(*pp_arena_instance)->cycle_to_die = CYCLE_TO_DIE;
}

static void		cw_destructor(t_arena **pp_arena_instance)
{
	t_iterator	iter;

	iter = CW_ITERATOR;
	while (++iter < CW_BUFFER_AMOUNT)
		(*pp_arena_instance)->pa_buffer_set[iter]->
			cw_destructor(&(*pp_arena_instance)->pa_buffer_set[iter]);
	free((*pp_arena_instance)->p_field);
	free(*pp_arena_instance);
	*pp_arena_instance = NULL;
}

extern void		cw_create_instance_arena(t_arena **pp_arena_obj)
{
	if (!(*pp_arena_obj = (t_arena *)malloc(sizeof(t_arena))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset(*pp_arena_obj, 0, sizeof(t_arena));
	(*pp_arena_obj)->cw_constructor = cw_constructor;
	(*pp_arena_obj)->cw_destructor = cw_destructor;
	(*pp_arena_obj)->cw_constructor(pp_arena_obj);
	cw_arena_functions_linker(*pp_arena_obj);
}
