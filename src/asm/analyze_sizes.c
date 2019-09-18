/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_sizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:44:05 by smorty            #+#    #+#             */
/*   Updated: 2019/09/18 23:13:37 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static void	set_links_values(t_opcode *list)
{
	int i;

	while (list)
	{
		i = 0;
		while (i < 3)
		{
			if (list->param[i] && list->param[i]->link)
				list->param[i]->value = find_label(list, list->param[i]->link);
			++i;
		}
		list = list->next;
	}
}

static int	params_size(t_opcode_param **params, t_opcode_type type)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (i < 3)
	{
		if (params[i])
		{
			if (params[i]->type == crw_registry)
				size += 1;
			else if (params[i]->type == crw_indirect
				|| type == crw_zjmp || type == crw_ldi || type == crw_sti
				|| type == crw_fork || type == crw_lld || type == crw_lfork)
				size += 2;
			else
				size += 4;
		}
		++i;
	}
	return (size);
}

static int	calculate_sizes(t_opcode *list)
{
	size_t total;

	total = 0;
	while (list)
	{
		list->size = 1 + (list->type != crw_live && list->type != crw_zjmp
						&& list->type != crw_fork && list->type != crw_lfork);
		list->size += params_size(list->param, list->type);
		total += list->size;
		list = list->next;
	}
	return (total);
}

void		analyze_sizes(t_warrior *warrior)
{
	warrior->code_size = calculate_sizes(warrior->program);
	set_links_values(warrior->program);
}
