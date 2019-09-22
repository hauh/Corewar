/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/22 19:30:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			initialization_carriage(corewar_t *game)
{
	carriage_t	*new_carriage;
	carriage_t	*iter;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->value_buf = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->address_buf = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	ft_memset(new_carriage->registers, 0, REG_NUMBER * REG_SIZE);
	ft_memset(new_carriage->value_buf, 0, REG_SIZE);
	ft_memset(new_carriage->address_buf, 0, REG_SIZE);
	new_carriage->id					= ++game->carriages_amount;
	new_carriage->player_id				= game->carriages_amount;
	new_carriage->carry_flag			= FALSE;
	new_carriage->waiting_time			= FALSE;
	new_carriage->last_live_loop		= FALSE;
	new_carriage->current_command		= NULL;
	new_carriage->current_location 		= FALSE;
	new_carriage->next_command_location	= FALSE;
	if (!game->carriages)
	{
		game->carriages = new_carriage;
		game->carriages->next = game->carriages;
		game->carriages->prev = game->carriages;
	}
	else
	{
		new_carriage->prev = game->carriages->prev;
		new_carriage->next = game->carriages;
		game->carriages->prev->next = new_carriage;
		game->carriages->prev =	new_carriage;
	}
}

void			initialization_carriages(corewar_t *game)
{
	int			iter;

	iter = 0;
	while (iter < game->players_amount)
	{
		initialization_carriage(game);
		game->carriages->prev->tmp_value = -game->carriages_amount;
		conversetionIntToBytes(game->carriages->prev->value_buf, &game->carriages->prev->tmp_value, 0);
		writeFromBufToReg(game->carriages->prev->value_buf, game->carriages->prev->registers, R1, 0);
		ft_memset(game->carriages->prev->value_buf, 0, REG_SIZE);
		++iter;
	}
	game->carriages = game->carriages->prev;
	game->destructor->carriages_detect = TRUE;
}