/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:41:49 by smorty            #+#    #+#             */
/*   Updated: 2019/09/18 17:38:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void	print_list(t_warrior *warrior)
{
	const char	*types[17] = {NULL, "live", "ld", "st", "add", "sub",
							"and", "or", "xor", "zjmp", "ldi", "sti",
							"fork", "lld", "lldi", "lfork", "aff"};
	const char	*param_types[4] = {"<undef>", "r", "%", "indir"};
	t_opcode *list;

	printf("name: %s\n", warrior->name);
	printf("comment: %s\n", warrior->comment);
	printf("===========\n");
	list = warrior->program;
	while (list)
	{

		printf("type: %s\n", types[list->type]);
		printf("size %zu, x %d, y %d\n", list->size, list->x, list->y);
		printf("label: %s\n", list->label);
		printf("code: %x\n", list->param_code);
		int i = 0;
		printf("\t");
		while (i < 3)
		{
			if (list->param[i])
				printf("%s%d (x %d), ", param_types[list->param[i]->type], list->param[i]->value, list->param[i]->x);
			++i;
		}
		printf("\n-------------\n");
		list = list->next;
	}
}
