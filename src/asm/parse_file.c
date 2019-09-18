/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/19 00:38:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				skip_whitespaces(char **line)
{
	int count;

	count = 0;
	while (**line && IS_BLANK(**line))
	{
		++(*line);
		++count;
	}
	return (count);
}

static void		trim_comment(char *line)
{
	while (*line && *line != COMMENT_CHAR && *line != COMMENT_CHAR_ALT)
		++line;
	*line = 0;
}

static t_opcode	*new_element(t_opcode **program)
{
	t_opcode *new;

	if (!(new = (t_opcode *)malloc(sizeof(t_opcode))))
		error(strerror(errno));
	new->next = NULL;
	new->label = NULL;
	new->type = crw_undef_code;
	new->param_code = 0;
	if ((new->prev = *program))
		(*program)->next = new;
	return (new);
}

static void		parse_line(t_opcode **program, char *line, int y)
{
	int	x;

	x = 1 + skip_whitespaces(&line);
	trim_comment(line);
	if (!*line)
		return ;
	if (!(*program) || (*program)->type != crw_undef_code)
		*program = new_element(program);
	(*program)->x = x;
	(*program)->y = y;
	parse_label(*program, &line);
	parse_opcode(*program, line, x);
}

t_warrior		*parse_file(int fd)
{
	t_warrior	*warrior;
	t_opcode	*program;
	char		*line;
	int			y;

	if (!(warrior = (t_warrior *)malloc(sizeof(t_warrior))))
		error(strerror(errno));
	y = parse_title(warrior, fd);
	program = NULL;
	while ((line = read_input(fd)))
	{
		parse_line(&program, line, ++y);
		free(line);
	}
	close(fd);
	while (program->prev)
		program = program->prev;
	warrior->program = program;
	return (warrior);
}
