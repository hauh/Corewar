/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:59:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 14:49:28 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			validate_player(player_t *player)
{
	int			check_size;

	check_size = CHAMP_MAX_SIZE - 1;
	if (player->binary_label != COREWAR_EXEC_MAGIC)
	{
		printf("The champion %s is not binary file!", player->name);
		exit(-1);
	}
	if (player->code_size > CHAMP_MAX_SIZE)
	{
		printf("The champion %s has not valid size of code\n", player->name);
		exit(-1);
	}
	while (!player->code[check_size])
		--check_size;
	if (player->code_size != check_size + 1)
	{
		printf("Real code_size is not corresponding declaread code_size, cheater!!! Go away!\n");
		exit(-1);
	}
}

player_t		*player_init(int player_id)
{
	player_t	*new_player;

	if (!(new_player				= (player_t *)malloc(sizeof(player_t))))
		exit(-1);
	if (!(new_player->player_source	= (unsigned char *)malloc(sizeof(unsigned char) * CODE)))
		exit(-1);
	memset(new_player->player_source, 0, CODE);
	if (!(new_player->code			= (unsigned char *)malloc(sizeof(unsigned char) * CHAMP_MAX_SIZE)))
		exit(-1);
	memset(new_player->code, 0, CHAMP_MAX_SIZE);
	if (!(new_player->comment		= (unsigned char *)malloc(sizeof(unsigned char) * COMMENT_LENGTH)))
		exit(-1);
	memset(new_player->comment, 0, COMMENT_LENGTH);
	if (!(new_player->name			= (unsigned char *)malloc(sizeof(unsigned char) * PROG_NAME_LENGTH)))
		exit(-1);
	memset(new_player->name, 0, PROG_NAME_LENGTH);
	new_player->id					= player_id;
	new_player->code_size			= 0;
	new_player->carriage_id			= 0;
	new_player->binary_label		= 0;
	new_player->reading_carriage	= 0;
	return (new_player);
}

void		build_player(player_t *player)
{
	int		iter;

	iter						= 0;
	while (player->reading_carriage < BINARY_LABEL)
		player->binary_label	|= player->player_source[player->reading_carriage++] << ((sizeof(int) - player->reading_carriage) * 8);
	while (player->reading_carriage < NAME)
		player->name[iter++]	= player->player_source[player->reading_carriage++];
	player->name[iter]			= 0;
	player->reading_carriage	+= NULL_SEPARATOR;
	iter						= 0;
	while (player->reading_carriage < CODE_SIZE)
		player->code_size		|= ((int)player->player_source[player->reading_carriage++] << ((sizeof(int) - ++iter) * 8));
	iter						= 0;
	while (player->reading_carriage < COMMENT)
		player->comment[iter++]	= player->player_source[player->reading_carriage++];
	player->comment[iter]		= 0;
	player->reading_carriage	+= NULL_SEPARATOR;
	iter						= 0;
	while (player->reading_carriage < CODE)
		player->code[iter++]	= player->player_source[player->reading_carriage++];
}

void		players_init(corewar_t *game, char **argv)
{
	int		iter;
	int		fd;

	iter = 0;
	while (iter < game->players_amount)
	{
		if ((fd = open(argv[game->players_indicies[iter]], O_RDONLY)) < 0)
			exit(fd);
		game->players[iter]	= player_init(iter + 1);
		if (read(fd, game->players[iter]->player_source, CODE) < 0)
			exit(-1);
		build_player(game->players[iter]);
		validate_player(game->players[iter]);
		close(fd);
		++iter;
	}
	game->memory_status.players_detect = TRUE;
}