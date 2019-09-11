/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:41:49 by smorty            #+#    #+#             */
/*   Updated: 2019/09/11 22:10:10 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void	print_list(t_token *list)
{
	while (list)
	{
		printf("%s x %d y %d type %d\n", list->line, list->x, list->y, list->type);
		list = list->next;
	}
}
