/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:41:49 by smorty            #+#    #+#             */
/*   Updated: 2019/09/14 20:37:12 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void	print_list(t_token *list)
{
	const char	*types[18] = {NAME_CMD_STRING, COMMENT_CMD_STRING,
							"live", "ld", "st", "add", "sub", "and",
							"or", "xor", "zjmp", "ldi", "sti",
							"fork", "lld", "lldi", "lfork", "aff"};
	while (list)
	{

		printf("type: %s\n", types[list->type]);
		printf("size x y: %d %d %d\n",list->size, list->x, list->y);
		printf("label: %s\n", list->label);
		int i = 0;
		while (i < 3)
		{
			if (list->arg[i])
				printf("\targ %d type %d val %d x %d\n", i, list->arg[i]->type, list->arg[i]->val, list->arg[i]->x);
			++i;
		}
		printf("-------------\n");
		list = list->next;
	}
}
