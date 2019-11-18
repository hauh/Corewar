/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/16 17:30:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_print(t_corewar *p_game_instance,
						t_process *p_process_obj, int mode)
{
	t_iter		pl_lo;
	t_iter		i;

	if (mode == GA_WRITING_MODE)
	{
		if (p_process_obj && (i = CW_ITERATOR))
		{
			cw_print(p_game_instance, p_process_obj->p_left, GA_WRITING_MODE);
			pl_lo = MEM_SIZE / GA_SC_PL_AM_I * (p_process_obj->p_owner->id - 1);
			PR_CURRENT_LOCATION_O = pl_lo;
			while (pl_lo < MEM_SIZE / GA_SC_PL_AM_I *
				(p_process_obj->p_owner->id - 1) + CHAMP_MAX_SIZE)
				p_game_instance->AR_FIELD_O[pl_lo++] = PR_OWNER_O->p_code[++i];
			cw_print(p_game_instance, p_process_obj->p_right, GA_WRITING_MODE);
		}
	}
	else if (mode == GA_INTRO_MODE)
		if (p_process_obj)
		{
			cw_print(p_game_instance, p_process_obj->p_left, GA_INTRO_MODE);
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			PR_OWNER_O->id, PR_OWNER_O->code_size, PR_OWNER_O->p_name,
			PR_OWNER_O->p_comment);
			cw_print(p_game_instance, p_process_obj->p_right, GA_INTRO_MODE);
		}
}

static void		cw_write_code_to_memory(t_corewar *p_game_instance)
{
	t_process	*tmp;
	t_iterator	pl_lo;
	t_iterator	iter;
	t_iterator	i;

	if (p_game_instance->timeline_avl_tree_mode)
		cw_print(p_game_instance,
		p_game_instance->p_scheduler->pa_timeline[1]->p_root, GA_WRITING_MODE);
	else if ((iter = CW_ITERATOR))
	{
		if (p_game_instance->timeline_list_mode)
			tmp = p_game_instance->p_scheduler->pa_timeline[1]->p_head;
		else
			tmp = p_game_instance->p_scheduler->p_processes_list;
		while (++iter < p_game_instance->p_scheduler->processes_amount)
		{
			pl_lo = MEM_SIZE / GA_SC_PL_AM_I * (tmp->p_owner->id - 1);
			i = CW_ITERATOR;
			tmp->current_location = pl_lo;
			while (pl_lo < MEM_SIZE / GA_SC_PL_AM_I *
			(tmp->p_owner->id - 1) + CHAMP_MAX_SIZE)
				GA_ARENA_OBJ_I->p_field[pl_lo++] = tmp->p_owner->p_code[++i];
			tmp = tmp->p_next;
		}
	}
}

static void		cw_congratulations(t_corewar *p_game_instance)
{
	if (GA_NCURSES_I)
	{
		cr_vis_winner(p_game_instance);
		cr_vis_main(p_game_instance, V_CLEANUP);
		exit(0);
	}
	else
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
		p_game_instance->p_arena_obj->p_winner->id,
		p_game_instance->p_arena_obj->p_winner->p_name);
	}
}

static void		cw_introduce_players(t_corewar *p_game_instance)
{
	t_process	*tmp;
	t_iterator	iter;

	iter = CW_ITERATOR;
	ft_printf("Introducing contestants...\n");
	if (p_game_instance->timeline_avl_tree_mode)
		cw_print(p_game_instance,
		p_game_instance->p_scheduler->pa_timeline[1]->p_root, GA_INTRO_MODE);
	else
	{
		if (p_game_instance->timeline_list_mode)
			tmp = p_game_instance->p_scheduler->pa_timeline[1]->p_head;
		else
			tmp = p_game_instance->p_scheduler->p_processes_list;
		while (++iter < p_game_instance->p_scheduler->processes_amount)
		{
			tmp = tmp->p_prev;
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			tmp->p_owner->id, tmp->p_owner->code_size, tmp->p_owner->p_name,
			tmp->p_owner->p_comment);
		}
	}
}

extern void		cw_game_functions_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_write_code_to_memory = cw_write_code_to_memory;
	p_game_instance->cw_introduce_players = cw_introduce_players;
	p_game_instance->cw_congratulations = cw_congratulations;
}
