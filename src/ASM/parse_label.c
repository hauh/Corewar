/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:24:54 by smorty            #+#    #+#             */
/*   Updated: 2019/11/16 14:44:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*get_label(char *line, size_t size)
{
	char *label;

	if (!(label = (char *)malloc(sizeof(char) * (size + 1))))
		error(strerror(errno), 0);
	label[size] = 0;
	while (size--)
		if (!ft_strchr(LABEL_CHARS, (label[size] = line[size])))
			error("Syntax error: invalid label character", 1);
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

static void		add_label(t_label **list, char *label_name)
{
	t_label *new;

	if (!(new = (t_label *)malloc(sizeof(t_label))))
		error(strerror(errno), 0);
	new->label_name = label_name;
	new->next = *list;
	*list = new;
}

void			parse_label(t_opcode *opcode, char **line)
{
	size_t		size;

	if ((size = label_size(*line)))
	{
		add_label(&opcode->labels, get_label(*line, size));
		g_cur_col += size;
		*line += size + 1;
	}
}
