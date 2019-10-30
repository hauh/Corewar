/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:56:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 15:57:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_set_id(t_player *p_player_instance, int *p_busy_byte,
							int id, int custom_id)
{
	if (custom_id)
	{
		if ((*p_busy_byte & (id << ((id - 1) * 8))) == id << ((id - 1) * 8))
		{
			p_player_instance->id = id;
			*p_busy_byte ^= (id << ((id - 1) * 8));
		}
		else
			cw_error_catcher(CW_NOT_VALID_KEY, "Not valid number near -n");
	}
	else
	{
		while (id <= CW_MAX_PLAYERS)
		{
			if ((*p_busy_byte & (id << ((id - 1) * 8))) == id << ((id - 1) * 8))
			{
				p_player_instance->id = id;
				*p_busy_byte ^= (id << ((id - 1) * 8));
				return ;
			}
			else
				++id;
		}
		cw_error_catcher(CW_NOT_VALID_KEY, "Not valid number near -n");
	}
}

void	cw_read_file(t_player *p_player_instance, const char *p_file)
{
	int		fd;

	if ((fd = open(p_file, O_RDONLY)) < 0)
		cw_error_catcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
	if (read(fd, p_player_instance->p_source, CODE) < 0)
		cw_error_catcher(CW_READ_FILE_ERROR, CW_PLAYER);
	close(fd);
}

void	cw_self_validate(t_player *p_player_instance)
{
	int		check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (p_player_instance->binary_label != COREWAR_EXEC_MAGIC)
		cw_error_catcher(CW_INCORRECT_BINARY, CW_PLAYER);
	if (p_player_instance->code_size > CHAMP_MAX_SIZE)
		cw_error_catcher(CW_TOO_BIG_SIZE, CW_PLAYER);
	while (!p_player_instance->p_code[check_size])
		--check_size;
	if (p_player_instance->code_size != check_size + 1)
		cw_error_catcher(CW_CHEAT_DETECT, CW_PLAYER);
}

void	cw_self_build(t_player *p_player_instance)
{
	int		g_i;
	int		l_i;

	g_i = -1;
	while (++g_i < BINARY_LABEL)
		p_player_instance->binary_label |= p_player_instance->
			p_source[g_i] << ((sizeof(int) - g_i - 1) * 8);
	l_i = 0;
	while (g_i < NAME)
		p_player_instance->p_name[l_i++] = p_player_instance->p_source[g_i++];
	p_player_instance->p_name[l_i] = 0;
	g_i += NULL_SEPARATOR;
	l_i = 0;
	while (g_i < CODE_SIZE)
		p_player_instance->code_size |= p_player_instance->
			p_source[g_i++] << ((sizeof(int) - ++l_i) * 8);
	l_i = 0;
	while (g_i < COMMENT)
		p_player_instance->p_comment[l_i++] = p_player_instance->
			p_source[g_i++];
	p_player_instance->p_comment[l_i] = 0;
	g_i += NULL_SEPARATOR;
	l_i = 0;
	while (g_i < CODE)
		p_player_instance->p_code[l_i++] = p_player_instance->p_source[g_i++];
}
