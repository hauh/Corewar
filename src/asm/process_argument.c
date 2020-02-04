/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:11:29 by smorty            #+#    #+#             */
/*   Updated: 2019/11/16 15:13:46 by smorty           ###   ########.fr       */
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
	if (flag & F_DISASSEMBLE ?
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
	*(new - (flag & F_DISASSEMBLE ? 4 : 2)) = 0;
	if (flag & F_OUTPUT_LOCAL)
	{
		while (new != file_name && *new != '/')
			--new;
		if (*new == '/')
			++new;
		file_name = new;
	}
	if (!(new = ft_strjoin(file_name, flag & F_DISASSEMBLE ? ".s" : ".cor")))
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
	if (flag & F_DISASSEMBLE)
		ft_printf("Writing output champion to %s\n", new_file);
	else
	{
		if (!(write(fd, warrior->byte_code, warrior->code_size)))
			error(strerror(errno), 0);
		close(fd);
		ft_printf("Writing output program to %s\n", new_file);
	}
	free(new_file);
	return (fd);
}

static void	cleanup(t_warrior *warrior)
{
	void *clean;

	while (warrior->program)
	{
		while (warrior->program->labels)
		{
			clean = (t_label *)warrior->program->labels;
			free(warrior->program->labels->label_name);
			warrior->program->labels = warrior->program->labels->next;
			free(clean);
		}
		if (warrior->program->param[0])
			free(warrior->program->param[0]);
		if (warrior->program->param[1])
			free(warrior->program->param[1]);
		if (warrior->program->param[2])
			free(warrior->program->param[2]);
		clean = (t_opcode *)warrior->program;
		warrior->program = warrior->program->next;
		free(clean);
	}
	free(warrior->name);
	free(warrior->comment);
	free(warrior->byte_code);
	free(warrior);
}

void		process_argument(char *arg, int flag)
{
	t_warrior *warrior;

	if (flag & F_DISASSEMBLE)
		disassemble(open_file(arg, flag), build_file(NULL, arg, flag));
	else
	{
		warrior = parse_file(open_file(arg, flag));
		calculate_sizes(warrior);
		assemble(warrior);
		build_file(warrior, arg, flag);
		cleanup(warrior);
	}
}
