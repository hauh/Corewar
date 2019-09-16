/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/16 21:38:21 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void	build_player(player_t *player)
{
	int iter;

	iter = 0;
	while (player->reading_carriage < BINARY_LABEL)
		player->binary_label |= player->player_source[player->reading_carriage++] << ((sizeof(int) - player->reading_carriage) * 8);
	while (player->reading_carriage < NAME)
		player->name[iter++] = player->player_source[player->reading_carriage++];
	player->name[iter] = 0;
	player->reading_carriage += NULL_SEPARATOR;
	iter = 0;
	while (player->reading_carriage < CODE_SIZE)
		player->code_size |= ((int)player->player_source[player->reading_carriage++] << ((sizeof(int) - ++iter) * 8));
	iter = 0;
	while (player->reading_carriage < COMMENT)
		player->comment[iter++] = player->player_source[player->reading_carriage++];
	player->comment[iter] = 0;
	player->reading_carriage += NULL_SEPARATOR;
	iter = 0;
	while (player->reading_carriage < CODE)
		player->code[iter++] = player->player_source[player->reading_carriage++];
}

void	print_arena(corewar_t *game)
{
	int border;
	int i;

	border = sqrt(MEM_SIZE);
	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%.2x | ", game->arena[i]);
		if ((i + 1) % border == 0 && i > 10)
			printf("\n");
		++i;
	}
}

carriage_t		*init_carriage(int owner, int id)
{
	carriage_t	*new_carriage;

	new_carriage = (carriage_t *)malloc(sizeof(carriage_t));
	new_carriage->registers = (int *)malloc(sizeof(int) * REG_SIZE * REG_NUMBER);
	memset(new_carriage->registers, 0, REG_SIZE * REG_NUMBER);
	new_carriage->registers[0] = (unsigned char)owner;
	new_carriage->register_size = REG_SIZE;
	new_carriage->current_location = 0;
	new_carriage->current_command = 0;
	new_carriage->waiting_time = 0;
	//new_carriage->owner = owner;
	new_carriage->id = id;
	return (new_carriage);
}

//void				arrange_players(corewar_t *game)
//{
//
//}

void				validate_player(player_t *player)
{
	if (player->binary_label != COREWAR_EXEC_MAGIC)
	{
		printf("The champion number %d is not binary file!", player->id);
		exit(-1);
	}
}

int					arrange_players(corewar_t *game)
{
	int				arena_carriage;
	int				memory_step;
	int				iter;

	iter = 0;
	memory_step = MEM_SIZE / game->players_amount;
	while (iter < game->players_amount)
	{
		arena_carriage = memory_step * iter;
		game->players[iter]->reading_carriage = 0;
		while (arena_carriage < memory_step * iter + CHAMP_MAX_SIZE)
			game->arena[arena_carriage++] = game->players[iter]->code[game->players[iter]->reading_carriage++];
		++iter;
	}
	print_arena(game);
	return (0);
}

void				check_arguments(int argc, char **argv)
{
	if (argc > MAX_PLAYERS)
		exit(-1);
}

player_t		*player_init(int player_id)
{
	player_t	*new_player;

	if (!(new_player				= (player_t *)malloc(sizeof(player_t))))
		exit(-1);
	if (!(new_player->player_source	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		exit(-1);
	if (!(new_player->code			= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		exit(-1);
	if (!(new_player->comment		= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		exit(-1);
	if (!(new_player->name			= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		exit(-1);
	new_player->id					= player_id;
	new_player->code_size			= 0;
	new_player->carriage_id			= 0;
	new_player->binary_label		= 0;
	new_player->reading_carriage	= 0;
	return (new_player);
}

corewar_t		*game_init(int player_amount, char **argv)
{
	corewar_t	*new_game;
	int			iter;
	int			fd;

	iter = 0;
	if (!(new_game = (corewar_t *)malloc(sizeof(corewar_t))))
		return (NULL);
	new_game->players_amount = 0;
	while (iter < player_amount)
	{
		if ((fd = open(argv[iter + 1], O_RDONLY)) < 0)
			exit(fd);
		new_game->players[iter]	= player_init(iter + 1);
		if (read(fd, new_game->players[iter]->player_source, CODE) < 0)
			exit(-1);
		build_player(new_game->players[iter]);
		validate_player(new_game->players[iter]);
		printf("Label: %d\n", new_game->players[iter]->binary_label);
		printf("Name: %s\n", new_game->players[iter]->name);
		printf("Size_code: %d\n", new_game->players[iter]->code_size);
		printf("Comment: %s\n\n", new_game->players[iter]->comment);
		close(fd);
		++new_game->players_amount;
		++iter;
	}
	if (!(new_game->arena = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		exit(-1);
	memset(new_game->arena, 0, MEM_SIZE);
	return (new_game);
}

int		main(int argc, char **argv)
{
	corewar_t		*game;

	check_arguments(argc - 1, argv);
	game = game_init(argc - 1, argv);
	arrange_players(game);
	//arrange_carriage(game);
	return (0);
}