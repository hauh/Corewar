/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 23:32:36 by smorty            #+#    #+#             */
/*   Updated: 2019/09/19 17:45:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		error(char *err)
{
	ft_putendl(err);
	exit(-1);
}

static int	open_file(char *file_name)
{
	char	*p;
	int		fd;

	p = file_name;
	while (*p)
		++p;
	if (p - file_name < 3 || *(p - 1) != 's' || *(p - 2) != '.')
		error("Usage: asm file.s");
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error(strerror(errno));
	return (fd);
}

static void	build_file(t_warrior *warrior, char *name)
{
	char	*p;
	mode_t	mode;
	int		fd;

	p = name;
	while (*p)
		++p;
	*(p - 2) = 0;
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

int			main(int argc, char **argv)
{
	t_warrior	*warrior;
	int			i;

	if (argc == 1)
		error("Usage: asm file.s");
	i = 1;
	while (i < argc)
	{
		warrior = parse_file(open_file(argv[i]));
		analyze_sizes(warrior);
		assemble(warrior);
		build_file(warrior, argv[i]);
		cleanup(warrior);
		++i;
	}
	return (0);
}
