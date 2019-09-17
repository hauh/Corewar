/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 23:31:59 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 22:14:53 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_dir_indir_value(char *line)
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
	while (IS_DIGIT(*line))
	{
		val = val * 10 + (*line - 48);
		if (val >= IDX_MOD)
			val %= IDX_MOD;
		++line;
	}
	if (*line && *line != SEPARATOR_CHAR && !IS_BLANK(*line))
		error("Syntax error in parameter value");
	return (val * sign);
}

static char		*get_label_link(char *line)
{
	char	*link;
	size_t	size;

	size = 0;
	while (line[size] && line[size] != SEPARATOR_CHAR && !IS_BLANK(line[size]))
		++size;
	if (!size)
		error("Syntax error in 'label' link");
	if (!(link = (char *)malloc(sizeof(char) * size)))
		error(strerror(errno));
	link[size] = 0;
	while (size--)
		link[size] = line[size];
	return (link);
}

static int		get_registry_value(char *line)
{
	int val;

	if (!IS_DIGIT(*line))
		error("Syntax error in 'r' token");
	val = *line++ - 48;
	if (IS_DIGIT(*line))
		val = val * 10 + (*line++ - 48);
	if (!val || (*line && *line != SEPARATOR_CHAR && !IS_BLANK(*line)))
		error("Syntax error in 'r' token");
	return (val);
}

static void		get_parameter(t_opcode_param *param, char *line)
{
	if (*line == REGISTRY_CHAR)
	{
		param->type = crw_registry;
		param->value = get_registry_value(line + 1);
		return ;
	}
	if (*line == DIRECT_CHAR)
	{
		param->type = crw_direct;
		++line;
	}
	else if (*line == LABEL_CHAR || IS_DIGIT(*line) || *line == '-')
		param->type = crw_indirect;
	else
		error("Syntax error at parameter type");
	if (*line == LABEL_CHAR)
		param->link = get_label_link(line + 1);
	else
		param->value = get_dir_indir_value(line);
}

t_opcode_param	*parse_parameter(char *line)
{
	t_opcode_param *param;

	param = NULL;
	if (*line)
	{
		if (!(param = (t_opcode_param *)malloc(sizeof(t_opcode_param))))
			error(strerror(errno));
		param->value = 0;
		param->link = NULL;
		get_parameter(param, line);
	}
	return (param);
}
