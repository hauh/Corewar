/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/13 15:46:49 by smorty           ###   ########.fr       */
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

static void	parse_line(t_token **list, char *line, int y)
{
	t_token *new;

	if (check_emptiness_and_comment(line))
		return ;
	if (!(new = (t_token *)malloc(sizeof(t_token))))
		error(strerror(errno));
	new->y = y;
	new->next = NULL;
	if ((new->prev = *list))
		(*list)->next = new;
	parse_arguments(new, line);
	*list = new;
}

static void get_name(int fd)
{
	char *line;

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
		++y;
		parse_line(&list, line, y);
		free(line);
	}
	while (list->prev)
		list = list->prev;
	return (list);
}
