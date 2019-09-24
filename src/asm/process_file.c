/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:11:29 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 22:47:56 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	open_file(char *file_name, int flag)
{
	char	*p;
	int		fd;

	p = file_name;
	while (*p)
		++p;
	if (flag & 1 ?
		p - file_name < 5 || !ft_strequ(p - 4, ".cor")
		: p - file_name < 3 || !ft_strequ(p - 2, ".s"))
		error("Wrong filename (need .s or .cor with -d flag)", 0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		error(strerror(errno), 0);
	return (fd);
}

static char	*get_new_filename(char *file_name, int flag)
{
	char	*new;

	new = file_name;
	while (*new)
		++new;
	*(new - (flag & 1 ? 4 : 2)) = 0;
	if (flag & 2)
	{
		while (new != file_name && *new != '/')
			--new;
		if (*new == '/')
			++new;
		file_name = new;
	}
	if (!(new = ft_strjoin(file_name, flag & 1 ? ".s" : ".cor")))
		error(strerror(errno), 0);
	return (new);
}

static int	build_file(t_warrior *warrior, char *name, int flag)
{
	char	*new_file;
	mode_t	mode;
	int		fd;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	new_file = get_new_filename(name, flag);
	if ((fd = open(new_file, O_CREAT | O_WRONLY | O_TRUNC, mode)) < 0)
		error(strerror(errno), 0);
	if (!(flag & 1))
	{
		write(fd, warrior->byte_code, warrior->code_size);
		close(fd);
		ft_printf("Writing output program to %s\n", new_file);
	}
	else
		ft_printf("Writing output champion to %s\n", new_file);
	free(new_file);
	return (fd);
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

void		process_file(char *arg, int flag)
{
	t_warrior *warrior;

	if (!(flag & 1))
	{
		warrior = parse_file(open_file(arg, flag));
		analyze_sizes(warrior);
		assemble(warrior);
		build_file(warrior, arg, flag);
		cleanup(warrior);
	}
	else
		disassemble(open_file(arg, flag), build_file(NULL, arg, flag));
}
