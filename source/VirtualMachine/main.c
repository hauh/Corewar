/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/19 12:56:22 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			args_init(corewar_t *game, char **argv, int argc)
{
	args_t		*new_args;
	int			iter;

	if (argc < 1)
		exit(-1);
	if (!(new_args						= (args_t *)malloc(sizeof(args_t))))
		exit(-1);
	game->memory_status.args_detect		= TRUE;
	iter								= 0;
	while (argc)
	{
		if (argv[argc][0] == '-')
		{
			if (argv[argc][1] == 'n' && argv[argc][2] == 0)
				new_args->custom_id			= TRUE;
			else if (argv[argc][1] == 'c' && argv[argc][2] == 0)
				new_args->concurance_cpu	= TRUE;
			else if (argv[argc][1] == 'g' && argv[argc][2] == 0)
				new_args->concurance_gpu	= TRUE;
			else if (argv[argc][1] == 'v' && argv[argc][2] == 0)
				new_args->visualizator		= TRUE;
			else
			{
				printf("Not valid flag\n");
				//clean_up(game);
				exit(-1);
			}
		}
		else
		{
			game->players_indicies[iter] = argc;
			++game->players_amount;
			++iter;
		}
		--argc;
	}
	game->args = new_args;
}

void			game_init(corewar_t **game, char **argv, int argc)
{
	corewar_t	*new_game;

	if (!(new_game						= (corewar_t *)malloc(sizeof(corewar_t))))
		exit(-1);
	if (!(new_game->players_indicies	= (int *)malloc(sizeof(int) * argc)))
		exit(-1);
	new_game->memory_status.indicies_detect = TRUE;
	ft_memset((void *)&new_game->memory_status, 0, sizeof(new_game->memory_status));
	new_game->players_amount	= 0;
	new_game->carriages			= NULL;
	*game						= new_game;
}

int				main(int argc, char **argv)
{
	corewar_t	*game;

	game_init(&game, argv, argc - 1);
	args_init(game, argv, argc - 1);
	players_init(game, argv);
	carriages_init(game);
	arena_init(game);
	arrange_units(game);
	introduce_players(game);
	here_we_go(game);
	return (0);
}