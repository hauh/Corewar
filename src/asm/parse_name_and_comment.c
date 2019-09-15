/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_and_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:20:13 by smorty            #+#    #+#             */
/*   Updated: 2019/09/15 22:26:46 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_string_size(int *y, int fd)
{
	int		size;
	char	buf;

	size = 0;
	while (read(fd, &buf, 1) > 0 && buf != '"')
	{
		++size;
		if (buf == '\n')
			++(*y);
	}
	if (buf != '"')
		error("Syntax Error");
	lseek(fd, -size - 1, SEEK_CUR);
	if (errno)
		error(strerror(errno));
	return (size);
}

static char	*get_string(int *y, int fd)
{
	char	*s;
	int		size;
	char	buf;

	while (read(fd, &buf, 1) > 0 && buf != '"')
		if (buf != ' ' && buf != '\t')
			error("Syntax Error");
	size = get_string_size(y, fd);
	if (!(s = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	read(fd, s, size + 1);
	s[size] = 0;
	while (read(fd, &buf, 1) > 0 && buf != '\n')
		if (buf == COMMENT_CHAR || buf == COMMENT_CHAR_ALT)
			while (read(fd, &buf, 1) > 0 && buf != '\n')
				;
		else if (buf != ' ' && buf != '\t')
			error("Syntax Error");
	if (errno)
		error(strerror(errno));
	return (s);
}

static int	check_string(const char *s, int size, int fd)
{
	char buf[size + 1];

	if (read(fd, buf, size) < 0)
		error(strerror(errno));
	buf[size] = 0;
	if (ft_strequ(s, buf))
		return (1);
	lseek(fd, -size, SEEK_CUR);
	if (errno)
		error(strerror(errno));
	return (0);
}

static void	skip_until_token(int *y, int fd)
{
	char buf;

	while (read(fd, &buf, 1) > 0)
		if (buf == COMMENT_CHAR || buf == COMMENT_CHAR_ALT)
			while (read(fd, &buf, 1) > 0 && buf != '\n')
				;
		else if (buf == '\n')
			++(*y);
		else if (buf != ' ' && buf != '\t')
			break ;
	lseek(fd, -1, SEEK_CUR);
	if (errno)
		error(strerror(errno));
}

void		parse_name_and_comment(t_warrior *warrior, int *y, int fd)
{
	warrior->name = NULL;
	warrior->comment = NULL;
	while (!warrior->name || !warrior->comment)
	{
		skip_until_token(y, fd);
		if (!warrior->name && check_string(NAME_CMD_STRING,
									sizeof(NAME_CMD_STRING) - 1, fd))
			warrior->name = get_string(y, fd);
		else if (!warrior->comment && check_string(COMMENT_CMD_STRING,
									sizeof(COMMENT_CMD_STRING) - 1, fd))
			warrior->comment = get_string(y, fd);
		else
			error("Syntax Error");
	}
}
