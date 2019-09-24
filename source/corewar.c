/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 21:45:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void			initialization_game(corewar_t **game)
{
	corewar_t	*new_game;

	if (!(new_game = (corewar_t *)malloc(sizeof(corewar_t))))
		error_catcher(MEMORY_ALLOC_ERROR, GAME);
	new_game->players_amount			= 0;
	new_game->carriages_amount			= 0;
	new_game->commands_amount			= 0;
	new_game->keys						= NULL;
	new_game->players					= NULL;
	new_game->arena						= NULL;
	new_game->carriages					= NULL;
	new_game->destructor				= NULL;
	*game								= new_game;
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
	//ft_memset(game->arena->field, 0, MEM_SIZE);
	//game->carriages->current_location	= 0;
	//game->arena->field[0] 				= 6;
	//game->arena->field[1] 				= 212;
	//game->arena->field[2] 				= 0;
	//game->arena->field[3] 				= 100;
	//game->arena->field[4] 				= 11;
	//game->arena->field[5] 				= 15;
	//game->arena->field[6] 				= 11;
	//game->arena->field[7] 				= 15;
	//game->arena->field[8] 				= 0;
	//game->arena->field[9] 				= 80;
	//game->arena->field[100]				= 0;
	//game->arena->field[101]				= 0;
	//game->arena->field[102]				= 3;
	//game->arena->field[103]				= 32;
	//int test;
	//int one;
	//int two;
	//one = 800;
	//two = 777;
	//REQUEST_REGISTER = 15;
	//cwConversionIntToBytes(game->arena->value_buf1, &one, 0);
	//cwWriteFromBufToReg(game->arena->value_buf1, game->carriages->registers, 7, 0);
	//cwConversionIntToBytes(game->arena->value_buf1, &two, 0);
	//cwWriteFromBufToReg(game->arena->value_buf1, game->carriages->registers, 11, 0);
	//game->carriages->current_command	= game->commands[6];
	//game->carriages->current_command->function(game);
	//game->carriages->current_location = (game->carriages->current_location + game->carriages->jump) % MEM_SIZE;
	//cwReadFromRegToBuf(game->arena->value_buf1, game->carriages->registers, 15, 0);
	//cwConversionBytesToInt(game->arena->value_buf1, &test, 0);
	//printf("%d\n", one & two);
	//printf(">>>%d\n", test);
	//printf("%d\n", game->carriages->current_location);
	//printf("%d\n", game->carriages->carry);
	//game->carriages->current_command   	= game->commands[3];
	////game->carriages->current_command->function(game);
	////print_arena(game);
	//exit(1);
	//cwTypeHandler(game);
	//printf("%d %d %d\n", game->carriages->current_command->first_arg, game->carriages->current_command->second_arg, game->carriages->current_command->third_arg);
	//printf("%d\n", game->carriages->current_location);
	//cwArgsHandler(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	//exit(1);
//
	////cwArgsHandler(game, game->arena->value_buf1, CW_WRITING_MODE, TRUE, SECOND_ARG);
//	//cr_vis_main					(game, V_INIT);
	introduce_players			(game);
	here_we_go					(game);
	return (0);
}