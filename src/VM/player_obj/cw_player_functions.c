/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:56:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 17:17:06 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_set_id(t_player *p_player_instance, int *p_busy_byte,
							int id, int custom_id)
{
	if (custom_id)
		if ((*p_busy_byte & (id << ((id - 1) * 8))) == id << ((id - 1) * 8)
		&& id > 0 && id < 5)
		{
			PL_ID_I = id;
			*p_busy_byte ^= (id << ((id - 1) * 8));
		}
		else
			cw_error_catcher(PL_OBJECT_NAME, PL_SET_ID_ERROR, __FILE__, S);
	else
	{
		while (id <= CW_MAX_PLAYERS)
		{
			if ((*p_busy_byte & (id << ((id - 1) * 8))) == id << ((id - 1) * 8))
			{
				PL_ID_I = id;
				*p_busy_byte ^= (id << ((id - 1) * 8));
				return ;
			}
			else
				++id;
		}
		cw_error_catcher(PL_OBJECT_NAME, PL_SET_ID_ERROR, __FILE__, __LINE__);
	}
}

static void	cw_read_file(t_player *p_player_instance, const char *p_file)
{
	t_mark	fd;

	if ((fd = open(p_file, O_RDONLY)) < 0)
		cw_error_catcher(PL_OBJECT_NAME, PL_OPEN_FILE_ERR, __FILE__, __LINE__);
	if (read(fd, p_player_instance->p_source, CODE) < 0)
		cw_error_catcher(PL_OBJECT_NAME, PL_READ_FILE_ERR, __FILE__, __LINE__);
	close(fd);
}

static void	cw_self_validate(t_player *p_player_instance)
{
	t_mark	check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (PL_BINARY_LABEL_I != COREWAR_EXEC_MAGIC)
		cw_error_catcher(PL_OBJECT_NAME, PL_BINARY_ERROR, __FILE__, __LINE__);
	if (PL_CODE_SIZE_I > CHAMP_MAX_SIZE)
		cw_error_catcher(PL_OBJECT_NAME, PL_TOO_BIG_SIZE, __FILE__, __LINE__);
	while (!PL_CODE_I[check_size])
		--check_size;
}

static void	cw_self_build(t_player *p_player_instance)
{
	t_iter	g_i;
	t_iter	l_i;

	g_i = CW_ITERATOR;
	while (++g_i < BINARY_LABEL)
		PL_BINARY_LABEL_I |= PL_SOURCE_I[g_i] << ((sizeof(int) - g_i - 1) * 8);
	l_i = 0;
	while (g_i < NAME)
		PL_NAME_I[l_i++] = PL_SOURCE_I[g_i++];
	PL_NAME_I[l_i] = 0;
	g_i += NULL_SEPARATOR;
	l_i = 0;
	while (g_i < CODE_SIZE)
		PL_CODE_SIZE_I |= PL_SOURCE_I[g_i++] << ((sizeof(int) - ++l_i) * 8);
	l_i = 0;
	while (g_i < COMMENT)
		PL_COMMENT_I[l_i++] = PL_SOURCE_I[g_i++];
	PL_COMMENT_I[l_i] = 0;
	g_i += NULL_SEPARATOR;
	l_i = 0;
	while (g_i < CODE)
		PL_CODE_I[l_i++] = PL_SOURCE_I[g_i++];
}

extern void	cw_player_functions_linker(t_player *p_player_instance)
{
	p_player_instance->cw_self_build = cw_self_build;
	p_player_instance->cw_self_validate = cw_self_validate;
	p_player_instance->cw_read_file = cw_read_file;
	p_player_instance->cw_set_id = cw_set_id;
}
