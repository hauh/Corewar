/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 15:56:35 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_player **pp_player_instance)
{
	if (!((*pp_player_instance)->p_source =
	(unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_code =
	(unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_comment =
	(unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_PLAYER);
	if (!((*pp_player_instance)->p_name =
	(unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_PLAYER);
	ft_memset((*pp_player_instance)->p_source, 0, CODE);
	ft_memset((*pp_player_instance)->p_code, 0, CHAMP_MAX_SIZE);
	ft_memset((*pp_player_instance)->p_comment, 0, COMMENT_LENGTH);
	ft_memset((*pp_player_instance)->p_name, 0, PROG_NAME_LENGTH);
	(*pp_player_instance)->binary_label = 0;
	(*pp_player_instance)->live_amount = 0;
	(*pp_player_instance)->carriage_id = 0;
	(*pp_player_instance)->code_size = 0;
	(*pp_player_instance)->p_next = NULL;
	(*pp_player_instance)->p_prev = NULL;
}

static void	cw_destructor(t_player **pp_player_instance)
{
	free((*pp_player_instance)->p_source);
	free((*pp_player_instance)->p_code);
	free((*pp_player_instance)->p_comment);
	free((*pp_player_instance)->p_name);
	free((*pp_player_instance));
	*pp_player_instance = NULL;
}

extern void	cw_create_instance_player(t_player **pp_player_obj)
{
	if (!(*pp_player_obj = (t_player *)malloc(sizeof(t_player))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_PLAYER);
	(*pp_player_obj)->cw_constructor = cw_constructor;
	(*pp_player_obj)->cw_destructor = cw_destructor;
	(*pp_player_obj)->cw_set_id = cw_set_id;
	(*pp_player_obj)->cw_read_file = cw_read_file;
	(*pp_player_obj)->cw_self_build = cw_self_build;
	(*pp_player_obj)->cw_self_validate = cw_self_validate;
	(*pp_player_obj)->cw_constructor(pp_player_obj);
}
