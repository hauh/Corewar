/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/16 22:19:26 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		trim_comment(char *line)
{
	while (*line && *line != COMMENT_CHAR && *line != COMMENT_CHAR_ALT)
		++line;
	*line = 0;
}

static t_opcode	*new_element(t_opcode **list)
{
	t_opcode *new;

	if (!(new = (t_opcode *)malloc(sizeof(t_opcode))))
		error(strerror(errno));
	new->next = NULL;
	if ((new->prev = *list))
		(*list)->next = new;
	return (new);
}

static char		*get_label(char *line)
{
	char	*label;
	size_t	size;

	size = skip_letters(&line) - 1;
	if (!size || *--line != LABEL_CHAR)
		return (NULL);
	if (!(label = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	label[size] = 0;
	while (size--)
		if (!ft_strchr(LABEL_CHARS, (label[size] = *--line)))
			error("Wrong label name");
	return (label);
}

static int		parse_line(t_opcode **list, char *line, int y, int fd)
{
	int	x;

	x = 1 + skip_whitespaces(&line);
	trim_comment(line);
	if (!*line)
		return (1);
	*list = new_element(list);
	(*list)->x = x;
	(*list)->y = y;
	if (((*list)->label = get_label(line)))
		x += skip_letters(&line) + skip_whitespaces(&line);
	while (line && !*line)
		if ((line = read_input(fd)))
		{
			++(*list)->y;
			x = 1 + skip_whitespaces(&line);
			trim_comment(line);
		}
	line ? parse_opcode(*list, line, x) : error("Syntax error");
	return ((*list)->y - y);
}

t_warrior		*parse_file(int fd)
{
	t_warrior	*warrior;
	t_opcode	*list;
	char		*line;
	int			y;

	if (!(warrior = (t_warrior *)malloc(sizeof(t_warrior))))
		error(strerror(errno));
	y = 1 + parse_title(warrior, fd);
	list = NULL;
	while ((line = read_input(fd)))
	{
		y += parse_line(&list, line, y, fd);
		free(line);
	}
	while (list->prev)
		list = list->prev;
	warrior->program = list;
	return (warrior);
}
