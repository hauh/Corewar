/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_movements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/01 13:56:24 by vrichese         ###   ########.fr       */
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
	int		f;
	int		s;
	int		t;

	lengthOfBrokenCode	= 1;
	iter				= 0;
	p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_MAIN_SAVE);
	p_carriage_instance->cw_move_to(p_carriage_instance, 1);
	if (p_carriage_instance->p_current_command->type_byte)
	{
		f = p_arena_obj->p_field[p_carriage_instance->current_location] >> 6 & 0x03;
		if (p_carriage_instance->p_current_command->args >> 24 & 0xff)
		{
			if (f == CW_REG_CODE)
				lengthOfBrokenCode += CW_REG_CODE_SIZE;
			else if (f == CW_DIR_CODE)
				lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
			else if (f == CW_IND_CODE)
				lengthOfBrokenCode += CW_IND_CODE_SIZE;
		}
		s = p_arena_obj->p_field[p_carriage_instance->current_location] >> 4 & 0x03;
		if (p_carriage_instance->p_current_command->args >> 16 & 0xff)
		{
			if (s == CW_REG_CODE)
				lengthOfBrokenCode += CW_REG_CODE_SIZE;
			else if (s == CW_DIR_CODE)
				lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
			else if (s == CW_IND_CODE)
				lengthOfBrokenCode += CW_IND_CODE_SIZE;
		}
		t = p_arena_obj->p_field[p_carriage_instance->current_location] >> 2 & 0x03;
		if (p_carriage_instance->p_current_command->args >> 8 & 0xff)
		{
			if (t == CW_REG_CODE)
				lengthOfBrokenCode += CW_REG_CODE_SIZE;
			else if (t == CW_DIR_CODE)
				lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
			else if (t == CW_IND_CODE)
				lengthOfBrokenCode += CW_IND_CODE_SIZE;
		}
		p_carriage_instance->cw_move_to(p_carriage_instance, lengthOfBrokenCode);
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Error occured while skipping damaged command");
}

void	cw_parse_types(t_carriage *p_carriage_instance, t_arena *p_arena_obj)
{
	int		sample;
	int		found;
	int		iter;

	p_carriage_instance->cw_move_to(p_carriage_instance, CW_NAME_PASS);
	found = CW_FALSE;
	if (p_carriage_instance->p_current_command->type_byte)
	{
		sample = p_carriage_instance->p_current_command->args >> 24 & 0xff;
		p_carriage_instance->first_arg = p_arena_obj->p_field[p_carriage_instance->current_location] >> 6 & 0x03;
		if (p_carriage_instance->first_arg == (!(sample >> 6 & 0x03) ? 2147483647 : (sample >> 6 & 0x03))
			|| p_carriage_instance->first_arg == (!(sample >> 4 & 0x03) ? 2147483647 : (sample >> 4 & 0x03))
			|| p_carriage_instance->first_arg == (!(sample >> 2 & 0x03) ? 2147483647 : (sample >> 2 & 0x03)))
			found = CW_TRUE;
		p_carriage_instance->first_arg == CW_REG_CODE ? p_carriage_instance->offset += CW_REG_CODE_SIZE : CW_FALSE;
		p_carriage_instance->first_arg == CW_DIR_CODE ? p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size : CW_FALSE;
		p_carriage_instance->first_arg == CW_IND_CODE ? p_carriage_instance->offset += CW_IND_CODE_SIZE : CW_FALSE;
		if (p_carriage_instance->first_arg == CW_REG_CODE)
		{
			if (p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] < 1
			|| p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] > 16)
			{
				p_carriage_instance->error_ocurred = CW_TRUE;
				found = CW_FALSE;
			}
		}
		if (!found && (p_carriage_instance->error_ocurred = CW_TRUE))
			return;
		found = CW_FALSE;
	 	sample = p_carriage_instance->p_current_command->args >> 16 & 0xff;
		if (sample)
		{
			p_carriage_instance->second_arg	= p_arena_obj->p_field[p_carriage_instance->current_location] >> 4 & 0x03;
			if (p_carriage_instance->second_arg == (!(sample >> 6 & 0x03) ? 2147483647 : (sample >> 6 & 0x03))
			|| p_carriage_instance->second_arg == (!(sample >> 4 & 0x03) ? 2147483647 : (sample >> 4 & 0x03))
			|| p_carriage_instance->second_arg == (!(sample >> 2 & 0x03) ? 2147483647 : (sample >> 2 & 0x03)))
				found = CW_TRUE;
			p_carriage_instance->second_arg == CW_REG_CODE ? p_carriage_instance->offset += CW_REG_CODE_SIZE : CW_FALSE;
			p_carriage_instance->second_arg == CW_DIR_CODE ? p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size : CW_FALSE;
			p_carriage_instance->second_arg == CW_IND_CODE ? p_carriage_instance->offset += CW_IND_CODE_SIZE : CW_FALSE;
			if (p_carriage_instance->second_arg == CW_REG_CODE)
			{
				if (p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] < 1
				|| p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] > 16)
				{
					p_carriage_instance->error_ocurred = CW_TRUE;
					found = CW_FALSE;
				}
			}
			if (!found && (p_carriage_instance->error_ocurred = CW_TRUE))
				return;
			found = CW_FALSE;
		}
		else
			p_carriage_instance->second_arg = 0;
	 	sample = p_carriage_instance->p_current_command->args >> 8 & 0xff;
		if (sample)
		{
	 		p_carriage_instance->third_arg = p_arena_obj->p_field[p_carriage_instance->current_location] >> 2 & 0x03;
			if (p_carriage_instance->third_arg == (!(sample >> 6 & 0x03) ? 2147483647 : (sample >> 6 & 0x03))
			|| p_carriage_instance->third_arg == (!(sample >> 4 & 0x03) ? 2147483647 : (sample >> 4 & 0x03))
			|| p_carriage_instance->third_arg == (!(sample >> 2 & 0x03) ? 2147483647 : (sample >> 2 & 0x03)))
				found = CW_TRUE;
			p_carriage_instance->third_arg == CW_REG_CODE ? p_carriage_instance->offset += CW_REG_CODE_SIZE : CW_FALSE;
			p_carriage_instance->third_arg == CW_DIR_CODE ? p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size : CW_FALSE;
			p_carriage_instance->third_arg == CW_IND_CODE ? p_carriage_instance->offset += CW_IND_CODE_SIZE : CW_FALSE;
			if (p_carriage_instance->third_arg == CW_REG_CODE)
			{
				if (p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] < 1
				|| p_arena_obj->p_field[(p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE] > 16)
				{
					p_carriage_instance->error_ocurred = CW_TRUE;
					found = CW_FALSE;
				}
			}
			if (!found && (p_carriage_instance->error_ocurred = CW_TRUE))
				return;
		}
		else
			p_carriage_instance->third_arg = 0;
	}
	else
	{
		p_carriage_instance->first_arg = CW_DIR_CODE;
		p_carriage_instance->second_arg	= CW_FALSE;
		p_carriage_instance->third_arg = CW_FALSE;
	}
	p_carriage_instance->cw_move_to(p_carriage_instance, p_carriage_instance->p_current_command->type_byte);
}