/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/19 00:31:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_usage(t_corewar *p_game_instance)
{
	ft_printf(
	"Usage: ./corewar [-dump N -s N -v N | -g --stealth --sellout --mini]"
		"[-a | -t] <champion1.cor> <...>\n"
	"\t-a\t: Prints output from \"aff\" (Default is to hide it)\n"
	"\t-t\t: TIMELINE AVL TREE execution model (faster with MANY carriages)\n"
	"##### TEXT OUTPUT MODE ##################"
		"#######################################\n"
	"\t-dump N : Dumps memory after N cycles then exits\n"
	"\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n"
	"\t-v N\t: Verbosity levels, can be added together to enable several\n"
	"\t\t- 1 : Show lives\n"
	"\t\t- 2 : Show cycles\n"
	"\t\t- 4 : Show deaths\n"
	"##### NCURSES OUTPUT MODE ###############"
		"#######################################\n"
	"\t-g\t\t: Ncurses output mode\n"
	"\t--stealth\t: Hides the real contents of the memory\n"
	"\t--sellout\t: Add some fun ad to game process XD\n"
	"\t--mini\t\t: Enable mini version for smaller screens\n"
	"########################################"
		"########################################\n");
	p_game_instance = NULL;
	exit(1);
}

static void	cw_start_execution(t_corewar *p_game_instance)
{
	char i;

	while (GA_SC_PR_AM_I && ++p_game_instance->AR_CYCLE_O)
	{
		GA_SCHEDULER_I->cw_execution_processes(GA_SCHEDULER_I,
			p_game_instance, p_game_instance->AR_CYCLE_O);
		if (GA_ARENA_OBJ_I->cw_time_to_check(GA_ARENA_OBJ_I, GA_LAST_CHECK_I))
			GA_SCHEDULER_I->cw_deadline(GA_SCHEDULER_I, p_game_instance);
		if (GA_DUMP_I == p_game_instance->AR_CYCLE_O && GA_SC_PR_AM_I)
			GA_ARENA_OBJ_I->cw_print_field(GA_ARENA_OBJ_I, CW_TRUE);
		if (GA_VERBOSE_I == GA_SHOW_CYCLES)
			ft_printf("It is now cycle %d\n", GA_ARENA_OBJ_I->cycle);
		if (GA_STARTING_I && p_game_instance->AR_CYCLE_O >= GA_STARTING_I)
		{
			GA_ARENA_OBJ_I->cw_print_field(GA_ARENA_OBJ_I, CW_FALSE);
			i = 0;
			while (i != '\n')
				read(0, &i, 1);
		}
	}
}

static void	cw_graphic_execution(t_corewar *p_game_instance)
{
	cr_vis_main(p_game_instance, V_INIT);
	while (GA_SC_PR_AM_I)
	{
		if (GA_SC_PR_AM_I)
			cr_vis_main(p_game_instance, V_CONTROL);
		if (p_game_instance->vis->exit)
			return ;
		else if ((p_game_instance->vis->step || p_game_instance->vis->flow) &&
				p_game_instance->vis->tick)
		{
			p_game_instance->AR_CYCLE_O += 1;
			GA_SCHEDULER_I->cw_execution_processes(GA_SCHEDULER_I,
				p_game_instance, p_game_instance->AR_CYCLE_O);
			if (GA_ARENA_OBJ_I->cw_time_to_check(GA_ARENA_OBJ_I,
				GA_LAST_CHECK_I))
				GA_SCHEDULER_I->cw_deadline(GA_SCHEDULER_I, p_game_instance);
			if (GA_SC_PR_AM_I)
				cr_vis_main(p_game_instance, V_UPDATE);
		}
	}
	while (!p_game_instance->vis->exit)
		cr_vis_main(p_game_instance, V_CONTROL);
}

extern void	cw_game_process_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_usage = cw_usage;
	p_game_instance->cw_start_execution = cw_start_execution;
	p_game_instance->cw_graphic_execution = cw_graphic_execution;
}
