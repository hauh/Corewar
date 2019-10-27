/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_arena_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 20:05:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_time_to_check(arena_t *p_arena_instance, int last_check_cycle)
{
	if (p_arena_instance->cycle_to_die <= 0 || p_arena_instance->cycle_amount - last_check_cycle == p_arena_instance->cycle_to_die)
		return (CW_TRUE);
	else
		return (CW_FALSE);
}

static void		cw_print_field(arena_t *p_arena_instance)
{
	int			border;
	int			iter;

	border = sqrt(MEM_SIZE);
	iter = CW_BEGIN_FROM_ZERO;
	ft_printf("0x0000 : ");
	while (iter < MEM_SIZE)
	{
		ft_printf("%.2x ", p_arena_instance->p_field[iter]);
		if ((iter + 1) % border == 0 && iter != MEM_SIZE - 1)
			ft_printf("\n%#06x : ", iter + 1);
		++iter;
	}
	ft_printf("\n");
}

static void		cw_buffer_init(arena_t *p_arena_instance)
{
	buffer_t	*buffer_obj;
	int			buf_iter;

	buf_iter = CW_BEGIN_FROM_ZERO;
	while (buf_iter < CW_BUFFER_AMOUNT)
	{
		cw_create_instance_buffer(&buffer_obj);
		p_arena_instance->pa_buffer_set[buf_iter] = buffer_obj;
		++buf_iter;
	}
}

static void		cw_set_last_survivor(arena_t *p_arena_instance,
										player_t *p_last_survivor)
{
	p_arena_instance->p_last_survivor = p_last_survivor;
}

static void		cw_constructor(arena_t **pp_arena_instance)
{
	if (!((*pp_arena_instance)->p_field =
	(unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	ft_memset((*pp_arena_instance)->p_field, 0, MEM_SIZE);
	(*pp_arena_instance)->cycle_amount = 0;
	(*pp_arena_instance)->check_amount = 0;
	(*pp_arena_instance)->live_amount = 0;
	(*pp_arena_instance)->cycle_to_die = CYCLE_TO_DIE;
	(*pp_arena_instance)->p_last_survivor = NULL;
}

static void		cw_destructor(arena_t **pp_arena_instance)
{
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < CW_BUFFER_AMOUNT)
		(*pp_arena_instance)->pa_buffer_set[iter]->
			cw_destructor(&(*pp_arena_instance)->pa_buffer_set[iter]);
	free((*pp_arena_instance)->p_field);
	free(*pp_arena_instance);
	*pp_arena_instance = NULL;
}

extern void		cw_create_instance_arena(arena_t **pp_arena_obj)
{
	if (!(*pp_arena_obj = (arena_t *)malloc(sizeof(arena_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	(*pp_arena_obj)->cw_constructor = cw_constructor;
	(*pp_arena_obj)->cw_destructor = cw_destructor;
	(*pp_arena_obj)->cw_set_last_survivor = cw_set_last_survivor;
	(*pp_arena_obj)->cw_time_to_check = cw_time_to_check;
	(*pp_arena_obj)->cw_buffer_init = cw_buffer_init;
	(*pp_arena_obj)->cw_print_field = cw_print_field;
	(*pp_arena_obj)->cw_constructor(pp_arena_obj);
}
