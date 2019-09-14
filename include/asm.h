/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/14 19:36:23 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# include <stdio.h> // remove

# define BUFF_SIZE 16

typedef enum	e_token_type
{
	crw_name,
	crw_comment,
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
	crw_aff,
	crw_undefined,
	crw_registry,
	crw_direct,
	crw_indirect
}				t_token_type;

typedef struct	s_argument
{
	t_token_type	type;
	int				val;
	int				x;
	int				y;
}				t_argument;

typedef struct	s_token
{
	t_token_type	type;
	t_argument		*arg[3];
	char			*label;
	int				size;
	int				x;
	int				y;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

void			error(char *err);
char			*read_input(int fd);
t_token			*parse_file(int fd);
int				parse_arguments(t_token *new, char *line);

void			print_list(t_token *list); //temp

#endif
