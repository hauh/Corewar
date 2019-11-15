/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_essence_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:39:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/15 15:04:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_processes_obj_init(t_corewar *p_game_instance)
{
	t_process	*p_process_obj;
	int			iter;

	iter = CW_ITERATOR;
	cw_scheduler_insertion_linker(GA_SCHEDULER_I, p_game_instance);
	cw_scheduler_functions_linker(GA_SCHEDULER_I, p_game_instance);
	if (GA_TREE_TIME_I || GA_LIST_TIME_I)
		GA_SCHEDULER_I->cw_timeline_init(GA_SCHEDULER_I, p_game_instance);
	GA_ARENA_OBJ_I->ncurses = GA_NCURSES_I;
	while (++iter < GA_SCHEDULER_I->players_amount)
	{
		cw_create_instance_process(&p_process_obj);
		p_process_obj->id = GA_SCHEDULER_I->processes_amount + 1;
		p_process_obj->pp_command_container = p_game_instance->pa_commands;
		p_process_obj->cw_set_owner(p_process_obj, GA_SCHEDULER_I);
		p_process_obj->cw_write_owner_id_to_reg(p_process_obj);
		GA_SCHEDULER_I->cw_insert_process(GA_SCHEDULER_I, p_process_obj, 1);
	}
	p_game_instance->numerate_carriage = GA_SCHEDULER_I->processes_amount;
	p_game_instance->p_arena_obj->p_winner = GA_SC_PR_I->p_owner;
}

static int		cw_keys_parse(t_corewar *p_game_instance,
								char **argv, int argc, int iter)
{
	while (*++(argv[iter]) && (SPY < 2 || SPY > 5))
		if (*(argv[iter]) == 's' && iter + 1 < argc && (SPY = CW_TRUE))
			p_game_instance->starting_cycle = ft_atoi(argv[iter + 1]);
		else if (!ft_strcmp(argv[iter], "dump") && iter + 1 < argc && (SPY = 2))
			p_game_instance->dump_cycle = ft_atoi(argv[iter + 1]);
		else if (*(argv[iter]) == 'n' && iter + 1 < argc && (SPY = CW_TRUE))
			p_game_instance->custom_id = ft_atoi(argv[iter + 1]);
		else if (*(argv[iter]) == 'v' && iter + 1 < argc && (SPY = CW_TRUE))
			p_game_instance->verbose = ft_atoi(argv[iter + 1]);
		else if (!ft_strcmp(argv[iter], "-sellout") && (SPY = 3))
			p_game_instance->sellout = CW_TRUE;
		else if (!ft_strcmp(argv[iter], "-stealth") && (SPY = 4))
			p_game_instance->stealth = CW_TRUE;
		else if (!ft_strcmp(argv[iter], "-mini") && (SPY = 5))
			p_game_instance->mini = CW_TRUE;
		else if (*(argv[iter]) == 't' && (SPY = 6))
			p_game_instance->timeline_avl_tree_mode = CW_TRUE;
		else if (*(argv[iter]) == 'l' && (SPY = 6))
			p_game_instance->timeline_list_mode = CW_TRUE;
		else if ((*(argv[iter]) == 'g' || *(argv[iter]) == 'a') && (SPY = 6))
			*(argv[iter]) == 'g' ? GA_NCURSES_I = CW_TRUE :
			(GA_AFF_I = CW_TRUE);
		else
			p_game_instance->cw_usage(p_game_instance);
	return (SPY);
}

static void		cw_players_obj_init(t_corewar *p_game_instance, int c, char **v)
{
	t_player	*p;
	t_mark		standart_id;
	t_mark		b;
	t_iter		i;

	standart_id = 0;
	b = CW_ALL_FREE;
	i = CW_BEGIN_FROM_ZERO;
	while (++i < c)
		if (*(v[i]) == CW_KEY && !(SPY = CW_FALSE))
			cw_keys_parse(p_game_instance, v, c, i) <= 2 ? ++i : 0;
		else
		{
			cw_create_instance_player(&p);
			p->cw_read_file(p, v[i]);
			p->cw_self_build(p);
			p->cw_self_validate(p);
			GA_ID_I ? p->cw_set_id(p, &b, GA_ID_I, CW_TRUE) : CW_FALSE;
			GA_SCHEDULER_I->cw_insert_player(GA_SCHEDULER_I, p);
			GA_ID_I = 0;
		}
	GA_SCHEDULER_I->players_amount < 1 || GA_SCHEDULER_I->players_amount > 4 ?
	cw_error_catcher(GA_OBJ_NAME, GA_KEY_ERROR, __FILE__, __LINE__) : (i = -1);
	while (++i < GA_SC_PL_AM_I && (GA_SC_PL_I = GA_SC_PL_I->p_prev))
		!GA_SC_PL_I->id ? GA_SC_PL_I->cw_set_id(GA_SC_PL_I, &b, 1, 0) : 0;
}

static void		cw_arena_scheduler_command_obj_init(t_corewar *p_game_instance)
{
	t_scheduler	*p_scheduler_obj;
	t_command	*p_command_obj;
	t_arena		*p_arena_obj;
	t_iter		iter;

	iter = CW_BEGIN_FROM_ZERO;
	cw_create_instance_arena(&p_arena_obj);
	p_arena_obj->cw_buffer_init(p_arena_obj);
	p_game_instance->p_arena_obj = p_arena_obj;
	cw_create_instance_scheduler(&p_scheduler_obj);
	p_scheduler_obj->p_cycle_to_die = &p_arena_obj->cycle_to_die;
	p_game_instance->p_scheduler = p_scheduler_obj;
	while (++iter < CW_COMMAND_AMOUNT)
	{
		cw_create_instance_command(&p_command_obj);
		p_command_obj->cw_recognize(p_command_obj, iter);
		p_game_instance->pa_commands[iter] = p_command_obj;
	}
}

extern void		cw_essence_init_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_arena_scheduler_command_obj_init =
		cw_arena_scheduler_command_obj_init;
	p_game_instance->cw_processes_obj_init = cw_processes_obj_init;
	p_game_instance->cw_players_obj_init = cw_players_obj_init;
}
