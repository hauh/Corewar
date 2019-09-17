/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_title.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:20:13 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 23:48:33 by smorty           ###   ########.fr       */
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
		if (!IS_BLANK(buf))
			error("Syntax Error");
	size = get_string_size(y, fd);
	if (!(s = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	read(fd, s, size + 1);
	s[size] = 0;
	if (errno)
		error(strerror(errno));
	return (s);
}

static int	check_token(const char *s, size_t size, int fd)
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
		{
			while (read(fd, &buf, 1) > 0 && buf != '\n')
				;
			++(*y);
		}
		else if (buf == '\n')
			++(*y);
		else if (!IS_BLANK(buf))
			break ;
	lseek(fd, -1, SEEK_CUR);
	if (errno)
		error(strerror(errno));
}

int			parse_title(t_warrior *warrior, int fd)
{
	int y;

	y = 0;
	warrior->name = NULL;
	warrior->comment = NULL;
	while (!warrior->name || !warrior->comment)
	{
		skip_until_token(&y, fd);
		if (!warrior->name && check_token(NAME_CMD_STRING,
									sizeof(NAME_CMD_STRING) - 1, fd))
			warrior->name = get_string(&y, fd);
		else if (!warrior->comment && check_token(COMMENT_CMD_STRING,
									sizeof(COMMENT_CMD_STRING) - 1, fd))
			warrior->comment = get_string(&y, fd);
		else
			error("Syntax error in title");
	}
	if (ft_strlen(warrior->name) > PROG_NAME_LENGTH)
		error("Name is too big");
	if (ft_strlen(warrior->comment) > COMMENT_LENGTH)
		error("Commentary is too big");
	return (y);
}
