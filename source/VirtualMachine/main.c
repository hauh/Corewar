/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/21 17:30:53 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			initialization_keys(corewar_t *game, char **argv, int argc)
{
	key_t		*new_keys;
	int			iter;

	if (!(new_keys = (key_t *)malloc(sizeof(key_t))))
		error_catcher(MEMORY_ALLOC_ERROR, KEYS);
	iter = 1;
	while (iter < argc)
	{
		if (argv[iter][0] == '-')
		{
			if (argv[iter][1] == 'n' && argv[iter][2] == 0)
				new_keys->custom_id			= TRUE;
			else if (argv[iter][1] == 'c' && argv[iter][2] == 0)
				new_keys->concurance_cpu	= TRUE;
			else if (argv[iter][1] == 'g' && argv[iter][2] == 0)
				new_keys->concurance_gpu	= TRUE;
			else if (argv[iter][1] == 'v' && argv[iter][2] == 0)
				new_keys->visualizator		= TRUE;
			else
				error_catcher(NOT_VALID_ARG, KEYS);
			argv[iter][0] = '*';
		}
		++iter;
	}
	game->destructor->keys_detect = TRUE;
	game->keys = new_keys;
}

void			put_option(size_t *option, size_t waiting_time, size_t dir_size, size_t id, size_t first_arg, size_t second_arg, size_t third_arg, size_t change_carry, size_t availability_types)
{
	*option |= PUT_WAITING_TIME(waiting_time);
	*option |= PUT_DIR_SIZE(dir_size);
	*option |= PUT_ID(id);
	*option |= PUT_FIRST_ARG(first_arg);
	*option |= PUT_SECOND_ARG(second_arg);
	*option |= PUT_THIRD_ARG(third_arg);
	*option |= PUT_CHANGE_CARRY(change_carry);
	*option |= PUT_AVAI_TYPES(availability_types);
}

void			initialization_command(command_t *command, size_t option, void *function)
{
	command->id					= GET_ID(option);
	command->first_arg			= GET_FIRST_ARG(option);
	command->second_arg			= GET_SECOND_ARG(option);
	command->third_arg			= GET_THIRD_ARG(option);
	command->dir_size			= GET_DIR_SIZE(option);
	command->change_carry		= GET_CHANGE_CARRY(option);
	command->waiting_time		= GET_WAITING_TIME(option);
	command->availability_types	= GET_AVAI_TYPES(option);
	command->function			= (void (*)(corewar_t *))function;
}

void			initialization_commands(corewar_t *game)
{
	command_t	*new_command;
	size_t		option;
	int			iter;

	iter = 1;
	while (iter <= COMMAND_AMOUNT)
	{
		if (!(new_command = (command_t *)malloc(sizeof(command_t))))
			error_catcher(MEMORY_ALLOC_ERROR, COMMAND);
		game->commands[iter] = new_command;
		option = 0;
		if (iter == LIVE)
		{
			put_option(&option, 10, DIRECTION_SIZE, LIVE, TRUE, FALSE, FALSE, FALSE, FALSE);
			initialization_command(new_command, option, &live_exec);
		}
		else if (iter == LD)
		{
			put_option(&option, 5, DIRECTION_SIZE, LD, TRUE, TRUE, FALSE, TRUE, TRUE);
			initialization_command(new_command, option, &ld_exec);
		}
		else if (iter == ST)
		{
			put_option(&option, 5, DIRECTION_SIZE, ST, TRUE, TRUE, FALSE, FALSE, TRUE);
			initialization_command(new_command, option, &st_exec);
		}
		else if (iter == ADD)
		{
			put_option(&option, 10, DIRECTION_SIZE, ADD, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &add_exec);
		}
		else if (iter == SUB)
		{
			put_option(&option, 10, DIRECTION_SIZE, SUB, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &sub_exec);
		}
		else if (iter == AND)
		{
			put_option(&option, 6, DIRECTION_SIZE, AND, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &and_exec);
		}
		else if (iter == OR)
		{
			put_option(&option, 6, DIRECTION_SIZE, OR, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &or_exec);
		}
		else if (iter == XOR)
		{
			put_option(&option, 6, DIRECTION_SIZE, XOR, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &xor_exec);
		}
		else if (iter == ZJMP)
		{
			put_option(&option, 20, SHORT_DIR_SIZE, ZJMP, TRUE, FALSE, FALSE, FALSE, FALSE);
			initialization_command(new_command, option, &zjmp_exec);
		}
		else if (iter == LDI)
		{
			put_option(&option, 25, SHORT_DIR_SIZE, LDI, TRUE, TRUE, TRUE, FALSE, TRUE);
			initialization_command(new_command, option, &ldi_exec);
		}
		else if (iter == STI)
		{
			put_option(&option, 25, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, FALSE, TRUE);
			initialization_command(new_command, option, &sti_exec);
		}
		else if (iter == FORK)
		{
			put_option(&option, 800, SHORT_DIR_SIZE, FORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			initialization_command(new_command, option, &fork_exec);
		}
		else if (iter == LLD)
		{
			put_option(&option, 10, DIRECTION_SIZE, LLD, TRUE, TRUE, FALSE, TRUE, TRUE);
			initialization_command(new_command, option, &lld_exec);
		}
		else if (iter == LLDI)
		{
			put_option(&option, 50, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, TRUE, TRUE);
			initialization_command(new_command, option, &lldi_exec);
		}
		else if (iter == LFORK)
		{
			put_option(&option, 1000, SHORT_DIR_SIZE, LFORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			initialization_command(new_command, option, &lfork_exec);
		}
		else if (iter == AFF)
		{
			put_option(&option, 2, DIRECTION_SIZE, AFF, TRUE, FALSE, FALSE, FALSE, TRUE);
			initialization_command(new_command, option, &aff_exec);
		}
		++iter;
	}
}

void			initialization_game(corewar_t **game)
{
	corewar_t	*new_game;

	if (!(new_game = (corewar_t *)malloc(sizeof(corewar_t))))
		error_catcher(MEMORY_ALLOC_ERROR, GAME);
	new_game->players_amount	= 0;
	new_game->carriages_amount	= 0;
	new_game->commands_amount	= 0;
	new_game->keys				= NULL;
	new_game->players			= NULL;
	new_game->arena				= NULL;
	new_game->carriages			= NULL;
	new_game->destructor		= NULL;
	*game = new_game;
}

void			initialization_destructor(corewar_t *game)
{
	destructor_t	*new_destructor;

	if (!(new_destructor = (destructor_t *)malloc(sizeof(destructor_t))))
		error_catcher(MEMORY_ALLOC_ERROR, DESTRUCTOR);
	new_destructor->self_detect			= TRUE;
	new_destructor->game_detect			= TRUE;
	new_destructor->keys_detect			= FALSE;
	new_destructor->arena_detect		= FALSE;
	new_destructor->players_detect		= FALSE;
	new_destructor->commands_detect 	= FALSE;
	new_destructor->carriages_detect	= FALSE;
	game->destructor					= new_destructor;
}

int				main(int argc, char **argv)
{
	corewar_t	*game;

	argc < 2 ? error_catcher(ARGS_AMOUN_ERROR, INIT) : FALSE;
	initialization_game			(&game);
	initialization_destructor	(game);
	initialization_keys			(game, argv, argc);
	initialization_players		(game, argv, argc);
	initialization_carriages	(game);
	initialization_arena		(game);
	initialization_commands		(game);
	print_arena(game);
	introduce_players(game);
	//here_we_go(game);
	return (0);
}