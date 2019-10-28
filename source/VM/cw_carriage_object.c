/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/28 16:03:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_reg_check(carriage_t *p_carriage_instance, arena_t *p_arena_obj, int type)
{
	int location;

	if (type == CW_REG_CODE)
		p_carriage_instance->offset += CW_REG_CODE_SIZE;
	else if (type == CW_DIR_CODE)
		p_carriage_instance->offset += p_carriage_instance->p_current_command->dir_size;
	else if (type == CW_IND_CODE)
		p_carriage_instance->offset += CW_IND_CODE_SIZE;
	if (type == CW_REG_CODE)
	{
		location = (p_carriage_instance->current_location + p_carriage_instance->offset) % MEM_SIZE;
		if (location < 0)
			location = MEM_SIZE + location;
		if (p_arena_obj->p_field[location] < 1 || p_arena_obj->p_field[location] > 16)
			p_carriage_instance->error_ocurred = CW_TRUE;
	}
}

static void	cw_copy_reg(carriage_t *p_carriage_instance, carriage_t *p_copying_carriage)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < CW_REG_SIZE * CW_REG_NUMBER)
		p_copying_carriage->p_registers[iter] = p_carriage_instance->p_registers[iter];
}

static void	cw_write_owner_id_to_reg(carriage_t *p_carriage_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	while (iter < CW_REG_SIZE)
	{
		p_carriage_instance->p_registers[iter] = (-p_carriage_instance->p_owner->id << (iter * 8)) >> 24;
		++iter;
	}
}

static void	cw_check_carry(carriage_t *p_carriage_instance)
{
	int		iter;

	iter = p_carriage_instance->current_register * CW_REG_SIZE - 1;
	while (++iter < (p_carriage_instance->current_register + 1) * CW_REG_SIZE)
		if (p_carriage_instance->p_registers[iter] != 0 && !(p_carriage_instance->carry = 0))
			return ;
	p_carriage_instance->carry = 1;
}

static void	cw_conversion_value_to_bytes(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->p_data[type] = (pBufferObj->s_types.int_value << (type * 8)) >> 24;
		++type;
	}
}

static void	cw_conversion_bytes_to_value(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	pBufferObj->s_types.int_value = 0;
	while (type < CW_REG_SIZE)
	{
		pBufferObj->s_types.int_value |= pBufferObj->p_data[type] << ((3 - type) * 8);
		++type;
	}
}

void		cw_write_operation(carriage_t *p_carriage_instance, arena_t *p_arena_obj, buffer_t *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE] = pBufferObj->p_data[i];
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		for (int i = 4 - p_carriage_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->p_field[p_carriage_instance->current_location] = pBufferObj->p_data[i];
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CW_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
		p_carriage_instance->cw_save_pos(p_carriage_instance, CW_ADDIT_SAVE);
		p_carriage_instance->cw_move_to	(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->p_field[p_carriage_instance->current_location] = pBufferObj->p_data[i];
		p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_ADDIT_SAVE);
	}
}

static void	cw_read_operation(carriage_t *p_carriage_instance, arena_t *p_arena_obj, buffer_t *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			pBufferObj->p_data[i] = p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = 4 - p_carriage_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, 4 - p_carriage_instance->p_current_command->dir_size);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CW_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
		p_carriage_instance->cw_save_pos(p_carriage_instance, CW_ADDIT_SAVE);
		p_carriage_instance->cw_move_to(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_carriage_return(p_carriage_instance, CW_ADDIT_SAVE);
	}
}

static void	cw_parse_types(carriage_t *p_carriage_instance, arena_t *p_arena_obj)
{
	int		iter;

	p_carriage_instance->cw_move_to(p_carriage_instance, CW_NAME_PASS);
	if (p_carriage_instance->p_current_command->type_byte)
	{
		p_carriage_instance->first_arg = (p_arena_obj->p_field[p_carriage_instance->current_location] & 0xc0) >> 6;
		iter = 0;
		if ((p_carriage_instance->p_current_command->args >> 24) & 0xff)
			while (++iter <= 3)
				if ((p_carriage_instance->first_arg & (p_carriage_instance->p_current_command->args >> (24 + (iter * 2)))) == p_carriage_instance->first_arg)
					break;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->first_arg);
		if ((iter == 4 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
			return ;
		p_carriage_instance->second_arg	= (p_arena_obj->p_field[p_carriage_instance->current_location] & 0x30) >> 4;
		iter = 0;
		if ((p_carriage_instance->p_current_command->args >> 16) & 0xff)
			while (++iter <= 3)
				if ((p_carriage_instance->second_arg & ((p_carriage_instance->p_current_command->args >> (16 + (iter * 2))))) == p_carriage_instance->second_arg)
					break;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->second_arg);
		if ((iter == 4 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
			return ;
		p_carriage_instance->third_arg = (p_arena_obj->p_field[p_carriage_instance->current_location] & 0x0c) >> 2;
		iter = 0;
		if ((p_carriage_instance->p_current_command->args >> 8) & 0xff)
			while (++iter <= 3)
				if ((p_carriage_instance->third_arg & (p_carriage_instance->p_current_command->args >> (8 + (iter * 2)))) == p_carriage_instance->third_arg)
					break;
		p_carriage_instance->cw_reg_check(p_carriage_instance, p_arena_obj, p_carriage_instance->third_arg);
		if ((iter == 4 && (p_carriage_instance->error_ocurred = CW_TRUE)) || p_carriage_instance->error_ocurred)
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

static void	cw_carriage_return(carriage_t *p_carriage_instance, int whereExactly)
{
	if (whereExactly == CW_MAIN_SAVE)
	{
		p_carriage_instance->current_location	= p_carriage_instance->save_point;
		p_carriage_instance->odometer			= 0;
	}
	else if (whereExactly == CW_ADDIT_SAVE)
	{
		p_carriage_instance->current_location	= p_carriage_instance->addit_save_point;
		p_carriage_instance->odometer			= p_carriage_instance->addit_odometer;
	}
}

static void	cw_move_to(carriage_t *pCarraigeInstance, int distance)
{
	int test;

	test = pCarraigeInstance->current_location;
	pCarraigeInstance->current_location = (pCarraigeInstance->current_location + distance) % MEM_SIZE;
	if (pCarraigeInstance->current_location < 0)
		pCarraigeInstance->current_location	= MEM_SIZE + pCarraigeInstance->current_location;
	pCarraigeInstance->odometer += (distance % MEM_SIZE);
}

static void	cw_save_pos(carriage_t *p_carriage_instance, int whichExactly)
{
	if (whichExactly == CW_MAIN_SAVE)
	{
		p_carriage_instance->save_point	= p_carriage_instance->current_location;
		p_carriage_instance->odometer = 0;
	}
	else if (whichExactly == CW_ADDIT_SAVE)
	{
		p_carriage_instance->addit_save_point = p_carriage_instance->current_location;
		p_carriage_instance->addit_odometer = p_carriage_instance->odometer;
	}
}

static void	cwReducewaiting_time(carriage_t *pCarraigeInstance)
{
	if (pCarraigeInstance->waiting_time > 0)
		pCarraigeInstance->waiting_time -= 1;
}

static void	cw_exec_command(carriage_t *p_carriage_instance, corewar_t *pGameInstance)
{
	if (p_carriage_instance->waiting_time || p_carriage_instance->error_ocurred)
		return ;
	p_carriage_instance->p_current_command->cw_callback(pGameInstance);
	if (p_carriage_instance->error_ocurred)
		p_carriage_instance->cw_return_protocol_activate(p_carriage_instance, pGameInstance->p_arena_obj);
	p_carriage_instance->p_current_command = NULL;
}

static void	cw_set_command_time(carriage_t *p_carriage_instance, arena_t *pArenaInstance)
{
	if (p_carriage_instance->waiting_time)
		return ;
	if (pArenaInstance->p_field[p_carriage_instance->current_location] < CW_LIVE || pArenaInstance->p_field[p_carriage_instance->current_location] > CW_AFF)
	{
		p_carriage_instance->cw_move_to(p_carriage_instance, 1);
		p_carriage_instance->error_ocurred = CW_TRUE;
		return ;
	}
	p_carriage_instance->offset			= 0;
	p_carriage_instance->error_ocurred 	= CW_FALSE;
	p_carriage_instance->p_current_command	= p_carriage_instance->pp_command_container[pArenaInstance->p_field[p_carriage_instance->current_location]];
	p_carriage_instance->waiting_time = p_carriage_instance->p_current_command->waiting_time;
	p_carriage_instance->cw_save_pos(p_carriage_instance, CW_MAIN_SAVE);
}

static void	cw_set_owner(carriage_t *p_carriage_instance, player_t *pPlayerList, int playersAmount)
{
	int		iter;

	iter = CW_ITERATOR;
	while (++iter < playersAmount)
	{
		if (pPlayerList->id == p_carriage_instance->id)
			p_carriage_instance->p_owner = pPlayerList;
		pPlayerList = pPlayerList->p_next;
	}
}

static void	cw_return_protocol_activate(carriage_t *p_carriage_instance, arena_t *p_arena_obj)
{
	int		lengthOfBrokenCode;
	int		iter;

	lengthOfBrokenCode	= 0;
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
		p_carriage_instance->cw_move_to(p_carriage_instance, lengthOfBrokenCode + 1);
	}
	else
		p_carriage_instance->cw_move_to(p_carriage_instance, p_carriage_instance->p_current_command->dir_size);
}

static void	cw_constructor(carriage_t **pp_carriage_instance)
{
	if (!((*pp_carriage_instance)->p_registers = (unsigned char *)malloc(sizeof(unsigned char) * CW_REG_NUMBER * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset((*pp_carriage_instance)->p_registers, 0, CW_REG_NUMBER * CW_REG_SIZE);
	(*pp_carriage_instance)->id = 0;
	(*pp_carriage_instance)->carry = CW_FALSE;
	(*pp_carriage_instance)->waiting_time = 0;
	(*pp_carriage_instance)->last_speak_cycle = 0;
	(*pp_carriage_instance)->addit_save_point = 0;
	(*pp_carriage_instance)->current_location = 0;
	(*pp_carriage_instance)->first_arg = 0;
	(*pp_carriage_instance)->second_arg = 0;
	(*pp_carriage_instance)->third_arg = 0;
	(*pp_carriage_instance)->odometer = 0;
	(*pp_carriage_instance)->addit_odometer = 0;
	(*pp_carriage_instance)->p_current_command = NULL;
	(*pp_carriage_instance)->p_owner = NULL;
	(*pp_carriage_instance)->p_next = NULL;
	(*pp_carriage_instance)->p_prev = NULL;
	(*pp_carriage_instance)->offset = 0;
	(*pp_carriage_instance)->checked = 0;
}

static void	cw_destructor(carriage_t **pp_carriage_instance)
{
	free((*pp_carriage_instance)->p_registers);
	free((*pp_carriage_instance));
	*pp_carriage_instance = NULL;
}

extern void	cw_create_instance_carriage(carriage_t **ppCarriageObj)
{
	if (!(*ppCarriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*ppCarriageObj)->cw_constructor = cw_constructor;
	(*ppCarriageObj)->cw_destructor = cw_destructor;
	(*ppCarriageObj)->cw_conversion_value_to_bytes = cw_conversion_value_to_bytes;
	(*ppCarriageObj)->cw_conversion_bytes_to_value = cw_conversion_bytes_to_value;
	(*ppCarriageObj)->cw_read_operation = cw_read_operation;
	(*ppCarriageObj)->cw_write_operation = cw_write_operation;
	(*ppCarriageObj)->cw_parse_types = cw_parse_types;
	(*ppCarriageObj)->cw_check_carry = cw_check_carry;
	(*ppCarriageObj)->cw_save_pos = cw_save_pos;
	(*ppCarriageObj)->cw_move_to = cw_move_to;
	(*ppCarriageObj)->cw_exec_command = cw_exec_command;
	(*ppCarriageObj)->cw_set_command_time = cw_set_command_time;
	(*ppCarriageObj)->cw_reduce_time = cwReducewaiting_time;
	(*ppCarriageObj)->cw_write_owner_id_to_reg = cw_write_owner_id_to_reg;
	(*ppCarriageObj)->cw_carriage_return = cw_carriage_return;
	(*ppCarriageObj)->cw_return_protocol_activate = cw_return_protocol_activate;
	(*ppCarriageObj)->cw_set_owner = cw_set_owner;
	(*ppCarriageObj)->cw_copy_reg = cw_copy_reg;
	(*ppCarriageObj)->cw_reg_check = cw_reg_check;
	(*ppCarriageObj)->cw_constructor(ppCarriageObj);
}
