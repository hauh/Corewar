/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/30 21:13:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cwTypeHandler(corewar_t *game)
{
	CW_CARRIAGE_SAVE_POINT = CW_CARRIAGE_LOCATION;
	CW_CARRIAGE_LOCATION += CW_AVAILABILITY_TYPES;
	if (CW_CURRENT_COMMAND->id != LIVE && CW_CURRENT_COMMAND->id != ZJMP
	&&  CW_CURRENT_COMMAND->id != FORK && CW_CURRENT_COMMAND->id != LFORK)
	{
		CW_FIRST_ARG	= (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] & 0xc0) >> 6;
		CW_SECOND_ARG	= (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] & 0x30) >> 4;
		CW_THIRD_ARG	= (CW_GAME_ARENA[CW_CARRIAGE_LOCATION] & 0x0c) >> 2;
	}
	else
	{
		CW_FIRST_ARG	= DIR_CODE;
		CW_SECOND_ARG	= CW_FALSE;
		CW_THIRD_ARG	= CW_FALSE;
	}
	CW_CARRIAGE_LOCATION += TO_FIRST_ARG;
}

void		cwReadAndValidateReg(corewar_t *game)
{
	int		current_register;

	current_register = game->arena->field[CW_CARRIAGE_LOCATION];
	if (current_register > 0 && current_register < 17)
		CW_REQUESTING_REGISTER = current_register;
	else
	{
		game->carriages->error_occured = TRUE;
		cwErrorCatcher(CW_CHEAT_DETECT, CW_COMMAND);
	}
}

void		cwWriteOperaion(corewar_t *game, unsigned char *buffer, int idx_mod, int input_arg)
{
	int		save_point;

	if (input_arg == CW_REG_CODE)
	{
		cwReadAndValidateReg(game);
		cwWriteFromBufToReg(buffer, CW_CARRIAGE_REGISTERS, CW_REQUESTING_REGISTER, CW_INT_BIAS);
		CW_CARRIAGE_LOCATION += CW_REGISTER_SIZE;
	}
	else if (input_arg == CW_DIR_CODE)
	{
		cwWriteFromBufToReg(buffer, CW_GAME_ARENA, CW_CARRIAGE_LOCATION, CW_DYNAMIC_SIZE_DIR);
		CW_CARRIAGE_LOCATION += CW_CURRENT_COMMAND->dir_size;
	}
	else if (input_arg == CW_IND_CODE)
	{
		save_point = CW_CARRIAGE_LOCATION;
		cwReadFromArenaToBuf(CW_BUFFER_SET[CW_SYSTEM_BUF], game->arena->field, CW_CARRIAGE_LOCATION, CW_SHORT_BIAS);
		cwConversionBytesToInt(CW_BUFFER_SET[CW_SYSTEM_BUF], &CW_BUFFER_SET[CW_SYSTEM_BUF]->short_value, CW_SHORT_BIAS);
		if (idx_mod == TRUE)
			CW_CARRIAGE_LOCATION = (game->carriages->save_point + (game->arena->short_value % IDX_MOD)) % MEM_SIZE;
		else
			CW_CARRIAGE_LOCATION = (game->carriages->save_point + game->arena->short_value) % MEM_SIZE;
		cwWriteFromBufToArena(buffer, game->arena->field, CW_CARRIAGE_LOCATION, 0);
		CW_CARRIAGE_LOCATION = save_point;
		CW_CARRIAGE_LOCATION += IND_SIZE;
	}
}

void		cwReadOperation(corewar_t *game, unsigned char *buffer, int idx_mod, int input_arg)
{
	int		save_point;

	if (input_arg == CW_REG_CODE)
	{
		cwReadAndValidateReg(game);
		cwReadFromRegToBuf(read_dst, game->carriages->registers, REQUEST_REGISTER, 0);
		CARRIAGE_LOCATION += REGISTR_SIZE;
	}
	else if (input_arg == CW_DIR_CODE)
	{
		cwReadFromArenaToBuf(read_dst, game->arena->field, CARRIAGE_LOCATION, DYNAMIC_SIZE_DIR);
		CARRIAGE_LOCATION += game->carriages->current_command->dir_size;
	}
	else if (input_arg == CW_IND_CODE)
	{
		save_point = CARRIAGE_LOCATION;
		cwReadFromArenaToBuf(game->arena->address_buf, game->arena->field, CARRIAGE_LOCATION, 2);
		cwConversionBytesToInt(game->arena->address_buf, &game->arena->short_value, 2);
		if (idx_mod == CW_TRUE)
		{
			CARRIAGE_LOCATION = (game->carriages->save_point + (game->arena->short_value % IDX_MOD)) % MEM_SIZE;
			cwReadFromArenaToBuf(read_dst, game->arena->field, CARRIAGE_LOCATION, 0);
		}
		else
		{
			CARRIAGE_LOCATION = (game->carriages->save_point + game->arena->short_value) % MEM_SIZE;
		}
		cwReadFromArenaToBuf(read_dst, game->arena->field, CARRIAGE_LOCATION, 0);
		CARRIAGE_LOCATION = save_point;
		CARRIAGE_LOCATION += IND_SIZE;
	}
}

void		live_exec(corewar_t *game)
{
	int		reference;
	int		input;

	cwTypeHandler					(game);
	cwReadOperation					(game, game->arena->value_buf1, CW_FALSE, FIRST_ARG);
	cwReadFromRegToBuf				(game->arena->value_buf2, game->carriages->registers, R1, 0);
	cwConversionBytesToInt			(game->arena->value_buf1, &input, 0);
	cwConversionBytesToInt			(game->arena->value_buf2, &reference, 0);
	if (-input == reference)
		game->arena->last_survivor	= game->carriages->owner;
	game->carriages->jump			= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION				= game->carriages->save_point;
	game->carriages->last_cycle		= game->arena->cycle_amount;
	game->arena->live_amount		+= 1;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		ld_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, game->arena->value_buf1, CW_TRUE, FIRST_ARG);
	cwWriteOperaion			(game, game->arena->value_buf1, CW_FALSE, SECOND_ARG);
	game->carriages->jump	= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION		= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		st_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, game->arena->value_buf1, CW_FALSE, FIRST_ARG);
	cwWriteOperaion			(game, game->arena->value_buf1, CW_TRUE, SECOND_ARG);
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

	ft_printf("Executing command: add\n");
	ft_printf("Before update: %d\n", game->carriages->current_location);
	print_arena(game);
	cwTypeHandler				(game);
	printf("one: %d two: %d three %d\n", game->carriages->current_command->first_arg, game->carriages->current_command->second_arg, game->carriages->current_command->third_arg);
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
	ft_printf("After update: %d\n", game->carriages->current_location);
	print_arena(game);
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
	ft_printf("After update: %d\n", game->carriages->current_location);
	print_arena(game);
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
	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &game->arena->tmp_value2, 0);
	if (game->carriages->carry)
		game->carriages->jump = game->arena->tmp_value2 % IDX_MOD;
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

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &first_arg, 0);
	cwConversionBytesToInt		(game->arena->value_buf2, &second_arg, 0);
	first_arg += second_arg;
	cwConversionIntToBytes		(game->arena->address_buf, &first_arg, 0);
	cwArgsHandler				(game, game->arena->address_buf, CW_WRITING_MODE, FALSE, THIRD_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void		sti_exec(corewar_t *game)
{
	int		second_arg;
	int		third_arg;
	int		total_address;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, TRUE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf2, CW_READING_MODE, TRUE, SECOND_ARG);
	cwArgsHandler				(game, game->arena->value_buf3, CW_READING_MODE, TRUE, THIRD_ARG);
	cwConversionBytesToInt		(game->arena->value_buf2, &second_arg, 0);
	cwConversionBytesToInt		(game->arena->value_buf3, &third_arg, 0);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	total_address = (CARRIAGE_LOCATION  + second_arg + third_arg) % IDX_MOD;
	cwWriteFromBufToArena		(game->arena->value_buf1, game->arena->field, total_address % MEM_SIZE, 0);
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void			fork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	copy_reg							(game->carriages->registers, new_carriage->registers, REG_NUMBER * REG_SIZE);
	new_carriage->id					= game->carriages->id;
	new_carriage->jump					= FALSE;
	new_carriage->owner					= game->carriages->owner;
	new_carriage->carry					= game->carriages->carry;
	new_carriage->last_cycle			= game->carriages->last_cycle;
	new_carriage->waiting_time			= FALSE;
	new_carriage->error_occured			= FALSE;
	new_carriage->current_command		= NULL;
	cwTypeHandler						(game);
	cwArgsHandler						(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwConversionBytesToInt				(game->arena->value_buf1, &game->arena->tmp_value1, 0);
	new_carriage->current_location 		= game->arena->tmp_value1 % IDX_MOD;
	new_carriage->prev					= game->arena->last_carriage;
	new_carriage->next					= game->arena->last_carriage->next;
	game->arena->last_carriage->next 	= new_carriage;
	game->arena->last_carriage			= new_carriage;
	game->carriages_amount				+= 1;
	game->carriages->jump				= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION					= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}

void	lld_exec(corewar_t *game)
{
	ft_printf("Executing command: lld\n");
	ft_printf("Before update: %d\n", game->carriages->current_location);
	print_arena(game);
	cwTypeHandler				(game);
	printf("one: %d two: %d three %d\n", game->carriages->current_command->first_arg, game->carriages->current_command->second_arg, game->carriages->current_command->third_arg);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwArgsHandler				(game, game->arena->value_buf1, CW_WRITING_MODE, FALSE, SECOND_ARG);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
	ft_printf("After update: %d\n", game->carriages->current_location);
	print_arena(game);
}

void	lldi_exec(corewar_t *game)
{
	int		first_arg;
	int		second_arg;
	int		total_address;

	ft_printf("Executing command: lldi\n");
	ft_printf("Before update: %d\n", game->carriages->current_location);
	print_arena(game);
	cwTypeHandler				(game);
	printf("one: %d two: %d three %d\n", game->carriages->current_command->first_arg, game->carriages->current_command->second_arg, game->carriages->current_command->third_arg);
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
	ft_printf("After update: %d\n", game->carriages->current_location);
	print_arena(game);
}

void	lfork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;
	int			total_address;

	ft_printf("Executing command: lfork\n");
	ft_printf("Before update: %d\n", game->carriages->current_location);
	print_arena(game);
	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
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
	ft_printf("After update: %d\n", game->carriages->current_location);
	print_arena(game);
}

void		aff_exec(corewar_t *game)
{
	int 	output;

	cwTypeHandler				(game);
	cwArgsHandler				(game, game->arena->value_buf1, CW_READING_MODE, FALSE, FIRST_ARG);
	cwConversionBytesToInt		(game->arena->value_buf1, &output, 0);
	printf("%c", output);
	game->carriages->jump		= CARRIAGE_LOCATION - game->carriages->save_point;
	CARRIAGE_LOCATION			= game->carriages->save_point;
	if (game->carriages->current_command->change_carry)
		check_carry(game->carriages->registers, &game->carriages->carry, REQUEST_REGISTER);
}