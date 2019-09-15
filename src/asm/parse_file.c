/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/15 21:00:02 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_empty_or_comment(char *line)
{
	int is_empty;

	is_empty = 1;
	while (*line)
	{
		if (*line == COMMENT_CHAR || *line == COMMENT_CHAR_ALT)
		{
			*line = 0;
			return (is_empty);
		}
		else if (*line != ' ' && *line != '\t' && *line != SEPARATOR_CHAR)
			is_empty = 0;
		++line;
	}
	return (is_empty);
}

static int	parse_line(t_token **list, char *line, int y, int fd)
{
	t_token	*new;
	char	*next_line;

	if (is_empty_or_comment(line))
		return (1);
	if (!(new = (t_token *)malloc(sizeof(t_token))))
		error(strerror(errno));
	new->y = y;
	new->label = NULL;
	new->next = NULL;
	if ((new->prev = *list))
		(*list)->next = new;
	*list = new;
	if (parse_arguments(new, line))
	{
		while ((next_line = read_input(fd)) && is_empty_or_comment(line))
			free(next_line);
		++new->y;
		parse_arguments(new, next_line);
		free(next_line);
		return (2);
	}
	return (1);
}

t_warrior	*parse_file(int fd)
{
	t_warrior	*warrior;
	t_token		*list;
	char		*line;
	int			y;

	if (!(warrior = (t_warrior *)malloc(sizeof(t_warrior))))
		error(strerror(errno));
	y = 1;
	parse_name_and_comment(warrior, &y, fd);
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
