/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 23:08:37 by smorty            #+#    #+#             */
/*   Updated: 2019/09/25 00:21:01 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_cur_col;

static t_opcode_type	get_opcode_type(char **line)
{
	static const char	*types[17] = {NULL, "live", "ld", "st", "add", "sub",
									"and", "or", "xor", "zjmp", "ldi", "sti",
									"fork", "lld", "lldi", "lfork", "aff"};
	size_t				size;
	int					i;

	i = 17;
	while (--i)
	{
		size = ft_strlen(types[i]);
		if (ft_strnequ(*line, types[i], size))
			break ;
	}
	if (i == crw_undef_code)
		error("Lexical error: invalid instruction", 1);
	*line += size;
	g_cur_col += size;
	return (i);
}

static int				validate_parameters(t_opcode_type type, int code)
{
	if ((type == crw_live || type == crw_fork || type == crw_lfork)
		&& code != 128)
		return (0);
	if ((type == crw_ld || type == crw_lld) && code != 144 && code != 208)
		return (0);
	if (type == crw_st && code != 80 && code != 112)
		return (0);
	if ((type == crw_add || type == crw_sub) && code != 84)
		return (0);
	if ((type == crw_and || type == crw_or || type == crw_xor)
						&& code != 84 && code != 100 && code != 116
						&& code != 148 && code != 164 && code != 180
						&& code != 212 && code != 228 && code != 244)
		return (0);
	if ((type == crw_ldi || type == crw_lldi)
						&& code != 84 && code != 100 && code != 148
						&& code != 164 && code != 212 && code != 228)
		return (0);
	if (type == crw_sti && code != 84 && code != 100 && code != 116
						&& code != 88 && code != 104 && code != 120)
		return (0);
	if (type == crw_aff && code != 64)
		return (0);
	return (1);
}

static void				skip_to_separator(char **line)
{
	while (**line && !IS_BLANK(**line) && **line != SEPARATOR_CHAR)
	{
		++(*line);
		++g_cur_col;
	}
}

void					parse_opcode(t_opcode *opcode, char *line)
{
	int i;

	skip_whitespaces(&line);
	if (!*line)
		return ;
	opcode->type = get_opcode_type(&line);
	i = 0;
	while (i < 3)
	{
		skip_whitespaces(&line);
		if ((opcode->param[i] = parse_parameter(line)))
		{
			opcode->param_code |= opcode->param[i]->type << ((3 - i) * 2);
			skip_to_separator(&line);
			skip_whitespaces(&line);
			if (*line && (*line++ != SEPARATOR_CHAR || i == 2))
				error("Syntax error: wrong parameters", 1);
		}
		++i;
	}
	if (!validate_parameters(opcode->type, opcode->param_code))
		error("Syntax error: wrong parameters types", 1);
}
