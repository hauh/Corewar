/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:44:05 by smorty            #+#    #+#             */
/*   Updated: 2019/09/18 21:41:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	evaluate_sizes(t_opcode *list)
{
	int total;
	int size;
	int i;

	total = 0;
	while (list)
	{
		size = 1 + (list->type != crw_live && list->type != crw_zjmp
				&& list->type != crw_fork && list->type != crw_lfork);
		i = -1;
		while (++i < 3)
			if (list->param[i])
			{
				if (list->param[i]->type == crw_registry)
					size += T_REG;
				else if (list->param[i]->type == crw_indirect
						|| list->type == crw_zjmp || list->type == crw_ldi
						|| list->type == crw_sti || list->type == crw_fork
						|| list->type == crw_lld || list->type == crw_lfork)
					size += T_DIR;
				else
					size += T_DIR * 2;
			}
		list->size = size;
		total += size;
		list = list->next;
	}
	return (total);
}

static int	find_label(t_opcode *head, char *label_name)
{
	t_opcode	*list;
	int			bytes;

	list = head->prev;
	bytes = 0;
	while (list)
	{
		bytes -= list->size;
		if (list->label && ft_strequ(list->label, label_name))
			return (bytes);
		list = list->prev;
	}
	list = head;
	bytes = 0;
	while (list)
	{
		if (list->label && ft_strequ(list->label, label_name))
			return (bytes);
		bytes += list->size;
		list = list->next;
	}
	error("Indirect label not found");
	return (0);
}

static void	set_link_lenghts(t_opcode *list)
{
	int i;

	while (list)
	{
		i = -1;
		while (++i < 3)
			if (list->param[i] && list->param[i]->link)
				list->param[i]->value = find_label(list, list->param[i]->link);
		list = list->next;
	}
}

void		analyze(t_warrior *warrior)
{
	warrior->code_size = evaluate_sizes(warrior->program);
	set_link_lenghts(warrior->program);
}
