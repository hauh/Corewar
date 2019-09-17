/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:24:54 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 23:44:44 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_label(char *line, size_t size)
{
	char *label;

	if (!(label = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	label[size] = 0;
	while (size--)
		if (!ft_strchr(LABEL_CHARS, (label[size] = line[size])))
			error("Invalid label characters");
	return (label);
}

static size_t	label_size(char *line)
{
	char *s;

	s = line;
	while (*s && *s != LABEL_CHAR && *s != DIRECT_CHAR && !IS_BLANK(*s))
		++s;
	if (*s == LABEL_CHAR)
		return (s - line);
	return (0);
}

int				parse_label(t_opcode *list, char *line)
{
	size_t	size;

	if ((size = label_size(line)))
	{
		if (list->label)
			error("Multiple labels");
		list->label = get_label(line, size);
		return (1);
	}
	return (0);
}
