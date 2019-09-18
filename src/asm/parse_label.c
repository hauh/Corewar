/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:24:54 by smorty            #+#    #+#             */
/*   Updated: 2019/09/19 00:36:27 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_label(char *line, size_t size)
{
	char *label;

	if (!(label = (char *)malloc(sizeof(char) * (size + 1))))
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

void			parse_label(t_opcode *opcode, char **line)
{
	size_t	size;

	if ((size = label_size(*line)))
	{
		if (opcode->label)
			error("Multiple labels");
		opcode->label = get_label(*line, size);
		opcode->x += size;
		*line += size + 1;
	}
}
