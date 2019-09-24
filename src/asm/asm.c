/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 23:32:36 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 17:36:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		error(char *err)
{
	ft_putendl(err);
	exit(-1);
}

static void	usage(void)
{
	ft_printf("Usage: asm [-df] [file]\n"
			"\tif no -d flag specified asm will assemble file.s\n"
			"\tuse -d for dissamble file.cor\n"
			"\twith -f flag asm will output into it's directory instead of file's\n");
	exit(1);
}

static int	open_file(char *file_name, int flag)
{
	char	*p;
	int		fd;

	p = file_name;
	while (*p)
		++p;
	if ((flag & 1 && (p - file_name < 5 || !ft_strequ(p - 4, ".cor")))
		|| (!(flag & 1) && (p - file_name < 3 || !ft_strequ(p - 2, ".s"))))
		error("Wrong filename (need .s or .cor with -d flag)");
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error(strerror(errno));
	return (fd);
}

static void	build_file(t_warrior *warrior, char *name, int flag)
{
	char	*p;
	mode_t	mode;
	int		fd;

	p = name;
	while (*p)
		++p;
	*(p - 2) = 0;
	if (flag & 2)
	{
		while (p != name && *p != '/')
			--p;
		if (*p == '/')
			++p;
		name = p;
	}
	if (!(name = ft_strjoin(name, ".cor")))
		error(strerror(errno));
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, mode);
	write(fd, warrior->byte_code, warrior->code_size);
	ft_printf("Writing output program to %s\n", name);
	close(fd);
	free(name);
}

static void	cleanup(t_warrior *warrior)
{
	t_opcode *clean;

	while (warrior->program)
	{
		clean = warrior->program;
		warrior->program = warrior->program->next;
		if (clean->label)
			free(clean->label);
		if (clean->param[0])
			free(clean->param[0]);
		if (clean->param[1])
			free(clean->param[1]);
		if (clean->param[2])
			free(clean->param[2]);
		free(clean);
	}
	free(warrior->name);
	free(warrior->comment);
	free(warrior->byte_code);
	free(warrior);
}

static int	get_flag(char *arg)
{
	int flag;

	++arg;
	flag = 0;
	while (*arg)
	{
		if (*arg == 'd')
			flag |= 1;
		else if (*arg == 'f')
			flag |= 2;
		else
			usage();
		++arg;
	}
	return (flag);
}

int			main(int argc, char **argv)
{
	t_warrior	*warrior;
	int			i;
	int			flag;

	if (argc == 1)
		usage();
	i = 1;
	while (i < argc)
	{
		flag = argv[i][0] == '-' ? get_flag(argv[i++]) : 0;
		if (!(flag & 1))
		{
			warrior = parse_file(open_file(argv[i], flag));
			analyze_sizes(warrior);
			assemble(warrior);
			build_file(warrior, argv[i], flag);
			cleanup(warrior);
		}
		else
			disassemble(open_file(argv[i], flag));
		++i;
	}
	return (0);
}
