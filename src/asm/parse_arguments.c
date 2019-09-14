/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 23:08:37 by smorty            #+#    #+#             */
/*   Updated: 2019/09/14 23:39:21 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			save_argument(t_argument *arg, char **line, int *x)
{
	char *p;

	arg->type = crw_undefined;
	if (**line == REGISTRY_CHAR)
	{
		arg->type = crw_registry;
		arg->val = ft_atoi(*line + 1);
	}
	else if (**line == DIRECT_CHAR)
	{
		++(*line);
		++(*x);
		if (**line == LABEL_CHAR)
		{
			arg->type = crw_indirect;
			p = *line + 1;
		}
		else if ((**line >= '0' && **line <= '9') || **line == '-')
		{
			arg->type = crw_direct;
			arg->val = ft_atoi(*line);
		}
	}
	if (arg->type == crw_undefined)
		error("Undefined argument");	
	while (**line && **line != ' ' && **line != '\t'
		&& **line != SEPARATOR_CHAR)
	{
		++(*line);
		++(*x);
	}
	if (arg->type == crw_indirect)
		arg->link = ft_strndup(p, *line - p);
}

static t_argument	*get_argument(char **line, int *x, int y)
{
	t_argument *arg;

	arg = NULL;
	while (**line
		&& (**line == ' ' || **line == '\t' || **line == SEPARATOR_CHAR))
	{
		++(*line);
		++(*x);
	}
	if (**line)
	{
		if (!(arg = (t_argument *)malloc(sizeof(t_argument))))
			error(strerror(errno));
		save_argument(arg, line, x);
		arg->x = *x;
		arg->y = y;
	}
	return (arg);
}

static t_token_type	get_type(char **line, int *x)
{
	const char	*types[18] = {NAME_CMD_STRING, COMMENT_CMD_STRING,
							"live", "ld", "st", "add", "sub", "and",
							"or", "xor", "zjmp", "ldi", "sti",
							"fork", "lld", "lldi", "lfork", "aff"};
	int			i;
	char		*p;

	while (**line && (**line == ' ' || **line == '\t'))
	{
		++(*line);
		++(*x);
	}
	p = *line;
	while (**line
		&& **line != ' ' && **line != '\t' && **line != SEPARATOR_CHAR)
	{
		++(*line);
		++(*x);
	}
	i = 0;
	while (i < 18 && !ft_strnequ(p, types[i], *line - p))
		++i;
	return (i);
}

static char			*get_label(char **line, int *x)
{
	char	*label;
	char	*p;
	int		size;

	p = *line;
	size = 0;
	while (*p && *p != ' ' && *p != '\t' && *p != LABEL_CHAR)
	{
		++size;
		++p;
	}
	if (*p != LABEL_CHAR)
		return (NULL);
	*x += size;
	if (!(label = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	p = label;
	while (size--)
		*p++ = *(*line)++;
	*p = 0;
	while (*++(*line) && (**line == ' ' || **line == '\t'))
		++(*x);
	return (label);
}

int					parse_arguments(t_token *new, char *line)
{
	int		x;
	int		i;

	x = 1;
	while (*line && (*line == ' ' || *line == '\t'))
	{
		++line;
		++x;
	}
	if (!new->label)
		if ((new->label = get_label(&line, &x)) && !*line)
			return (1);
	new->x = x;
	if ((new->type = get_type(&line, &x)) == crw_undefined)
		error("Undefined argument");
	i = 0;
	while (i < 3)
		new->arg[i++] = *line ? get_argument(&line, &x, new->y) : NULL;
	return (0);
}
