/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/22 21:54:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

player_t	*find_player(corewar_t *game, int id)
{
	player_t	*iter;

	iter = game->players;
	while (iter)
	{
		if (iter->id == id)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void	copy_reg(carriage_t *from, carriage_t *to)
{
	int iter;

	iter = 0;
	if (!(from->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE * REG_NUMBER)))
		error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	while (iter < REG_NUMBER * REG_SIZE)
	{
		from->registers[iter] = to->registers[iter];
		++iter;
	}
}

int		get_arg(unsigned char byte_of_types, int requesting_argument)
{
	if (requesting_argument == FIRST_ARG)
		return ((byte_of_types << 2) >> 6);
	else if (requesting_argument == SECOND_ARG)
		return ((byte_of_types << 4) >> 6);
	else if (requesting_argument == THIRD_ARG)
		return ((byte_of_types << 6) >> 6);
	return (0);
}

void	live_exec(corewar_t *game)
{
	int	step;
	int live;

	game->arena->live_amount_in_ctd += 1;
	game->carriages->last_live_loop = game->arena->loop_amount;
	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, R1, 0);
	conversetionBytesToInt(game->carriages->value_buf, &game->carriages->tmp_value, 0);
	readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 0);
	conversetionBytesToInt(game->carriages->value_buf, &live, 0);
	if (game->carriages->tmp_value == -live)
		game->arena->last_survivor = find_player(game, live);
	step += DIRECTION_SIZE;
	game->carriages->next_command_location = step;
	printf("Live\n");
}

void	ld_exec(corewar_t *game)
{
	int	step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		step += IND_SIZE;
	}
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	game->carriages->next_command_location = step;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	printf("Ld\n");
}

void	st_exec(corewar_t *game)
{
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		writeFromBufToArena(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step), 0);
		step += IND_SIZE;
	}
	game->carriages->next_command_location = step;
	printf("St\n");
}

void	add_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	left_operand = 0;
	right_operand = 0;
	result = 0;
	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
	step += REGISTR_SIZE;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
	step += REGISTR_SIZE;
	result = left_operand + right_operand;
	conversetionIntToBytes(game->carriages->value_buf, &result, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	game->carriages->next_command_location = step;
	printf("Add\n");
}

void	sub_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	left_operand = 0;
	right_operand = 0;
	result = 0;
	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
	step += REGISTR_SIZE;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
	step += REGISTR_SIZE;
	result = left_operand - right_operand;
	conversetionIntToBytes(game->carriages->value_buf, &result, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	game->carriages->next_command_location = step;
	printf("Sub\n");
}

void	and_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += IND_SIZE;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += IND_SIZE;
	}
	result = left_operand & right_operand;
	conversetionIntToBytes(game->carriages->value_buf, &result, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	game->carriages->next_command_location = step;
	printf("And\n");
}

void	or_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG)], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += IND_SIZE;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += IND_SIZE;
	}
	result = left_operand | right_operand;
	conversetionIntToBytes(game->carriages->value_buf, &result, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	game->carriages->next_command_location = step;
	printf("Or\n");
}

void	xor_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_operand, 0);
		step += IND_SIZE;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 4);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (game->carriages->tmp_value % IDX_MOD)) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_operand, 0);
		step += IND_SIZE;
	}
	result = left_operand ^ right_operand;
	conversetionIntToBytes(game->carriages->value_buf, &result, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	game->carriages->next_command_location = step;
	printf("Xor\n");
}

void	zjmp_exec(corewar_t *game)
{
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (game->carriages->carry_flag)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->value_buf, &game->carriages->tmp_value, 2);
		step = game->carriages->tmp_value % IDX_MOD;
	}
	else
		step += 2;
	game->carriages->next_command_location = step;
	printf("Zjmp\n");
}

void	ldi_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG)], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step), 2);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 2);
		step += 2;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + game->carriages->tmp_value) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += 2;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 2);
		step += 2;
	}
	readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + ((left_args + right_args) % IDX_MOD)) % MEM_SIZE, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	game->carriages->next_command_location = step;
	printf("Ldi\n");
}

void	sti_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types + REGISTR_SIZE;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 2);
		step += 2;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + game->carriages->tmp_value) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += 2;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], THIRD_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], THIRD_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 2);
		step += 2;
	}
	readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + ((left_args + right_args) % IDX_MOD)) % MEM_SIZE, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + 1) % MEM_SIZE], 0);
	game->carriages->next_command_location = step;
	printf("Sdi\n");
}

void	fork_exec(corewar_t *game)
{
	//carriage_t	*new_carriage;
	//carriage_t	*iter;
//
	//if (!(new_carriage		= (carriage_t *)malloc(sizeof(carriage_t))))
	//	error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	//if (!(new_carriage->reg_buf = (unsigned char *)malloc(sizeof(unsigned char))))
	//	error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	//ft_memset(new_carriage, 0, REG_SIZE);
	//read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 1, 2);
	//new_carriage->id					= game->carriages->id;
	//new_carriage->player_id				= game->carriages->id;
	//new_carriage->carry_flag			= game->carriages->carry_flag;
	//new_carriage->waiting_time			= FALSE;
	//new_carriage->last_live_loop		= game->carriages->last_live_loop;
	//new_carriage->next_command_location	= FALSE;
	//new_carriage->current_location		= conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD;
	//new_carriage->current_command		= NULL;
	//iter = game->carriages;
	//while (iter->prev)
	//	iter = iter->prev;
	//new_carriage->prev = NULL;
	//new_carriage->next = iter;
	//iter->prev = new_carriage;
	//copy_reg(game->carriages, new_carriage);
	printf("Fork\n");
}

void	lld_exec(corewar_t *game)
{
	int	step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 0);
		step += game->carriages->current_command->dir_size;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + game->carriages->tmp_value) % MEM_SIZE, 0);
		step += IND_SIZE;
	}
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	game->carriages->next_command_location = step;
	check_carry(game->carriages->value_buf, &game->carriages->carry_flag);
	printf("Lld\n");
}

void	lldi_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG)], FIRST_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step), 2);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 2);
		step += 2;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], FIRST_ARG) == IND_CODE)
	{
		readFromArenaToBuf(game->carriages->address_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->address_buf, &game->carriages->tmp_value, 2);
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + game->carriages->tmp_value) % MEM_SIZE, 0);
		conversetionBytesToInt(game->carriages->value_buf, &left_args, 0);
		step += 2;
	}
	if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == REG_CODE)
	{
		readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 0);
		step += REGISTR_SIZE;
	}
	else if (get_arg(game->arena->field[(game->carriages->current_location + MOVE_TO_ARG) % MEM_SIZE], SECOND_ARG) == DIR_CODE)
	{
		readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + step) % MEM_SIZE, 2);
		conversetionBytesToInt(game->carriages->value_buf, &right_args, 2);
		step += 2;
	}
	readFromArenaToBuf(game->carriages->value_buf, game->arena->field, (game->carriages->current_location + (left_args + right_args)) % MEM_SIZE, 0);
	writeFromBufToReg(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	step += REGISTR_SIZE;
	game->carriages->next_command_location = step;
	printf("Ldi\n");
}

void	lfork_exec(corewar_t *game)
{
	//carriage_t	*new_carriage;
	//carriage_t	*iter;
//
	//if (!(new_carriage		= (carriage_t *)malloc(sizeof(carriage_t))))
	//	error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	//if (!(new_carriage->reg_buf = (unsigned char *)malloc(sizeof(unsigned char))))
	//	error_catcher(MEMORY_ALLOC_ERROR, CARRIAGE);
	//ft_memset(new_carriage, 0, REG_SIZE);
	//read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 1, 2);
	//new_carriage->id					= game->carriages->id;
	//new_carriage->player_id				= game->carriages->id;
	//new_carriage->carry_flag			= game->carriages->carry_flag;
	//new_carriage->waiting_time			= FALSE;
	//new_carriage->last_live_loop		= game->carriages->last_live_loop;
	//new_carriage->next_command_location	= FALSE;
	//new_carriage->current_location		= game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2);
	//new_carriage->current_command		= NULL;
	//iter = game->carriages;
	//while (iter->prev)
	//	iter = iter->prev;
	//new_carriage->prev = NULL;
	//new_carriage->next = iter;
	//iter->prev = new_carriage;
	//copy_reg(game->carriages, new_carriage);
	printf("Lfork\n");
}

void	aff_exec(corewar_t *game)
{
	int result;
	int step;

	step = MOVE_TO_ARG + game->carriages->current_command->availability_types;
	readFromRegToBuf(game->carriages->value_buf, game->carriages->registers, game->arena->field[(game->carriages->current_location + step) % MEM_SIZE], 0);
	conversetionBytesToInt(game->carriages->value_buf, &result, 0);
	printf("%c", (char)result);
}