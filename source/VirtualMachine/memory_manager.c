/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:01:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 19:04:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void	read_from_reg_to_buf(carriage_t *carriage, int reg_num)
{
	int iter;
	int buf_iter;

	buf_iter = 0;
	iter = --reg_num * REG_SIZE;
	while (buf_iter < REG_SIZE)
	{
		carriage->reg_buf[buf_iter] = carriage->registers[iter];
		++iter;
		++buf_iter;
	}
}

void	read_from_arena_to_buf(carriage_t *carriage, unsigned char *field, int data_location, int amount)
{
	int buf_iter;

	buf_iter = 0;
	while (buf_iter < amount)
	{
		carriage->reg_buf[buf_iter] = field[data_location];
		++data_location;
		++buf_iter;
	}
}

void	write_from_buf_to_reg(carriage_t *carriage, int reg_num)
{
	int iter;
	int buf_iter;

	buf_iter = 0;
	iter = --reg_num * REG_SIZE;
	while (buf_iter < REG_SIZE)
	{
		carriage->registers[iter] = carriage->reg_buf[buf_iter];
		++iter;
		++buf_iter;
	}
}

void	write_from_buf_to_arena(carriage_t *carriage, unsigned char *field, int data_location)
{
	int buf_iter;

	buf_iter = 0;
	while (buf_iter < REG_SIZE)
	{
		field[data_location] = carriage->reg_buf[buf_iter];
		++data_location;
		++buf_iter;
	}
}