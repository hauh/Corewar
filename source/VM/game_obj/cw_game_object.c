/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/15 12:55:30 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_corewar **pp_game_instance)
{
	(*pp_game_instance)->ncurses = CW_FALSE;
	(*pp_game_instance)->stealth = CW_FALSE;
	(*pp_game_instance)->mini = CW_FALSE;

}

static void	cw_destructor(t_corewar **pp_game_instance)
{
	t_iter	iter;

	iter = CW_BEGIN_FROM_ZERO;
	cr_vis_main(*pp_game_instance, V_CLEANUP);
	while (++iter < CW_COMMAND_AMOUNT)
		(*pp_game_instance)->pa_commands[iter]->
			cw_destructor(&(*pp_game_instance)->pa_commands[iter]);
	(*pp_game_instance)->p_arena_obj->
		cw_destructor(&(*pp_game_instance)->p_arena_obj);
	(*pp_game_instance)->p_scheduler->
		cw_destructor(&(*pp_game_instance)->p_scheduler);
	free(*pp_game_instance);
	*pp_game_instance = NULL;
}

extern void	cw_create_instance_game(t_corewar **pp_game_obj)
{
	if (!(*pp_game_obj = (t_corewar *)malloc(sizeof(t_corewar))))
		cw_error_catcher(GA_OBJ_NAME, GA_OBJ_ERROR, __FILE__, __LINE__);
	ft_memset(*pp_game_obj, 0, sizeof(t_corewar));
	(*pp_game_obj)->cw_constructor = cw_constructor;
	(*pp_game_obj)->cw_destructor = cw_destructor;
	(*pp_game_obj)->cw_constructor(pp_game_obj);
	cw_game_process_linker(*pp_game_obj);
	cw_essence_init_linker(*pp_game_obj);
	cw_game_functions_linker(*pp_game_obj);
}
