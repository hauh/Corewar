/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/10 22:35:43 by smorty           ###   ########.fr       */
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

typedef struct	s_cor
{
	char			*line;
	struct s_cor	*next;
}				t_cor;

typedef struct	s_token
{
	char			*line;
	int				x;
	int				y;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

char			*read_input(int fd);
void			error(char *err);
t_cor			*parse_file(int fd);

#endif
