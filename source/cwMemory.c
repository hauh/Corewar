/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwMemory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:01:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 18:58:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwCopyReg(unsigned char *from, unsigned char *to, int size)
{
	int iter;

	iter = 0;
	while (iter < size)
	{
		to[iter] = from[iter];
		++iter;
	}
}

void	cwCheckCarry(unsigned char *registers, int *carry, int reg_num)
{
	int iter;

	iter = --reg_num * REG_SIZE;
	while (iter < reg_num * REG_SIZE + REG_SIZE)
	{
		if (registers[iter] != 0)
		{
			*carry = 0;
			return ;
		}
		++iter;
	}
	*carry = 1;
}

void	cwConversionIntToBytes(unsigned char *buffer, int *from, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
	{
		buffer[bias] = (*from << (bias * 8)) >> 24;
		++bias;
	}
}

void	cwConversionBytesToInt(unsigned char *buffer, void *dest, int bias, int type)
{
	char 	*char_value;
	short 	*short_value;
	int		*int_value;

	if (type == CW_CHAR)
	{
		char_value = (char *)dest;
		*char_value = 0;
		while (bias < REG_SIZE)
		{
			*char_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
	else if (type == CW_SHORT)
	{
		short_value = (short *)dest;
		*short_value = 0;
		while (bias < REG_SIZE)
		{
			*short_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
	else if (type == CW_INT)
	{
		int_value = (int *)dest;
		*int_value = 0;
		while (bias < REG_SIZE)
		{
			*int_value |= buffer[bias] << ((3 - bias) * 8);
			++bias;
		}
	}
}

void	cwReadFromRegToBuf(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
	{
		buffer[bias] = registers[bias + ((reg_num - 1) * REG_SIZE)];
		++bias;
	}
}

void	cwReadFromArenaToBuf(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	ft_memset(buffer, 0, REG_SIZE);
	while (bias < REG_SIZE)
		buffer[bias++] = field[data_location++];
}

void	cwWriteFromBufToReg(unsigned char *buffer, unsigned char *registers, int reg_num, int bias)
{
	while (bias < REG_SIZE)
	{
		registers[bias + ((reg_num - 1) * REG_SIZE)] = buffer[bias];
		++bias;
	}
}

void	cwWriteFromBufToArena(unsigned char *buffer, unsigned char *field, int data_location, int bias)
{
	while (bias < REG_SIZE)
		field[data_location++] = buffer[bias++];
}