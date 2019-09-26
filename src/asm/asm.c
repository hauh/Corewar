/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 23:32:36 by smorty            #+#    #+#             */
/*   Updated: 2019/09/26 22:05:35 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_cur_line;
int g_cur_col;

void		error(char *err, int type)
{
	if (type)
		ft_printf("%s [%d:%d]\n", err, g_cur_line, g_cur_col);
	else
		ft_printf("%s\n", err);
	exit(11);
}

static void	usage(void)
{
	ft_printf("Usage: asm [-df] [file]\n"
			"\tif no -d flag specified asm will assemble file.s\n"
			"\tuse -d for dissamble file.cor\n"
			"\twith -f flag asm will output into current directory\n");
	exit(1);
}

static int	get_flag(char *arg)
{
	int flag;

	++arg;
	flag = 0;
	while (*arg)
	{
		if (*arg == 'd')
			flag |= F_DISASSEMBLE;
		else if (*arg == 'f')
			flag |= F_OUTPUT_LOCAL;
		else
			usage();
		++arg;
	}
	return (flag);
}

int			main(int argc, char **argv)
{
	int			flag;
	int			i;

	if (argc == 1)
		usage();
	i = 1;
	while (i < argc)
	{
		flag = argv[i][0] == '-' ? get_flag(argv[i++]) : 0;
		if (i == argc)
			error("File not specified", 0);
		process_argument(argv[i], flag);
		++i;
	}
	return (0);
}
