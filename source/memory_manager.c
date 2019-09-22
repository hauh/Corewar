/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:01:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/22 19:37:15 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_carry(unsigned char *buffer, int *carry)
{
	int iter;

	iter = 0;
	while (iter < REG_SIZE)
	{
		if (buffer[iter] != 0)
		{
			*carry = 1;
			return ;
		}
		++iter;
	}
	*carry = 1;
}

void	conversetionIntToBytes(unsigned char *buffer, int *from, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
	{
		buffer[bias] = (*from << (3 - bias) * 8) >> 24;
		++bias;
	}
}

void	conversetionBytesToInt(unsigned char *buffer, int *dest, int bias)
{
	*dest = 0;
	while (bias < REG_SIZE)
	{
		*dest |= buffer[bias] << ((3 - bias) * 8);
		++bias;
	}
}

void	readFromRegToBuf(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
	{
		buffer[bias] = registers[bias + ((reg_num + 1) * REG_SIZE)];
		++bias;
	}
}

void	readFromArenaToBuf(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
		buffer[bias++] = field[data_location++];
}

void	writeFromBufToReg(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	while (bias < REG_SIZE)
	{
		buffer[bias] = registers[bias + ((reg_num - 1) * REG_SIZE)];
		++bias;
	}
}

void	writeFromBufToArena(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	while (bias < REG_SIZE)
		field[data_location++] = buffer[bias++];
}