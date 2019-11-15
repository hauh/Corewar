/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:11:48 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 22:42:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_int(int fd, size_t size)
{
	unsigned char	byte[size];
	int				num;
	int				i;

	if (read(fd, byte, size) < 0)
		error(strerror(errno), 0);
	num = 0;
	i = size;
	while (i--)
		num |= byte[size - i - 1] << (i * 8);
	return (num);
}

static void	print_string(char *token, int size, int fd, int fd_out)
{
	char byte[size + 1];

	if (read(fd, byte, size) < 0)
		error(strerror(errno), 0);
	byte[size + 1] = 0;
	ft_printf("{*}%s \"%s\"\n", fd_out, token, byte);
	get_int(fd, 4);
}

static void	print_params(int opcode, char params_code, int fd, int fd_out)
{
	int		i;
	char	type;

	i = 3;
	type = ((params_code >> (i-- * 2)) & 0x3);
	while (type)
	{
		if (type == crw_registry)
			ft_printf("{*}%c%hhd", fd_out, REGISTRY_CHAR, get_int(fd, T_REG));
		else if (type == crw_indirect)
			ft_printf("{*}%d", fd_out, get_int(fd, T_DIR));
		else if (opcode == crw_ldi || opcode == crw_sti || opcode == crw_lldi)
			ft_printf("{*}%c%hd", fd_out, DIRECT_CHAR, get_int(fd, T_DIR));
		else if (type)
			ft_printf("{*}%c%d", fd_out, DIRECT_CHAR, get_int(fd, T_IND));
		type = ((params_code >> (i-- * 2)) & 0x3);
		ft_printf((type ? "{*}, " : "{*}\n"), fd_out);
	}
}

static void	print_code(int fd, int fd_out)
{
	const char	*types[17] = {NULL, "live", "ld", "st", "add", "sub",
							"and", "or", "xor", "zjmp", "ldi", "sti",
							"fork", "lld", "lldi", "lfork", "aff"};
	char		byte;

	while (read(fd, &byte, 1) > 0)
	{
		if (errno)
			error(strerror(errno), 0);
		ft_printf("{*}%s ", fd_out, types[(t_opcode_type)byte]);
		if (byte == crw_live)
			ft_printf("{*}%c%d\n", fd_out, DIRECT_CHAR, get_int(fd, T_IND));
		else if (byte == crw_zjmp || byte == crw_fork || byte == crw_lfork)
			ft_printf("{*}%c%hd\n", fd_out, DIRECT_CHAR, get_int(fd, T_DIR));
		else if (byte == crw_aff)
			ft_printf("{*}%c%hhd\n", fd_out, REGISTRY_CHAR, get_int(fd, T_REG));
		else
			print_params((t_opcode_type)byte, get_int(fd, 1), fd, fd_out);
	}
}

void		disassemble(int fd, int fd_out)
{
	if (get_int(fd, sizeof(int)) != COREWAR_EXEC_MAGIC)
		error("Error: wrong magic number", 0);
	print_string(NAME_CMD_STRING, PROG_NAME_LENGTH, fd, fd_out);
	get_int(fd, sizeof(int));
	print_string(COMMENT_CMD_STRING, COMMENT_LENGTH, fd, fd_out);
	ft_printf("{*}\n", fd_out);
	print_code(fd, fd_out);
	close(fd_out);
}
