/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/21 19:22:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

int		get_arg(corewar_t *game, int requesting_argument)
{
	int bytes_of_type;

	bytes_of_type = game->arena->field[game->carriages->current_location + 1];
	if (requesting_argument == FIRST_ARG)
		return ((bytes_of_type << 2) >> 6);
	else if (requesting_argument == SECOND_ARG)
		return ((bytes_of_type << 4) >> 6);
	else if (requesting_argument == THIRD_ARG)
		return ((bytes_of_type << 6) >> 6);
	else
		printf("Request of arg not valid\n"); exit(1);
}

void	live_exec(corewar_t *game)
{
	int live;
	int live2;

	game->carriages->last_live_loop = game->arena->check_amount;
	read_from_reg_to_buf(game->carriages, 1);
	live = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 1, 4);
	live2 = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	if (-live == live2)
		game->arena->last_survivor = game->c
}

void	ld_exec(corewar_t *game)
{
	if (get_arg(game, FIRST_ARG) == DIR_CODE)
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 4);
	else if (get_arg(game, FIRST_ARG) == IND_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
	}
	check_carry(game->carriages);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 6]);
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
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD);
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
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
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
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
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
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
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
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
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
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 6;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
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
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		right_operand = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 2;
	}
	result = left_operand ^ right_operand;
	conversetion_int_to_bytes(game->carriages->reg_buf, result);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
	check_carry(game->carriages);
}

void	zjmp_exec(corewar_t *game)
{
	//if (game->carriages->carry == 1)
	//{
//
	//	game->carriages->curre
	;
}

void	ldi_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	if (get_arg(game, FIRST_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 3;
	}
	else if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 4;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 2;
	}
	read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + (left_args + right_args) % IDX_MOD, 4);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
}

void	sti_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 3]);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 3, 2);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 5;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 3, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 5;
	}
	if (get_arg(game, THIRD_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, THIRD_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 4;
	}
	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
	write_from_buf_to_arena(game->carriages, game->arena->field, game->carriages->current_location + (left_args + right_args) % IDX_MOD);
}

void	fork_exec(corewar_t *game)
{
	;
}

void	lld_exec(corewar_t *game)
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
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2), 4);
		check_carry(game->carriages);
		write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + 6]);
	}
	else
		printf("Bug!\n");
}

void	lldi_exec(corewar_t *game)
{
	int left_args;
	int right_args;
	int step;

	if (get_arg(game, FIRST_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 2]);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 3;
	}
	else if (get_arg(game, FIRST_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 4;
	}
	else
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + 2, 2);
		read_from_arena_to_buf(game->carriages, game->arena->field,
		game->carriages->current_location + conversetion_bytes_to_int(game->carriages->reg_buf, 2) % IDX_MOD, 4);
		left_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 4;
	}
	if (get_arg(game, SECOND_ARG) == REG_CODE)
	{
		read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
		step += 1;
	}
	else if (get_arg(game, SECOND_ARG) == DIR_CODE)
	{
		read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + step, 2);
		right_args = conversetion_bytes_to_int(game->carriages->reg_buf, 2);
		step += 2;
	}
	read_from_arena_to_buf(game->carriages, game->arena->field, game->carriages->current_location + (left_args + right_args), 4);
	write_from_buf_to_reg(game->carriages, (int)game->arena->field[game->carriages->current_location + step]);
}

void	lfork_exec(corewar_t *game)
{
	;
}

void	aff_exec(corewar_t *game)
{
	int result;

	read_from_reg_to_buf(game->carriages, (int)game->arena->field[game->carriages->current_location + 1]);
	result = conversetion_bytes_to_int(game->carriages->reg_buf, 4);
	printf("%c", (char)result);
}