/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 23:32:36 by smorty            #+#    #+#             */
/*   Updated: 2019/09/18 23:26:50 by smorty           ###   ########.fr       */
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

static int	check_endian(void)
{
	unsigned int	i;
	char			*c;

	i = 1;
	c = (char *)&i;
	return (*c ? 1 : 0);
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
	write(fd, warrior->byte_code, warrior->total_size);
	ft_printf("Writing output program to %s\n", name);
}

int			main(int argc, char **argv)
{
	t_warrior *warrior;

	if (argc != 2)
		error("Usage: asm file.s");
	warrior = parse_file(open_file(argv[1]));
	analyze_sizes(warrior);
	warrior->endian = check_endian();
	assemble(warrior);
	build_file(warrior, argv[1]);
	return (0);
}
