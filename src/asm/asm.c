/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 23:32:36 by smorty            #+#    #+#             */
/*   Updated: 2019/09/10 19:51:06 by smorty           ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	t_cor	*list;
	int		fd;

	if (argc != 2)
		error("Usage: asm file.s");
	fd = open_file(argv[1]);
	list = parse_file(fd);
	close(fd);
	return (0);
}
