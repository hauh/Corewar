/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 17:24:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cwTypeHandler(corewar_t *game)
{
	game->carriages->save_point = CARRIAGE_LOCATION;
	CARRIAGE_LOCATION += game->carriages->current_command->availability_types;
	if (game->carriages->current_command->id != LIVE	&& game->carriages->current_command->id != ZJMP
	&&  game->carriages->current_command->id != FORK	&& game->carriages->current_command->id != LFORK)
	{
		game->carriages->current_command->first_arg		= (game->arena->field[CARRIAGE_LOCATION] & 0xc0) >> 6;
		game->carriages->current_command->second_arg	= (game->arena->field[CARRIAGE_LOCATION] & 0x30) >> 4;
		game->carriages->current_command->third_arg		= (game->arena->field[CARRIAGE_LOCATION] & 0x0c) >> 2;
	}
	else
	{
		game->carriages->current_command->first_arg		= DIR_CODE;
		game->carriages->current_command->second_arg	= FALSE;
		game->carriages->current_command->third_arg		= FALSE;
	}
	CARRIAGE_LOCATION += TO_FIRST_ARG;
}

void		cwReadAndValidateReg(corewar_t *game)
{
	int		current_register;

	current_register = game->arena->field[CARRIAGE_LOCATION];
	if (current_register < 1 || current_register > 16)
		REQUEST_REGISTER = ERROR;
	else
		REQUEST_REGISTER = current_register;
}

void	cwArgsHandler(corewar_t *game, unsigned char *read_write_dst, int mode, int div_mod, int input_arg)
{
	if (mode == CW_READING_MODE)
	{
		if (input_arg == REG_CODE)
		{
			cwReadAndValidateReg(game);
			if (REQUEST_REGISTER == ERROR)
				return;
			cwReadFromRegToBuf(read_write_dst, game->carriages->registers, REQUEST_REGISTER, 0);
			CARRIAGE_LOCATION += REGISTR_SIZE;
		}
		else if (input_arg == DIR_CODE)
		{
			cwReadFromArenaToBuf(read_write_dst, game->arena->field, CARRIAGE_LOCATION, DYNAMIC_SIZE_DIR);
			CARRIAGE_LOCATION += game->carriages->current_command->dir_size;
		}
		else if (input_arg == IND_CODE)
		{
			cwReadFromArenaToBuf(game->arena->address_buf, game->arena->field, CARRIAGE_LOCATION, 2);
			cwConversionBytesToInt(game->arena->address_buf, &game->arena->tmp_value1, 2);
			if (div_mod == TRUE)
				cwReadFromArenaToBuf(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + (game->arena->tmp_value1 % IDX_MOD)) % MEM_SIZE, 0);
			else
				cwReadFromArenaToBuf(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + game->arena->tmp_value1) % MEM_SIZE, 0);
			CARRIAGE_LOCATION += IND_SIZE;
		}
	}
	else if (mode == CW_WRITING_MODE)
	{
		if (input_arg == REG_CODE)
		{
			cwReadAndValidateReg(game);
			if (REQUEST_REGISTER == ERROR)
				return;
			cwWriteFromBufToReg(read_write_dst, game->carriages->registers, REQUEST_REGISTER, 0);
			CARRIAGE_LOCATION += REGISTR_SIZE;
		}
		else if (input_arg == DIR_CODE)
		{
			cwWriteFromBufToReg(read_write_dst, game->arena->field, CARRIAGE_LOCATION, DYNAMIC_SIZE_DIR);
			CARRIAGE_LOCATION += game->carriages->current_command->dir_size;
		}
		else if (input_arg == IND_CODE)
		{
			cwReadFromArenaToBuf(game->arena->address_buf, game->arena->field, CARRIAGE_LOCATION, 2);
			cwConversionBytesToInt(game->arena->address_buf, &game->arena->tmp_value1, 2);
			if (div_mod == TRUE)
				cwWriteFromBufToArena(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + (game->arena->tmp_value1 % IDX_MOD)) % MEM_SIZE, 0);
			else
				cwWriteFromBufToArena(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + game->arena->tmp_value1) % MEM_SIZE, 0);
			CARRIAGE_LOCATION += IND_SIZE;
		}
	}
}

void		live_exec(corewar_t *game)
{
	int		reference;
	int		input;

	cwTypeHandler					(game);
	cwArgsHandler					(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	if (REQUEST_REGISTER == ERROR)
		return;
	cwReadFromRegToBuf				(game->arena->value_buf2, game->carriages->registers, R1, 0);
	cwConversionBytesToInt			(game->arena->value_buf2, &reference, 0);
	cwConversionBytesToInt			(game->arena->value_buf1, &input, 0);
	if (-input == reference)
		game->arena->last_survivor	= game->carriages->owner;
	game->carriages->jump			= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION				= game->carriages->save_point;
	game->carriages->last_cycle		= game->arena->cycle_amount;
	game->arena->live_amount++;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		ld_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwArgsHandler			(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler			(game, game->arena->value_buf1, CW_WRITING_MODE, TRUE, SECOND_ARG);
	game->carriages->jump	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION		= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		st_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwArgsHandler			(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler			(game, game->arena->value_buf1, CW_WRITING_MODE, TRUE, SECOND_ARG);
	game->carriages->jump	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION		= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		add_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, FALSE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &left_operand, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &right_operand, 0);
	result = left_operand + right_operand;
	cwConversionIntToBytes		(game->arena->value_buf3, &result, 0);
	cwArgsHandler				(game, game->arena->value_buf3, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		sub_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, FALSE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &left_operand, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &right_operand, 0);
	result = left_operand - right_operand;
	cwConversionIntToBytes		(game->arena->value_buf3, &result, 0);
	cwArgsHandler				(game, game->arena->value_buf3, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		and_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &left_operand, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &right_operand, 0);
	result = left_operand & right_operand;
	cwConversionIntToBytes		(game->arena->value_buf3, &result, 0);
	cwArgsHandler				(game, game->arena->value_buf3, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		or_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &left_operand, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &right_operand, 0);
	result = left_operand | right_operand;
	cwConversionIntToBytes		(game->arena->value_buf3, &result, 0);
	cwArgsHandler				(game, game->arena->value_buf3, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		xor_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &left_operand, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &right_operand, 0);
	result = left_operand ^ right_operand;
	cwConversionIntToBytes		(game->arena->value_buf3, &result, 0);
	cwArgsHandler				(game, game->arena->value_buf3, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		zjmp_exec(corewar_t *game)
{
	int 	jump;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &jump, 0);
	if (game->carriages->carry)
		game->carriages->jump = jump;
	else
		game->carriages->jump = CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION = game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		ldi_exec(corewar_t *game)
{
	int		first_arg;
	int		second_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &first_arg, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &second_arg, 0);
	total_address = (first_arg + second_arg) % IDX_MOD;
	cwConversionIntToBytes		(game->arena->address_buf, &total_address, 0);
	cwArgsHandler				(game, game->arena->address_buf, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void	sti_exec(corewar_t *game)
{
	int		data;
	int		second_arg;
	int		third_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwArgsHandler				(game, game->arena->value_buf3, CW_READING_MODE, TRUE, THIRD_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &data, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &second_arg, 0);
	cwConversionBytesToInt		(game->arena->value_buf3, &third_arg, 0);
	total_address = (second_arg + third_arg) % IDX_MOD;
	cwConversionIntToBytes		(game->arena->address_buf, &total_address, 0);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	cwWriteFromBufToArena		(game->arena->address_buf, game->arena->field, (CARRIAGE_LOCATION + total_address) % MEM_SIZE, 0);
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void			fork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;
	int			total_address;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	copy_reg(game->carriages->registers, new_carriage->registers, REG_NUMBER * REG_SIZE);
	new_carriage->id				= game->carriages->id;
	new_carriage->jump				= FALSE;
	new_carriage->owner				= game->carriages->owner;
	new_carriage->carry				= game->carriages->carry;
	new_carriage->last_cycle		= game->carriages->last_cycle;
	new_carriage->waiting_time		= FALSE;
	new_carriage->error_occured		= FALSE;
	new_carriage->current_command	= NULL;
	cwTypeHandler					(game);
	cwArgsHandler					(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwConversionBytesToInt			(game->arena->value_buf1, &total_address, 0);
	new_carriage->current_location 	= total_address % IDX_MOD;
	new_carriage->prev				= game->arena->last_carriage;
	new_carriage->next				= game->arena->last_carriage->next;
	game->arena->last_carriage->next = new_carriage;
	game->arena->last_carriage		= new_carriage;
	game->carriages_amount++;
	game->carriages->jump			= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION				= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void	lld_exec(corewar_t *game)
{
	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf1, CW_WRITING_MODE, FALSE, SECOND_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void	lldi_exec(corewar_t *game)
{
	int		first_arg;
	int		second_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &first_arg, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &second_arg, 0);
	total_address = (first_arg + second_arg);
	cwConversionIntToBytes		(game->arena->address_buf, &total_address, 0);
	cwArgsHandler				(game, game->arena->address_buf, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void	lfork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;
	int			total_address;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	copy_reg(game->carriages->registers, new_carriage->registers, REG_NUMBER * REG_SIZE);
	new_carriage->id				= game->carriages->id;
	new_carriage->jump				= FALSE;
	new_carriage->owner				= game->carriages->owner;
	new_carriage->carry				= game->carriages->carry;
	new_carriage->last_cycle		= game->carriages->last_cycle;
	new_carriage->waiting_time		= FALSE;
	new_carriage->error_occured		= FALSE;
	new_carriage->current_command	= NULL;
	cwTypeHandler					(game);
	cwArgsHandler					(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwConversionBytesToInt			(game->arena->value_buf1, &total_address, 0);
	new_carriage->current_location 	= total_address % MEM_SIZE;
	new_carriage->prev				= game->arena->last_carriage;
	new_carriage->next				= game->arena->last_carriage->next;
	game->arena->last_carriage->next = new_carriage;
	game->arena->last_carriage		= new_carriage;
	game->carriages_amount++;
	game->carriages->jump			= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION				= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		aff_exec(corewar_t *game)
{
	int 	output;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwConversionBytesToInt	(game->arena->value_buf1, &output, 0);
	printf("%c", output);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}