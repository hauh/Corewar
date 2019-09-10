/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:51:16 by smorty            #+#    #+#             */
/*   Updated: 2019/09/10 22:38:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void parse_name(t_cor **list, int fd)
{
	char	*buf;
	char	*p;
	int		len;

	if (!((*list)->next = (t_cor *)malloc(sizeof(t_cor))))
		error(strerror(errno));
	*list = (*list)->next;
	(*list)->next = NULL;
	len = ft_strlen(NAME_CMD_STRING);
	buf = read_input(fd);
	if (!ft_strnequ(buf, NAME_CMD_STRING, len))
		error("Error: no name command");
	p = buf + len;
	while (*p == ' ' || *p == '\t')
		++p;
	if (*p != '"' || !*(p + 1))
		error("Error: name is missing");
	if ((len = ft_strlen(++p) - 1) > PROG_NAME_LENGTH)
		error("Error: name is too long");
	if (!((*list)->line = (char *)malloc(sizeof(char) * len)))
		error(strerror(errno));
	(*list)->line[len] = 0;
	while (len--)
		(*list)->line[len] = p[len];
	free(buf);
}

static void	parse_comment(t_cor **list, int fd)
{
	char	*buf;
	char	*p;
	int		len;

	if (!((*list)->next = (t_cor *)malloc(sizeof(t_cor))))
		error(strerror(errno));
	*list = (*list)->next;
	(*list)->next = NULL;
	len = ft_strlen(COMMENT_CMD_STRING);
	buf = read_input(fd);
	if (!ft_strnequ(buf, COMMENT_CMD_STRING, len))
		error("Error: no comment command");
	p = buf + len;
	while (*p == ' ' || *p == '\t')
		++p;
	if (*p != '"' || !*(p + 1))
		error("Error: comment is missing");
	if ((len = ft_strlen(++p) - 1) > COMMENT_LENGTH)
		error("Error: comment is too long");
	if (!((*list)->line = (char *)malloc(sizeof(char) * len)))
		error(strerror(errno));
	(*list)->line[len] = 0;
	while (len--)
		(*list)->line[len] = p[len];
	free(buf);
}

int save_token(int fd)
{
	int		len;
	char	buf;

	len = 0;
	while (read(fd, &buf, 1) && buf != ' ' && buf != ' ' && buf != '\t' && buf != '\'' && buf)
		++len;
	lseek(fd, SEEK_CUR, -len);
}

void parse(int fd)
{
	int		size;
	int		x;
	int		y;
	char	buf;

	y = 1;
	size = 0;
	while (read(fd, &buf, 1))
	{
		++x;
		if (buf == '\n')
		{
			++y;
			x = 0;
		}
		else if (buf != ' ' && buf != '\t' && buf != '\'')
		{
			
		}
	}
	++size;
	ft_putnbr(size);
	lseek(fd, SEEK_SET, 0);
	while (read(fd, &buf, 1))
		++size;
	exit(0);
}



t_cor		*parse_file(int fd)
{
	t_cor	*list;
	t_cor	*head;
	char	*buf;

	parse(fd);
	if (!(head = (t_cor *)malloc(sizeof(t_cor))))
		error(strerror(errno));
	list = head;
	buf = read_input(fd);
	parse_name(&list, fd);
		ft_putendl(list->line);
	parse_comment(&list, fd);
		ft_putendl(list->line);
	return (head);
}
