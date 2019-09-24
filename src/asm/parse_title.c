/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_title.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:20:13 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 23:02:01 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_cur_line;

static int	get_string_size(int fd)
{
	int		size;
	char	buf;

	size = 0;
	while (read(fd, &buf, 1) > 0 && buf != '"')
	{
		++size;
		if (buf == '\n')
			++g_cur_line;
	}
	if (buf != '"')
		error("Syntax error", 1);
	lseek(fd, -size - 1, SEEK_CUR);
	if (errno)
		error(strerror(errno), 0);
	return (size);
}

static char	*get_string(int fd)
{
	char	*s;
	int		size;
	char	buf;

	while (read(fd, &buf, 1) > 0 && buf != '"')
		if (!IS_BLANK(buf))
			error("Syntax error", 1);
	size = get_string_size(fd);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		error(strerror(errno), 0);
	read(fd, s, size + 1);
	s[size] = 0;
	if (errno)
		error(strerror(errno), 0);
	return (s);
}

static int	check_token(const char *s, size_t size, int fd)
{
	char buf[size + 1];

	if (read(fd, buf, size) < 0)
		error(strerror(errno), 0);
	buf[size] = 0;
	if (ft_strequ(s, buf))
		return (1);
	lseek(fd, -size, SEEK_CUR);
	if (errno)
		error(strerror(errno), 0);
	return (0);
}

static void	skip_until_token(int fd)
{
	char buf;

	while (read(fd, &buf, 1) > 0)
		if (buf == COMMENT_CHAR || buf == COMMENT_CHAR_ALT)
		{
			while (read(fd, &buf, 1) > 0 && buf != '\n')
				;
			++g_cur_line;
		}
		else if (buf == '\n')
			++g_cur_line;
		else if (!IS_BLANK(buf))
			break ;
	lseek(fd, -1, SEEK_CUR);
	if (errno)
		error(strerror(errno), 0);
}

void		parse_title(t_warrior *warrior, int fd)
{
	warrior->name = NULL;
	warrior->comment = NULL;
	while (!warrior->name || !warrior->comment)
	{
		skip_until_token(fd);
		if (!warrior->name && check_token(NAME_CMD_STRING,
									sizeof(NAME_CMD_STRING) - 1, fd))
			warrior->name = get_string(fd);
		else if (!warrior->comment && check_token(COMMENT_CMD_STRING,
									sizeof(COMMENT_CMD_STRING) - 1, fd))
			warrior->comment = get_string(fd);
		else
			error("Syntax error: wrong title", 1);
	}
	if (ft_strlen(warrior->name) > PROG_NAME_LENGTH)
		error("Error: name is too big", 0);
	if (ft_strlen(warrior->comment) > COMMENT_LENGTH)
		error("Error: commentary is too big", 0);
}
