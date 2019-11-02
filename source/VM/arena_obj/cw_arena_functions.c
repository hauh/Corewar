/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_arena_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:22:52 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:28:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cw_time_to_check(t_arena *p_arena_instance, int last_check)
{
	if (AR_CYCLE_TO_DIE <= 0 || AR_CYCLE_AMOUNT - last_check == AR_CYCLE_TO_DIE)
		return (CW_TRUE);
	else
		return (CW_FALSE);
}

static void		cw_print_field(t_arena *p_arena_instance)
{
	int			border;
	int			iter;

	iter = CW_ITERATOR;
	border = sqrt(MEM_SIZE);
	ft_printf("0x0000 : ");
	while (++iter < MEM_SIZE)
	{
		ft_printf("%.2x ", AR_FIELD[iter]);
		if ((iter + 1) % border == 0 && iter != MEM_SIZE - 1)
			ft_printf("\n%#06x : ", iter + 1);
	}
	ft_printf("\n");
	exit(AR_DUMP_EXIT);
}

static void		cw_buffer_init(t_arena *p_arena_instance)
{
	t_buffer	*buffer_obj;
	int			buf_iter;

	buf_iter = CW_ITERATOR;
	while (++buf_iter < CW_BUFFER_AMOUNT)
	{
		cw_create_instance_buffer(&buffer_obj);
		AR_BUFFERS[buf_iter] = buffer_obj;
	}
}

extern void		cw_arena_functions_linker(t_arena *p_arena_instance)
{
	p_arena_instance->cw_time_to_check = cw_time_to_check;
	p_arena_instance->cw_print_field = cw_print_field;
	p_arena_instance->cw_buffer_init = cw_buffer_init;
}
