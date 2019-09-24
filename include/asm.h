/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/24 22:59:09 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define BUFF_SIZE 16

# define IS_BLANK(c) (c == ' ' || c == '\t')
# define IS_DIGIT(c) (c >= '0' && c <= '9')

extern int		g_cur_line;
extern int		g_cur_col;

typedef enum	e_opcode_type
{
	crw_undef_code,
	crw_live,
	crw_ld,
	crw_st,
	crw_add,
	crw_sub,
	crw_and,
	crw_or,
	crw_xor,
	crw_zjmp,
	crw_ldi,
	crw_sti,
	crw_fork,
	crw_lld,
	crw_lldi,
	crw_lfork,
	crw_aff
}				t_opcode_type;

typedef enum	e_param_type
{
	crw_undef_param,
	crw_registry,
	crw_direct,
	crw_indirect
}				t_param_type;

typedef struct	s_opcode_param
{
	char			*link;
	t_param_type	type;
	int				value;
}				t_opcode_param;

typedef struct	s_opcode
{
	char			*label;
	t_opcode_param	*param[3];
	t_opcode_type	type;
	size_t			size;
	unsigned char	param_code;
	struct s_opcode	*next;
	struct s_opcode	*prev;
}				t_opcode;

typedef struct	s_warrior
{
	char			*name;
	char			*comment;
	t_opcode		*program;
	unsigned char	*byte_code;
	size_t			code_size;
}				t_warrior;

char			*read_input(int fd);
void			skip_whitespaces(char **line);
int				ft_printf(const char *line, ...);
void			process_file(char *arg, int flag);
void			error(char *err, int type);

t_warrior		*parse_file(int fd);
void			parse_title(t_warrior *warrior, int fd);
void			parse_label(t_opcode *program, char **line);
void			parse_opcode(t_opcode *new, char *line);
t_opcode_param	*parse_parameter(char *line);

void			analyze_sizes(t_warrior *list);
void			assemble(t_warrior *warrior);
void			disassemble(int fd, int fd_out);

#endif
