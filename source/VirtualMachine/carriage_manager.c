/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/19 20:33:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			conversetion_int_to_bytes(unsigned char *dst, int number)
{
	int iter;
	int bias;

	iter = 0;
	bias = 3;
	while (iter < REG_SIZE)
	{
		dst[iter] = number & (0xff << bias);
		++iter;
		--bias;
	}
}

void			carriage_init(corewar_t *game)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		exit(-1);
	game->memory_status.carriage_list_detect = TRUE;
	new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	if (!game->carriages)
	{
		game->carriages = new_carriage;
		game->carriages->next = NULL;
		game->carriages->prev = NULL;
		return ;
	}
	game->carriages->prev = new_carriage;
	new_carriage->next = game->carriages;
	game->carriages = new_carriage;
}

void			carriages_init(corewar_t *game)
{
	int			iter;

	iter = 0;
	while (iter < game->players_amount)
	{
		carriage_init(game);
		game->carriages->id = game->players[iter]->id * CARRIAGE_ID_STEP;
		game->carriages->player_id = game->players[iter]->id;
		game->carriages->carry_flag = 0;
		game->carriages->step_bytes = 0;
		game->carriages->waiting_time = 0;
		game->carriages->last_live_loop = 0;
		game->carriages->current_command = 0;
		game->carriages->current_location = 0;
		ft_memset(game->carriages->reg_buf, 0, REG_SIZE);
		conversetion_int_to_bytes(game->carriages->reg_buf, game->players[iter]->id);
		++iter;
	}
}