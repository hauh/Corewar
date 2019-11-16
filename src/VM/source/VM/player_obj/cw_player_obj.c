/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_player_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 17:17:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_player **pp_player_instance)
{
	if (!((*pp_player_instance)->p_source =
	(unsigned char *)malloc(sizeof(unsigned char) * CODE + 1)))
		cw_error_catcher(PL_OBJECT_NAME, PL_SOURCE_ERROR, __FILE__, __LINE__);
	if (!((*pp_player_instance)->p_code =
	(unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE + 1)))
		cw_error_catcher(PL_OBJECT_NAME, PL_SOURCE_ERROR, __FILE__, __LINE__);
	if (!((*pp_player_instance)->p_comment =
	(unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH + 1)))
		cw_error_catcher(PL_OBJECT_NAME, PL_SOURCE_ERROR, __FILE__, __LINE__);
	if (!((*pp_player_instance)->p_name =
	(unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH + 1)))
		cw_error_catcher(PL_OBJECT_NAME, PL_SOURCE_ERROR, __FILE__, __LINE__);
	ft_memset((*pp_player_instance)->p_source, 0, CODE);
	ft_memset((*pp_player_instance)->p_code, 0, CHAMP_MAX_SIZE);
	ft_memset((*pp_player_instance)->p_comment, 0, COMMENT_LENGTH);
	ft_memset((*pp_player_instance)->p_name, 0, PROG_NAME_LENGTH);
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
		cw_error_catcher(PL_OBJECT_NAME, PL_OBJECT_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_player_obj, 0, sizeof(t_player));
	(*pp_player_obj)->cw_constructor = cw_constructor;
	(*pp_player_obj)->cw_destructor = cw_destructor;
	(*pp_player_obj)->cw_constructor(pp_player_obj);
	cw_player_functions_linker(*pp_player_obj);
}
