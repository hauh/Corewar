/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_sizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:44:05 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 23:11:10 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	find_label(t_opcode *head, char *label_name)
{
	t_opcode	*prog;
	int			bytes;

	prog = head->prev;
	bytes = 0;
	while (prog)
	{
		bytes -= prog->size;
		if (prog->label && ft_strequ(prog->label, label_name))
			return (bytes);
		prog = prog->prev;
	}
	prog = head;
	bytes = 0;
	while (prog)
	{
		if (prog->label && ft_strequ(prog->label, label_name))
			return (bytes);
		bytes += prog->size;
		prog = prog->next;
	}
	ft_printf("Label %s ");
	error("not found", 0);
	return (0);
}

static void	set_links_values(t_opcode *prog)
{
	int i;

	while (prog)
	{
		i = 0;
		while (i < 3)
		{
			if (prog->param[i] && prog->param[i]->link)
			{
				prog->param[i]->value = find_label(prog, prog->param[i]->link);
				free(prog->param[i]->link);
			}
			++i;
		}
		prog = prog->next;
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
				size += T_REG;
			else if (params[i]->type == crw_indirect
				|| type == crw_zjmp || type == crw_ldi || type == crw_sti
				|| type == crw_fork || type == crw_lld || type == crw_lfork)
				size += T_DIR;
			else
				size += T_IND;
		}
		++i;
	}
	return (size);
}

static int	calculate_sizes(t_opcode *prog)
{
	size_t total;

	total = 0;
	while (prog)
	{
		prog->size = 1 + (prog->type != crw_live && prog->type != crw_zjmp
						&& prog->type != crw_fork && prog->type != crw_lfork);
		prog->size += params_size(prog->param, prog->type);
		total += prog->size;
		prog = prog->next;
	}
	return (total);
}

void		analyze_sizes(t_warrior *warrior)
{
	warrior->code_size = calculate_sizes(warrior->program);
	set_links_values(warrior->program);
}
