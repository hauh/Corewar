/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:11:48 by smorty            #+#    #+#             */
/*   Updated: 2019/09/19 19:32:40 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_string(unsigned char **code, const char *token, size_t size)
{
	*(code + size) = 0;
	ft_printf("%s %s\n", token, *code);
	*code += size + 4;
}

void		disassemble(int fd)
{
	unsigned char *code;

	code = (unsigned char *)read_input(fd);
	// ft_printf("%s %x\n", code, *(unsigned int *)code);
	// if (*(int *)code != COREWAR_EXEC_MAGIC)
	// 	error("Wrong magic number");
	code += sizeof(COREWAR_EXEC_MAGIC);
	print_string(&code, NAME_CMD_STRING, PROG_NAME_LENGTH);
	code += 4;
	print_string(&code, COMMENT_CMD_STRING, COMMENT_LENGTH);
}
