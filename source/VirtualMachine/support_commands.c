/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/19 20:33:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void	ld_exec(corewar_t *game)
{
	if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 4);
		check_carry(game->carriages);
		write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 6]);
	}
	else if (get_arg(game, SECOND_ARG) == IND_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		check_carry(game->carriages);
		write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 6]);
	}
	else
		printf("Bug!\n");
}

void	st_exec(corewar_t *game)
{
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 3]);
	}
	else if (get_arg(game, SECOND_ARG) == IND_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 3, 2);
		write_from_buf_to_arena(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD);
	}
}

void	add_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;

	left_operand = 0;
	right_operand = 0;
	result = 0;
	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
	left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 3]);
	right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	result = left_operand + right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 4]);
	check_carry(game->carriages);
}

void	sub_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;

	left_operand = 0;
	right_operand = 0;
	result = 0;
	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
	left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 3]);
	right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	result = left_operand - right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 4]);
	check_carry(game->carriages);
}

void	and_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	if (get_arg(game, FIRST_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 3;
	}
	else if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 2;
	}
	result = left_operand & right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
	check_carry(game->carriages);
}

void	or_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	if (get_arg(game, FIRST_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 3;
	}
	else if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 2;
	}
	result = left_operand | right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
	check_carry(game->carriages);
}

void	xor_exec(corewar_t *game)
{
	int left_operand;
	int right_operand;
	int result;
	int step;

	if (get_arg(game, FIRST_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 3;
	}
	else if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		(game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2)) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 2;
	}
	result = left_operand ^ right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
	check_carry(game->carriages);
}