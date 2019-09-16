/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 23:31:59 by smorty            #+#    #+#             */
/*   Updated: 2019/09/16 23:54:25 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			crw_atoi(char *line)
{
	int	val;
	int	sign;

	if (*line == '-')
	{
		++line;
		sign = -1;
	}
	else
		sign = 1;
	while (*line >= '0' && *line <= '9')
	{
		val = val * 10 + (*line - 48);
		if (val >= IDX_MOD)
			val %= IDX_MOD;
		++line;
	}
	if (*line && *line != SEPARATOR_CHAR && *line != ' ' && *line != '\t')
		error("Syntax error in parameter value");
	return (val * sign);
}

static char			*crw_strdup(char *line)
{
	char	*link;
	size_t	size;

	size = 0;
	while (line[size] && line[size] != SEPARATOR_CHAR
		&& line[size] != ' ' && line[size] != '\t')
		++size;
	if (!(link = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	link[size] = 0;
	while (size--)
		link[size] = line[size];
	return (link);
}

static void			get_param_value(t_opcode_param *param, char *line)
{
	if (param->type == crw_registry || param->type == crw_direct)
		++line;
	if (*line == LABEL_CHAR && param->type != crw_registry)
	{
		param->value = 0;
		param->link = crw_strdup(line + 1);
	}
	else if (*line == '-' || (*line >= '0' && *line <= '9'))
	{
		param->value = crw_atoi(line);
		param->link = NULL;
	}
	else
		error("Wrong parameter value");
}

static t_param_type	get_param_type(char *line)
{
	if (*line == REGISTRY_CHAR)
		return (crw_registry);
	if (*line == DIRECT_CHAR)
		return (crw_direct);
	if (*line == LABEL_CHAR || *line == '-' || (*line >= '0' && *line <= '9'))
		return (crw_indirect);
	error("Wrong parameter");
	return (crw_undef_param);
}

t_opcode_param		*parse_parameter(char **line, int *x, int y)
{
	t_opcode_param *param;

	param = NULL;
	if (**line)
	{
		if (!(param = (t_opcode_param *)malloc(sizeof(t_opcode_param))))
			error(strerror(errno));
		param->type = get_param_type(*line);
		get_param_value(param, *line);
		param->x = *x;
		param->y = y;
		while (**line && **line != SEPARATOR_CHAR && **line != ' ' && **line != '\t')
		{
			++(*line);
			++(*x);
		}
		if (**line == SEPARATOR_CHAR)
		{
			++(*line);
			++(*x);
		}
		*x += skip_whitespaces(line);
	}
	return (param);
}
