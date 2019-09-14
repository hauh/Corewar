/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/14 19:38:06 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_emptiness_and_comment(char *line)
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

	if (check_emptiness_and_comment(line))
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
		next_line = read_input(fd);
		++new->y;
		parse_arguments(new, next_line);
		free(next_line);
		return (2);
	}
	return (1);
}

static void	get_name(int fd) // stub
{
	char *line;

	free((line = read_input(fd)));
	free((line = read_input(fd)));
	free((line = read_input(fd)));
}

t_token		*parse_file(int fd)
{
	t_token *list;
	char	*line;
	int		y;

	get_name(fd);
	y = 2;
	list = NULL;
	while ((line = read_input(fd)))
	{
		y += parse_line(&list, line, y, fd);
		free(line);
	}
	while (list->prev)
		list = list->prev;
	return (list);
}
