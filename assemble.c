/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:10:03 by smorty            #+#    #+#             */
/*   Updated: 2019/09/12 22:12:05 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	num_to_bytes(unsigned char **code, int num)
{
	*(*code)++ = (unsigned char)((num >> 24) & 0xff);
	*(*code)++ = (unsigned char)((num >> 16) & 0xff);
	*(*code)++ = (unsigned char)((num >> 8) & 0xff);
	*(*code)++ = (unsigned char)(num & 0xff);
}

static unsigned char	*assemble_name(t_token **list)
{
	unsigned char	*name_code;
	unsigned char	*p;
	char			*s;
	size_t			size;

	size = PROG_NAME_LENGTH + COMMENT_LENGTH + 24;
	if (!(name_code = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		error(strerror(errno));
	ft_bzero(name_code, size);
	p = name_code;
	num_to_bytes(&p, COREWAR_EXEC_MAGIC);
	s = (*list)->next->line;
	while (*s)
		*p++ = *s++;
	p = name_code + PROG_NAME_LENGTH + 16;
	*list = (*list)->next->next->next;
	s = (*list)->line;
	while (*s)
		*p++ = *s++;
	*list = (*list)->next;
	return (name_code);
}

// void code_live(t_token **list, unsigned char *exec_code)
// {
// 	*exec_code++ = 0x01;
// 	*list = (*list)->next;
// 	*exec_code++ = list->line[1] - '0';
// }

int	find_label(t_token *list, char *label)
{
	t_token	*start;
	int		size;
	int		len;

	len = ft_strlen(label);
	start = list;
	size = 0;
	while (list && list->prev)
	{
		if (list->type == crw_registry)
			size += T_REG;
		else if (list->type == crw_direct)
			size += T_DIR;
		else if (list->type == crw_indirect)
			size += T_IND;
		else if (list->type )
		if (ft_strnequ(list->line, label, len))
			return (size);
	}
	list = start;
	size = 0;
	while (list && list->prev)
	{
		if (list->type == crw_registry)
			size += T_REG;
		else if (list->type == crw_direct)
			size += T_DIR;
		else if (list->type == crw_indirect)
			size += T_IND;
		if (ft_strequ(list->line, label))
			return (~size);
	}
	return (0);
}

void code_args(t_token **list, unsigned char *args, unsigned char *code, int count)
{
	int i;

	i = 0;
	*args = 0;
	while (i < count)
	{
		if ((*list)->type == crw_registry)
		{
			*args |= 1 << (count - i) * 2;
			*code++ = ft_atoi((*list)->line[1]);
		}
		else if ((*list)->type == crw_direct)
		{
			*args |= 2 << (count - i) * 2;
			num_to_bytes(&code, ft_atoi((*list)->line[1]));
		}
		else if ((*list)->type == crw_indirect)
		{
			*args |= 3 << (count - i) * 2;
			num_to_bytes(&code, find_label(*list, &list->line[2]));
		}
		++i;
		*list = (*list)->next;
	}
}

void code_sti(t_token **list, unsigned char *exec_code)
{
	*exec_code++ = 0x0b;
	*list = (*list)->next;
	code_args(list, exec_code, exec_code + 1, 3);
	*exec_code++ =
}

void code_ld(t_token *list, unsigned char *exec_code)
{
	*exec_code++ = 1;
}



unsigned char *assemble_code(t_token *list)
{
	unsigned char *exec_code;


}

void		assemble(t_token *list)
{
	unsigned char	*name_code;
	unsigned char	*exec_code;

	name_code = assemble_name(&list);
	exec_code = assemble_code(list);
//	print_list(list);
	
}
