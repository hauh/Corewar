/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 19:04:02 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			conversetion_int_to_bytes(unsigned char *dst, int number)
{
	int iter;
	int bias;

	iter = 0;
	while (iter < REG_SIZE)
	{
		dst[iter] = (number << (iter * 8)) >> 24;
		++iter;
	}
}

void			initialization_carriage(corewar_t *game)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->reg_buf = (unsigned char *)malloc(sizeof(unsigned char *) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	ft_memset(new_carriage->reg_buf, 0, REG_SIZE);
	new_carriage->id					= ++game->carriages_amount;
	new_carriage->player_id				= game->carriages_amount;
	new_carriage->carry_flag			= FALSE;
	new_carriage->waiting_time			= FALSE;
	new_carriage->last_live_loop		= FALSE;
	new_carriage->current_command		= NULL;
	new_carriage->current_location 		= FALSE;
	new_carriage->next_command_location	= FALSE;
	new_carriage->next 					= NULL;
	new_carriage->prev					= NULL;
	if (!game->carriages)
		game->carriages = new_carriage;
	else
	{
		game->carriages->prev = new_carriage;
		new_carriage->next = game->carriages;
		game->carriages = new_carriage;
	}
}

void			initialization_carriages(corewar_t *game)
{
	int			iter;

	iter = 0;
	while (iter < game->players_amount)
	{
		initialization_carriage(game);
		conversetion_int_to_bytes(game->carriages->reg_buf, -game->carriages->id);
		write_from_buf_to_reg(game->carriages, 1);
		ft_memset(game->carriages->reg_buf, 0, REG_SIZE);
		++iter;
	}
	game->destructor->carriages_detect = TRUE;
}