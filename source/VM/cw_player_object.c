/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/27 12:18:33 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_set_id(player_t *p_player_instance, int *p_busy_byte,
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
			cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid number near -n");
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
		cwErrorCatcher(CW_NOT_VALID_KEY, "Not valid number near -n");
	}
}

static void	cw_read_file(player_t *p_player_instance, const char *p_file)
{
	int		fd;

	if ((fd = open(p_file, O_RDONLY)) < 0)
		cwErrorCatcher(CW_OPEN_FILE_ERROR, CW_PLAYER);
	if (read(fd, p_player_instance->p_source, CODE) < 0)
		cwErrorCatcher(CW_READ_FILE_ERROR, CW_PLAYER);
	close(fd);
}

static void	cw_self_validate(player_t *p_player_instance)
{
	int		check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (p_player_instance->binary_label != COREWAR_EXEC_MAGIC)
		cwErrorCatcher(CW_INCORRECT_BINARY, CW_PLAYER);
	if (p_player_instance->code_size > CHAMP_MAX_SIZE)
		cwErrorCatcher(CW_TOO_BIG_SIZE, CW_PLAYER);
	while (!p_player_instance->p_code[check_size])
		--check_size;
	if (p_player_instance->code_size != check_size + 1)
		cwErrorCatcher(CW_CHEAT_DETECT, CW_PLAYER);
}

static void	cw_self_build(player_t *p_player_instance)
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

static void	cw_constructor(player_t **pp_player_instance)
{
	if (!((*pp_player_instance)->p_source =
	(unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_code =
	(unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_comment =
	(unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_name =
	(unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset((*pp_player_instance)->p_source, 0, CODE);
	ft_memset((*pp_player_instance)->p_code, 0, CHAMP_MAX_SIZE);
	ft_memset((*pp_player_instance)->p_comment, 0, COMMENT_LENGTH);
	ft_memset((*pp_player_instance)->p_name, 0, PROG_NAME_LENGTH);
	(*pp_player_instance)->binary_label = 0;
	(*pp_player_instance)->carriage_id = 0;
	(*pp_player_instance)->code_size = 0;
	(*pp_player_instance)->p_next = NULL;
	(*pp_player_instance)->p_prev = NULL;
}

static void	cw_destructor(player_t **pp_player_instance)
{
	free((*pp_player_instance)->p_source);
	free((*pp_player_instance)->p_code);
	free((*pp_player_instance)->p_comment);
	free((*pp_player_instance)->p_name);
	free((*pp_player_instance));
	*pp_player_instance = NULL;
}

extern void	cw_create_instance_player(player_t **pp_player_obj)
{
	if (!(*pp_player_obj = (player_t *)malloc(sizeof(player_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_PLAYER);
	(*pp_player_obj)->cw_constructor = cw_constructor;
	(*pp_player_obj)->cw_destructor = cw_destructor;
	(*pp_player_obj)->cw_set_id = cw_set_id;
	(*pp_player_obj)->cw_read_file = cw_read_file;
	(*pp_player_obj)->cw_self_build = cw_self_build;
	(*pp_player_obj)->cw_self_validate = cw_self_validate;
	(*pp_player_obj)->cw_constructor(pp_player_obj);
}
