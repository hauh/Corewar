/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:17:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/15 16:42:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

int		init_arena(corewar_t *game)
{
	unsigned char	*arena;
	int				fill_carry;
	int				code_carry;
	int				memory_step;
	int				iter;
	int				test;

	iter = 0;
	fill_carry = 0;
	code_carry = 0;
	memory_step = MEM_SIZE / game->amount_players;
	arena = (unsigned char *)malloc(sizeof(unsigned char *) * MEM_SIZE);
	memset(arena, 0, MEM_SIZE);
	while (iter < game->amount_players)
	{
		fill_carry = memory_step * iter;
		code_carry = 0;
		while (fill_carry < memory_step * iter + MAX_EXECUTION_CODE_LENGTH)
			arena[fill_carry++] = game->champions[iter]->execution_code[code_carry++];
		++iter;
	}
	test = sqrt(MEM_SIZE);
	fill_carry = 0;
	while (fill_carry < MEM_SIZE)
	{
		printf("%.2x", arena[fill_carry]);
		if (fill_carry % test == 0)
			printf("\n");
		++fill_carry;
	}
}