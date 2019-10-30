/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_movements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/30 20:12:32 by vrichese         ###   ########.fr       */
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
		if (f == CW_REG_CODE)
			lengthOfBrokenCode += CW_REG_CODE_SIZE;
		else if (f == CW_DIR_CODE)
			lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
		else if (f == CW_IND_CODE)
			lengthOfBrokenCode += CW_IND_CODE_SIZE;
		s = p_arena_obj->p_field[p_carriage_instance->current_location] >> 4 & 0x03;
		if (s == CW_REG_CODE)
			lengthOfBrokenCode += CW_REG_CODE_SIZE;
		else if (s == CW_DIR_CODE)
			lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
		else if (s == CW_IND_CODE)
			lengthOfBrokenCode += CW_IND_CODE_SIZE;
		t = p_arena_obj->p_field[p_carriage_instance->current_location] >> 2 & 0x03;
		if (t == CW_REG_CODE)
			lengthOfBrokenCode += CW_REG_CODE_SIZE;
		else if (t == CW_DIR_CODE)
			lengthOfBrokenCode += p_carriage_instance->p_current_command->dir_size;
		else if (t == CW_IND_CODE)
			lengthOfBrokenCode += CW_IND_CODE_SIZE;
		p_carriage_instance->cw_move_to(p_carriage_instance, lengthOfBrokenCode);
	}
	else
		cw_error_catcher(CW_KERNEL_ERROR, "Error occured while skipping damaged command");
}

void	cw_parse_types(t_carriage *p_carriage_instance, t_arena *p_arena_obj)
{
	int		sample1;
	int		sample2;
	int		sample3;
	int		found = CW_FALSE;
	int 	f_s;
	int		s_s;
	int		t_s;
	int		iter;

	p_carriage_instance->cw_move_to(p_carriage_instance, CW_NAME_PASS);
	p_carriage_instance->offset = 0;
	if (p_carriage_instance->p_current_command->type_byte)
	{
		sample1 = p_carriage_instance->p_current_command->args >> 24 & 0xff;
	 	sample2 = p_carriage_instance->p_current_command->args >> 16 & 0xff;
	 	sample3 = p_carriage_instance->p_current_command->args >> 8 & 0xff;
		f_s = sample1 >> 6 & 0x03;
		!f_s ? f_s = 2147483647 : 0;
		s_s = sample1 >> 4 & 0x03;
		!s_s ? s_s = 2147483647 : 0;
		t_s = sample1 >> 2 & 0x03;
		!t_s ? t_s = 2147483647 : 0;
		p_carriage_instance->first_arg = p_arena_obj->p_field[p_carriage_instance->current_location] >> 6 & 0x03;
		if (p_carriage_instance->first_arg == f_s || p_carriage_instance->first_arg == s_s || p_carriage_instance->first_arg == t_s)
			found = CW_TRUE;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->first_arg, &found);
		if (!found && (p_carriage_instance->error_ocurred = CW_TRUE))
			return;
		found = CW_FALSE;
		if (sample2)
		{
	 		f_s = sample2 >> 6 & 0x03;
			!f_s ? f_s = 2147483647 : 0;
			s_s = sample2 >> 4 & 0x03;
			!s_s ? s_s = 2147483647 : 0;
			t_s = sample2 >> 2 & 0x03;
			!t_s ? t_s = 2147483647 : 0;
			p_carriage_instance->second_arg	= p_arena_obj->p_field[p_carriage_instance->current_location] >> 4 & 0x03;
			if (p_carriage_instance->second_arg == f_s || p_carriage_instance->second_arg == s_s || p_carriage_instance->second_arg == t_s)
				found = CW_TRUE;
			p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->second_arg, &found);
			if (!found && (p_carriage_instance->error_ocurred = CW_TRUE))
				return;
			found = CW_FALSE;
		}
		else
			p_carriage_instance->second_arg = 0;
		if (sample3)
		{
			f_s = sample3 >> 6 & 0x03;
			!f_s ? f_s = 2147483647 : 0;
			s_s = sample3 >> 4 & 0x03;
			!s_s ? s_s = 2147483647 : 0;
			t_s = sample3 >> 2 & 0x03;
			!t_s ? t_s = 2147483647 : 0;
	 		p_carriage_instance->third_arg = p_arena_obj->p_field[p_carriage_instance->current_location] >> 2 & 0x03;
			if (p_carriage_instance->third_arg == f_s || p_carriage_instance->third_arg == s_s || p_carriage_instance->third_arg == t_s)
				found = CW_TRUE;
			p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->second_arg, &found);
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