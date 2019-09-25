/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:12:14 by smorty            #+#    #+#             */
/*   Updated: 2019/09/26 00:26:30 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_cur_line;
int g_cur_col;

void			skip_whitespaces(char **line)
{
	while (**line && IS_BLANK(**line))
	{
		++(*line);
		++g_cur_col;
	}
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
		error(strerror(errno), 0);
	new->next = NULL;
	new->labels = NULL;
	new->type = crw_undef_code;
	new->param_code = 0;
	if ((new->prev = *program))
		(*program)->next = new;
	return (new);
}

static void		parse_line(t_opcode **program, char *line)
{
	g_cur_col = 1;
	skip_whitespaces(&line);
	trim_comment(line);
	if (!*line)
		return ;
	if (!(*program) || (*program)->type != crw_undef_code)
		*program = new_element(program);
	parse_label(*program, &line);
	parse_opcode(*program, line);
}

t_warrior		*parse_file(int fd)
{
	t_warrior	*warrior;
	t_opcode	*program;
	char		*line;

	if (!(warrior = (t_warrior *)malloc(sizeof(t_warrior))))
		error(strerror(errno), 0);
	g_cur_line = 1;
	g_cur_col = 1;
	parse_title(warrior, fd);
	program = NULL;
	while ((line = read_input(fd)))
	{
		parse_line(&program, line);
		free(line);
		++g_cur_line;
	}
	close(fd);
	while (program->prev)
		program = program->prev;
	warrior->program = program;
	return (warrior);
}
