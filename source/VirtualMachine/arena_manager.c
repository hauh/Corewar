/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 18:40:37 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void		print_arena(corewar_t *game)
{
	int		border;
	int		i;

	border	= sqrt(MEM_SIZE);
	i		= 0;
	while (i < MEM_SIZE)
	{
		printf("%.2x | ", game->arena->field[i]);
		if ((i + 1) % border == 0 && i > 10)
			printf("\n");
		++i;
	}
}

int				arrange_units(corewar_t *game)
{
	int			arena_carriage;
	int			memory_step;
	int			iter;

	iter = 0;
	memory_step = MEM_SIZE / game->players_amount;
	while (iter < game->players_amount)
	{
		arena_carriage = memory_step * iter;
		game->players[iter]->reading_carriage = 0;
		game->carriages->current_location = arena_carriage;
		while (arena_carriage < memory_step * iter + CHAMP_MAX_SIZE)
			game->arena->field[arena_carriage++] = game->players[iter]->code[game->players[iter]->reading_carriage++];
		++iter;
	}
	return (0);
}

void			initialization_arena(corewar_t *game)
{
	arena_t		*new_arena;

	if (!(new_arena = (arena_t *)malloc(sizeof(arena_t))))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->field = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	game->memory_status.arena_detect = TRUE;
	ft_memset(new_arena->field, 0, MEM_SIZE);
	new_arena->last_survivor	= game->players[game->players_amount - 1];
	new_arena->loop_amount 		= 0;
	new_arena->live_amount		= 0;
	new_arena->check_amount		= 0;
	new_arena->cycle_to_die		= CYCLE_TO_DIE;
	game->arena					= new_arena;
}