/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 23:08:37 by smorty            #+#    #+#             */
/*   Updated: 2019/09/16 23:45:51 by smorty           ###   ########.fr       */
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

void					parse_opcode(t_opcode *new, char *line, int x)
{
	int i;

	x += skip_whitespaces(&line);
	new->x = x;
	new->type = get_opcode_type(&line, &x);
	x += skip_whitespaces(&line);
	i = -1;
	while (++i < 3)
		new->param[i] = parse_parameter(&line, &x, new->y);
}
