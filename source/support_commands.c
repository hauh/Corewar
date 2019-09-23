/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/23 21:52:19 by vrichese         ###   ########.fr       */
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
	if (mode == READING_MODE)
	{
		if (input_arg == REG_CODE)
		{
			cwReadAndValidateReg(game);
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
			cwReadFromArenaToBuf(game->carriages->address_buf, game->arena->field, CARRIAGE_LOCATION, 2);
			cwConversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
			if (div_mod == TRUE)
				cwReadFromArenaToBuf(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
			else
				cwReadFromArenaToBuf(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + game->carriages->tmp_value) % MEM_SIZE, 0);
			CARRIAGE_LOCATION += IND_SIZE;
		}
	}
	else if (mode == WRITING_MODE)
	{
		if (input_arg == REG_CODE)
		{
			cwReadAndValidateReg(game);
			cwWriteFromBufToReg(read_write_dst, game->carriages->registers, REQUEST_REGISTER, 0);
			CARRIAGE_LOCATION += REGISTR_SIZE;
		}
		else if (input_arg == DIR_CODE)
		{
			cwWriteFromBufToReg(read_write_dst, game->arena->field, CARRIAGE_LOCATION, 4 - game->carriages->current_command->dir_size);
			CARRIAGE_LOCATION += game->carriages->current_command->dir_size;
		}
		else if (input_arg == IND_CODE)
		{
			cwReadFromArenaToBuf(game->carriages->address_buf, game->arena->field, CARRIAGE_LOCATION, 2);
			cwConversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
			if (div_mod == TRUE)
				cwWriteFromBufToArena(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
			else
				cwWriteFromBufToArena(read_write_dst, game->arena->field, (CARRIAGE_LOCATION + game->carriages->tmp_value) % MEM_SIZE, 0);
			CARRIAGE_LOCATION					+= IND_SIZE;
		}
	}
}

void		live_exec(corewar_t *game)
{
	int		reference;
	int		input;

	cwTypeHandler					(game);
	cwArgsHandler					(game, game->carriages->value_buf1, READING_MODE, FALSE, FIRST_ARG);
	cwReadFromRegToBuf				(game->carriages->common_buf, game->carriages->registers, R1, 0);
	cwConversetionBytesToInt		(game->carriages->common_buf, &reference, 0);
	cwConversetionBytesToInt		(game->carriages->value_buf1, &input, 0);
	if (-input == reference)
		game->arena->last_survivor	= game->carriages->owner;
	game->carriages->next_step		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION				= game->carriages->save_point;
	game->carriages->last_live_loop	= game->arena->loop_amount;
	game->arena->live_amount_in_ctd++;
}

void		ld_exec(corewar_t *game)
{
	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf1, WRITING_MODE, TRUE, SECOND_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		st_exec(corewar_t *game)
{
	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf1, WRITING_MODE, TRUE, SECOND_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		add_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, FALSE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &left_operand, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &right_operand, 0);
	result = left_operand + right_operand;
	cwConversetionIntToBytes	(game->carriages->common_buf, &result, 0);
	cwArgsHandler				(game, game->carriages->common_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		sub_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, FALSE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &left_operand, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &right_operand, 0);
	result = left_operand - right_operand;
	cwConversetionIntToBytes	(game->carriages->common_buf, &result, 0);
	cwArgsHandler				(game, game->carriages->common_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		and_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &left_operand, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &right_operand, 0);
	result = left_operand & right_operand;
	cwConversetionIntToBytes	(game->carriages->common_buf, &result, 0);
	cwArgsHandler				(game, game->carriages->common_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		or_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &left_operand, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &right_operand, 0);
	result = left_operand | right_operand;
	cwConversetionIntToBytes	(game->carriages->common_buf, &result, 0);
	cwArgsHandler				(game, game->carriages->common_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		xor_exec(corewar_t *game)
{
	int		left_operand;
	int		right_operand;
	int		result;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &left_operand, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &right_operand, 0);
	result = left_operand ^ right_operand;
	cwConversetionIntToBytes	(game->carriages->common_buf, &result, 0);
	cwArgsHandler				(game, game->carriages->common_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void		zjmp_exec(corewar_t *game)
{
	int 	jump;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &jump, 0);
	if (game->carriages->carry_flag)
		game->carriages->next_step = jump;
	else
		game->carriages->next_step = CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION = game->carriages->save_point;
}

void		ldi_exec(corewar_t *game)
{
	int		first_arg;
	int		second_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &first_arg, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &second_arg, 0);
	total_address = (first_arg + second_arg) % IDX_MOD;
	cwConversetionIntToBytes	(game->carriages->address_buf, &total_address, 0);
	cwArgsHandler				(game, game->carriages->address_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void	sti_exec(corewar_t *game)
{
	int		data;
	int		second_arg;
	int		third_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwArgsHandler				(game, game->carriages->value_buf3, READING_MODE, TRUE, THIRD_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &data, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &second_arg, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf3, &third_arg, 0);
	total_address = (second_arg + third_arg) % IDX_MOD;
	cwConversetionIntToBytes	(game->carriages->address_buf, &total_address, 0);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	cwWriteFromBufToArena		(game->carriages->address_buf, game->arena->field, (CARRIAGE_LOCATION + total_address) % MEM_SIZE, 0);
}

void	fork_exec(corewar_t *game)
{
	;
}

void	lld_exec(corewar_t *game)
{
	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf1, WRITING_MODE, FALSE, SECOND_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void	lldi_exec(corewar_t *game)
{
	int		first_arg;
	int		second_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->carriages->value_buf2, READING_MODE, TRUE, SECOND_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &first_arg, 0);
	cwConversetionBytesToInt	(game->carriages->value_buf2, &second_arg, 0);
	total_address = (first_arg + second_arg);
	cwConversetionIntToBytes	(game->carriages->address_buf, &total_address, 0);
	cwArgsHandler				(game, game->carriages->address_buf, WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}

void	lfork_exec(corewar_t *game)
{
	;
}

void		aff_exec(corewar_t *game)
{
	int 	output;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->carriages->value_buf1, READING_MODE, FALSE, FIRST_ARG);
	cwConversetionBytesToInt	(game->carriages->value_buf1, &output, 0);
	printf("%c", output);
	game->carriages->next_step	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
}