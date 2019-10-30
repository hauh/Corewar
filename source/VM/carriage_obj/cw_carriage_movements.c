/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_movements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 16:30:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_save_pos(t_carriage *p_carriage_instance, int whichExactly)
{
	if (whichExactly == CW_MAIN_SAVE)
	{
		p_carriage_instance->odometer = 0;
		p_carriage_instance->save_point	= p_carriage_instance->current_location;
	}
	else if (whichExactly == CW_ADDIT_SAVE)
	{
		p_carriage_instance->addit_save_point = p_carriage_instance->current_location;
		p_carriage_instance->addit_odometer = p_carriage_instance->odometer;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Save_pos error");
}

void	cw_move_to(t_carriage *pCarraigeInstance, int distance)
{
	pCarraigeInstance->current_location = (pCarraigeInstance->current_location + distance) % MEM_SIZE;
	if (pCarraigeInstance->current_location < 0)
		pCarraigeInstance->current_location	= MEM_SIZE + pCarraigeInstance->current_location;
	pCarraigeInstance->odometer += (distance % MEM_SIZE);
}

void	cw_carriage_return(t_carriage *p_carriage_instance, int whereExactly)
{
	if (whereExactly == CW_MAIN_SAVE)
	{
		p_carriage_instance->odometer = 0;
		p_carriage_instance->current_location = p_carriage_instance->save_point;
	}
	else if (whereExactly == CW_ADDIT_SAVE)
	{
		p_carriage_instance->current_location = p_carriage_instance->addit_save_point;
		p_carriage_instance->odometer = p_carriage_instance->addit_odometer;
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Return carriage error");
}

void		cw_skip_damaged_command(t_carriage *p_carriage_instance, t_arena *p_arena_obj)
{
	int		lengthOfBrokenCode;
	int		iter;

	lengthOfBrokenCode	= 1;
	iter				= 0;
	p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_MAIN_SAVE);
	p_carriage_instance->cw_move_to(p_carriage_instance, 1);
	if (p_carriage_instance->p_current_command->type_byte)
	{
		while (++iter <= 3)
			if (((p_arena_obj->p_field[p_carriage_instance->current_location] >> (iter * 2)) & 0x03) == CW_REG_CODE)
				lengthOfBrokenCode += CW_REG_CODE_SIZE;
			else if (((p_arena_obj->p_field[p_carriage_instance->current_location] >> (iter * 2)) & 0x03) == CW_DIR_CODE)
				lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
			else if (((p_arena_obj->p_field[p_carriage_instance->current_location] >> (iter * 2)) & 0x03) == CW_IND_CODE)
				lengthOfBrokenCode += CW_IND_CODE_SIZE;
		p_carriage_instance->cw_move_to(p_carriage_instance, lengthOfBrokenCode);
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Error occured while skipping damaged command");
}

void	cw_parse_types(t_carriage *p_carriage_instance, t_arena *p_arena_obj)
{
	int		sample;
	int		iter;

	p_carriage_instance->cw_move_to(p_carriage_instance, CW_NAME_PASS);
	if (p_carriage_instance->p_current_command->type_byte)
	{
		if ((p_arena_obj->p_field[p_carriage_instance->current_location] & 0x03) != 0)
			p_carriage_instance->error_ocurred = CW_TRUE;
		p_carriage_instance->first_arg = (p_arena_obj->p_field[p_carriage_instance->current_location] & 0xc0) >> 6;
		iter = 0;
		sample = p_carriage_instance->p_current_command->args >> 24 & 0xff;
		if ((p_carriage_instance->p_current_command->args >> 24) & 0xff)
		{
			if (!p_carriage_instance->first_arg)
				iter = 4;
			while (++iter <= 3)
				if ((p_carriage_instance->first_arg & ((p_carriage_instance->p_current_command->args >> (24 + (iter * 2))) & 0xff)) == p_carriage_instance->first_arg)
					break;
		}
		else
			if (p_carriage_instance->first_arg != 0)
				iter = 5;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->first_arg);
		if ((iter > 3 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
			return ;
		p_carriage_instance->second_arg	= (p_arena_obj->p_field[p_carriage_instance->current_location] & 0x30) >> 4;
		iter = 0;
		if ((p_carriage_instance->p_current_command->args >> 16) & 0xff)
		{
			if (!p_carriage_instance->second_arg)
				iter = 4;
			while (++iter <= 3)
				if ((p_carriage_instance->second_arg & ((p_carriage_instance->p_current_command->args >> (16 + (iter * 2))) & 0xff)) == p_carriage_instance->second_arg)
					break;
		}
		else
			if (p_carriage_instance->second_arg != 0)
				iter = 5;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->second_arg);
		if ((iter > 3 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
			return ;
		p_carriage_instance->third_arg = (p_arena_obj->p_field[p_carriage_instance->current_location] & 0x0c) >> 2;
		iter = 0;
		if ((p_carriage_instance->p_current_command->args >> 8) & 0xff)
		{
			if (!p_carriage_instance->third_arg)
				iter = 4;
			while (++iter <= 3)
				if ((p_carriage_instance->third_arg & ((p_carriage_instance->p_current_command->args >> (8 + (iter * 2))) & 0xff)) == p_carriage_instance->third_arg)
					break;
		}
		else
			if (p_carriage_instance->third_arg != 0)
				iter = 5;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->third_arg);
		if ((iter > 3 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
			return ;
	}
	else
	{
		p_carriage_instance->first_arg = CW_DIR_CODE;
		p_carriage_instance->second_arg	= CW_FALSE;
		p_carriage_instance->third_arg = CW_FALSE;
	}
	p_carriage_instance->cw_move_to(p_carriage_instance, p_carriage_instance->p_current_command->type_byte);
}