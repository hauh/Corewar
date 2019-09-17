/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 23:47:49 by smorty           ###   ########.fr       */
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
	new->label = NULL;
	new->type = crw_undef_code;
	new->param_code = 0;
	if ((new->prev = *list))
		(*list)->next = new;
	return (new);
}

static void		parse_line(t_opcode **list, char *line, int y)
{
	int	x;

	x = 1 + skip_whitespaces(&line);
	trim_comment(line);
	if (!*line)
		return ;
	if (!(*list) || (*list)->type != crw_undef_code)
		*list = new_element(list);
	(*list)->x = x;
	(*list)->y = y;
	if (parse_label(*list, line))
		x += skip_letters(&line) + skip_whitespaces(&line);
	if (*line)
		parse_opcode(*list, line, x);
}

t_warrior		*parse_file(int fd)
{
	t_warrior	*warrior;
	t_opcode	*list;
	char		*line;
	int			y;

	if (!(warrior = (t_warrior *)malloc(sizeof(t_warrior))))
		error(strerror(errno));
	y = parse_title(warrior, fd);
	list = NULL;
	while ((line = read_input(fd)))
	{
		parse_line(&list, line, ++y);
		free(line);
	}
	while (list->prev)
		list = list->prev;
	warrior->program = list;
	return (warrior);
}
