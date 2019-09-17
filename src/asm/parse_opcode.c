/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 23:08:37 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 18:47:42 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_opcode_type	get_opcode_type(char **line, int *x)
{
	const char	*types[16] = {"live", "add", "sub", "and", "or", "xor",
							"sti", "st", "lfork", "fork", "lldi", "lld",
							"ldi", "ld", "zjmp", "aff"};
	size_t		size;
	int			i;

	i = 0;
	while (i < 16)
	{
		size = ft_strlen(types[i]);
		if (ft_strnequ(*line, types[i], size))
			break ;
		++i;
	}
	if (i == crw_undef_code)
		error("Undefined opcode");
	*line += size;
	*x += size;
	return (i);
}

static int				check_parameters(t_opcode_type type, int code)
{
	if ((type == crw_live || type == crw_aff || type == crw_fork
					|| type == crw_lfork) && code != 128)
		return (1);
	if ((type == crw_ld || type == crw_lld) && code != 144 && code != 208)
		return (1);
	if (type == crw_st && code != 80 && code != 112)
		return (1);
	if ((type == crw_add || type == crw_sub) && code != 84)
		return (1);
	if ((type == crw_and || type == crw_or || type == crw_xor)
						&& code != 84 && code != 100 && code != 116
						&& code != 148 && code != 164 && code != 180
						&& code != 212 && code != 228 && code != 244)
		return (1);
	if ((type == crw_ldi || type == crw_lldi)
						&& code != 84 && code != 100 && code != 148
						&& code != 164 && code != 212 && code != 228)
		return (1);
	if (type == crw_sti && code != 84 && code != 100 && code != 116
						&& code != 88 && code != 104 && code != 120)
		return (1);
	if (type == crw_aff && code != 64)
		return (1);
	return (0);
}

void					parse_opcode(t_opcode *new, char *line, int x)
{
	int i;

	x += skip_whitespaces(&line);
	new->x = x;
	new->type = get_opcode_type(&line, &x);
	new->param_code = 0;
	x += skip_whitespaces(&line);
	i = -1;
	while (++i < 3)
		if ((new->param[i] = parse_parameter(&line, &x, new->y)))
			new->param_code |= new->param[i]->type << ((3 - i) * 2);
	skip_whitespaces(&line);
	if (*line)
		error("Syntax error");
	if (check_parameters(new->type, new->param_code))
		error("Wrong parameters");
}
