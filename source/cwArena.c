/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwArena.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 17:17:19 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Arena initialization is here. At the beginning we are create the game arena
** that includes field, temporary buffers and so on. Rules of game here too.
** Thera are also function to arrange all units to field.
*/

void			cwIntroducePlayers(corewar_t *game)
{
	int			iter;

	iter = CW_BEGIN_FROM_ZERO;
	printf("Introducing contestants...\n");
	while (iter < game->players_amount)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		game->players->id,
		game->players->code_size,
		game->players->name,
		game->players->comment);
		game->players = game->players->next;
		++iter;
	}
}

void			cwPrintArena(corewar_t *game)
{
	int			border;
	int			i;

	border	= sqrt(MEM_SIZE);
	i		= CW_BEGIN_FROM_ZERO;
	printf("%4d: ", 0);
	while (i < MEM_SIZE)
	{
		printf("%.2x ", game->arena->field[i]);
		if ((i + 1) % border == 0)
			printf("\n%4d: ", i + 1);
		++i;
	}
	printf("\n");
}

void			cwArrangeUnits(corewar_t *game)
{
	int			iter;
	int			player_location;
	int			memory_step;
	int			code_iter;

	memory_step = MEM_SIZE / game->players_amount;
	iter = CW_BEGIN_FROM_ZERO;
	while (iter < game->players_amount)
	{
		code_iter = CW_BEGIN_FROM_ZERO;
		player_location = memory_step * iter;
		game->carriages->current_location = player_location;
		while (player_location < memory_step * iter + CHAMP_MAX_SIZE)
			game->arena->field[player_location++] = game->players->code[code_iter++];
		game->players = game->players->next;
		game->carriages = game->carriages->next;
		++iter;
	}
}

void			cwInitializationArena(corewar_t *game)
{
	arena_t		*new_arena;
	int			buf_iter;

	buf_iter = CW_BEGIN_FROM_ZERO;
	if (!(new_arena = (arena_t *)malloc(sizeof(arena_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	if (!(new_arena->field = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
	while (buf_iter < CW_BUFFER_AMOUNT)
	{
		if (!(new_arena->buffer_set[buf_iter] = (buffer_t *)malloc(sizeof(buffer_t))))
			cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
		if (!(new_arena->buffer_set[buf_iter]->data = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE)))
			cwErrorCatcher(CW_NOT_ALLOCATED, CW_ARENA);
		++buf_iter;
	}
	ft_memset(new_arena->field, 0, MEM_SIZE);
	new_arena->last_survivor		= game->players;
	new_arena->last_carriage		= game->carriages;
	new_arena->cycle_amount 		= 0;
	new_arena->live_amount			= 0;
	new_arena->check_amount			= 0;
	new_arena->cycle_to_die			= CYCLE_TO_DIE;
	game->destructor->arena_detect	= TRUE;
	game->arena						= new_arena;
	cwArrangeUnits					(game);
}