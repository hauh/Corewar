// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse_file.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/09/10 19:51:16 by smorty            #+#    #+#             */
// /*   Updated: 2019/09/12 19:51:37 by smorty           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "asm.h"

// static int	save_name_string(t_token **list, int fd, int x, int y)
// {
// 	t_token	*token;
// 	int		len;
// 	char	buf;

// 	if (!(token = (t_token *)malloc(sizeof(t_token))))
// 		error(strerror(errno));
// 	token->x = x;
// 	token->y = y;
// 	token->next = NULL;
// 	if ((token->prev = *list))
// 		(*list)->next = token;
// 	*list = token;
// 	len = 1;
// 	while (read(fd, &buf, 1) > 0 && buf != '"')
// 	{
// 		++len;
// 		if (buf == '\n')
// 			++y;
// 	}
// 	if (buf != '"')
// 		error("Syntax Error");
// 	errno = 0;
// 	lseek(fd, -len, SEEK_CUR);
// 	token->line = (char *)malloc(sizeof(char) * len);
// 	if (errno)
// 		error(strerror(errno));
// 	if (read(fd, token->line, len) < 0)
// 		error(strerror(errno));
// 	token->line[len - 1] = 0;
// 	return (y);
// }

// static int	save_token(t_token **list, int fd, int x, int y)
// {
// 	t_token	*token;
// 	int		len;
// 	int		r;
// 	char	buf;

// 	len = 1;
// 	errno = 0;
// 	while ((r = read(fd, &buf, 1)) > 0
// 		&& buf != ' ' && buf != '\t' && buf != '\n' && buf != '"' && buf != SEPARATOR_CHAR)
// 		++len;
// 	lseek(fd, -len - r, SEEK_CUR);
// 	token = (t_token *)malloc(sizeof(t_token));
// 	if (errno)
// 		error(strerror(errno));
// 	if (!(token->line = (char *)malloc(sizeof(char) * (len + 1))))
// 		error(strerror(errno));
// 	if (read(fd, token->line, len) < 0)
// 		error(strerror(errno));
// 	token->line[len] = 0;
// 	token->next = NULL;
// 	if ((token->prev = *list))
// 		(*list)->next = token;
// 	*list = token;
// 	token->x = x;
// 	token->y = y;
// 	return (len);
// }

// static void	skip_comment(int fd)
// {
// 	char buf;

// 	errno = 0;
// 	while (read(fd, &buf, 1) > 0 && buf != '\n')
// 		;
// 	lseek(fd, 1, SEEK_CUR);
// 	if (errno)
// 		error(strerror(errno));
// }

// static void	typization(t_token *list)
// {
// 	const char	*types[18] = {NAME_CMD_STRING, COMMENT_CMD_STRING,
// 							"live", "ld", "st", "add", "sub", "and",
// 							"or", "xor", "zjmp", "ldi", "sti",
// 							"fork", "lld", "lldi", "lfork", "aff"};
// 	int			i;
// 	char		*p;

// 	while (list)
// 	{
// 		i = 0;
// 		while (i < 18 && !ft_strequ(list->line, types[i]))
// 			++i;
// 		if (i == 18)
// 		{
// 			p = list->line;
// 			if (*p == REGISTRY_CHAR && *(p + 1) >= '0' && *(p + 1) <= '9')
// 				i = crw_registry;
// 			else if (*p == DIRECT_CHAR)
// 				i = *(p + 1) == LABEL_CHAR ? crw_indirect : crw_direct;
// 		}
// 		list->type = i;
// 		list = list->next;
// 	}
// }

// t_token		*parse_file(int fd)
// {
// 	t_token *list;
// 	int		x;
// 	int		y;
// 	char	buf;

// 	list = NULL;
// 	y = 1;
// 	x = 1;
// 	errno = 0;
// 	while (read(fd, &buf, 1) > 0)
// 	{
// 		if (buf == '\n')
// 		{
// 			++y;
// 			x = 1;
// 		}
// 		else if (buf == COMMENT_CHAR || buf == COMMENT_CHAR_ALT)
// 			skip_comment(fd);
// 		else if (buf == '"')
// 			y = save_name_string(&list, fd, x, y);
// 		else if (buf != ' ' && buf != '\t' && buf != SEPARATOR_CHAR)
// 			x += save_token(&list, fd, x, y);
// 		else
// 			++x;
// 	}
// 	if (errno)
// 		error(strerror(errno));
// 	while (list->prev)
// 		list = list->prev;
// 	typization(list);
// 	return (list);
// }
