/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/11 23:00:45 by smorty           ###   ########.fr       */
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
	crw_undefined
}				t_token_type;

typedef struct	s_cor
{
	char			*line;
	struct s_cor	*next;
}				t_cor;

typedef struct	s_token
{
	char			*line;
	t_token_type	type;
	int				x;
	int				y;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

void			error(char *err);
t_token			*parse_file(int fd);

void			print_list(t_token *list); //temp

#endif
