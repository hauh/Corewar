/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCallback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:45:28 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/09 21:27:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		live_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadFromRegToBuf		(CW_BUFFER_SET[CW_VALUE_BUF_2]->data, CW_CARRIAGE_REGISTERS, R1, CW_INT_BIAS);
	cwConversionBytesToInt	(CW_BUFFER_SET[CW_VALUE_BUF_2]->data, &CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value, CW_INT_BIAS, CW_INT);
	if (CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value == -CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value)
		game->arena->last_survivor	= game->carriages->owner;
	game->carriages->jump			= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION			= CW_CARRIAGE_SAVE_POINT;
	game->carriages->last_cycle		= game->arena->cycle_amount;
	game->arena->live_amount		+= 1;
}

void		ld_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_TRUE, CW_FIRST_ARG);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_SECOND_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		st_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_TRUE, CW_SECOND_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
}

void		add_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_FALSE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value + CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	cwConversionIntToBytes	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, &CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		sub_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_FALSE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value - CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	cwConversionIntToBytes	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, &CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		and_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_FALSE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value & CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	cwConversionIntToBytes	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, &CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		or_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_FALSE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value | CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	cwConversionIntToBytes	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, &CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		xor_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_FALSE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value ^ CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	cwConversionIntToBytes	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, &CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void		zjmp_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	if (game->carriages->carry)
		game->carriages->jump = CW_BUFFER_SET[CW_VALUE_BUF_1]->short_value % IDX_MOD;
	else
		game->carriages->jump = CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION = CW_CARRIAGE_SAVE_POINT;
}

void		ldi_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_TRUE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_TRUE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = 0;
	if (CW_FIRST_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_1]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value;
	if (CW_SECOND_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = CW_CARRIAGE_SAVE_POINT + CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value % IDX_MOD;
	cwReadFromArenaToBuf	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, CW_GAME_ARENA, CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value % MEM_SIZE, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
}

void		sti_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_TRUE, CW_SECOND_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_TRUE, CW_THIRD_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value = 0;
	if (CW_SECOND_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	if (CW_THIRD_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_3]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value;
	CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value = CW_CARRIAGE_SAVE_POINT + CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value % IDX_MOD;
	cwWriteFromBufToArena	(CW_BUFFER_SET[CW_VALUE_BUF_1]->data, CW_GAME_ARENA, CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value % MEM_SIZE, CW_INT_BIAS);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
}

void			fork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	cwCopyReg						(CW_CARRIAGE_REGISTERS, new_carriage->registers, REG_NUMBER * REG_SIZE);
	new_carriage->id				= game->carriages->id;
	new_carriage->jump				= CW_FALSE;
	new_carriage->owner				= game->carriages->owner;
	new_carriage->carry				= game->carriages->carry;
	new_carriage->last_cycle		= game->carriages->last_cycle;
	new_carriage->waiting_time		= CW_FALSE;
	new_carriage->current_location 	= CW_FALSE;
	new_carriage->current_command	= NULL;
	cwTypeHandler					(game);
	cwReadOperation					(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	new_carriage->current_location 	= CW_BUFFER_SET[CW_VALUE_BUF_1]->short_value % IDX_MOD;
	new_carriage->prev				= game->arena->last_carriage;
	new_carriage->next				= game->arena->last_carriage->next;
	game->arena->last_carriage->next= new_carriage;
	game->arena->last_carriage		= new_carriage;
	game->carriages_amount			+= 1;
	game->carriages->jump			= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION			= CW_CARRIAGE_SAVE_POINT;
}

void	lld_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_SECOND_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void	lldi_exec(corewar_t *game)
{
	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_TRUE, CW_FIRST_ARG);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_2], CW_TRUE, CW_SECOND_ARG);
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = 0;
	if (CW_FIRST_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_1]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_1]->int_value;
	if (CW_SECOND_ARG == CW_DIR_CODE)
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->short_value;
	else
		CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value += CW_BUFFER_SET[CW_VALUE_BUF_2]->int_value;
	CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value = (CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value + CW_CARRIAGE_SAVE_POINT);
	cwReadFromArenaToBuf	(CW_BUFFER_SET[CW_VALUE_BUF_3]->data, CW_GAME_ARENA, CW_BUFFER_SET[CW_VALUE_BUF_3]->int_value % MEM_SIZE, CW_INT_BIAS);
	cwWriteOperation		(game, CW_BUFFER_SET[CW_VALUE_BUF_3], CW_FALSE, CW_THIRD_ARG);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
	cwCheckCarry(CW_CARRIAGE_REGISTERS, &game->carriages->carry, CW_REQUESTING_REGISTER);
}

void	lfork_exec(corewar_t *game)
{
	carriage_t	*new_carriage;

	if (!(new_carriage = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	if (!(new_carriage->registers = (unsigned char *)malloc(sizeof(unsigned char) * REG_NUMBER * REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	cwCopyReg						(CW_CARRIAGE_REGISTERS, new_carriage->registers, REG_NUMBER * REG_SIZE);
	new_carriage->id				= game->carriages->id;
	new_carriage->jump				= CW_FALSE;
	new_carriage->owner				= game->carriages->owner;
	new_carriage->carry				= game->carriages->carry;
	new_carriage->last_cycle		= game->carriages->last_cycle;
	new_carriage->waiting_time		= CW_FALSE;
	new_carriage->current_location 	= CW_FALSE;
	new_carriage->current_command	= NULL;
	cwTypeHandler					(game);
	cwReadOperation					(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	new_carriage->current_location 	= CW_BUFFER_SET[CW_VALUE_BUF_1]->short_value % MEM_SIZE;
	new_carriage->prev				= game->arena->last_carriage;
	new_carriage->next				= game->arena->last_carriage->next;
	game->arena->last_carriage->next= new_carriage;
	game->arena->last_carriage		= new_carriage;
	game->carriages_amount			+= 1;
	game->carriages->jump			= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION			= CW_CARRIAGE_SAVE_POINT;
}

void		aff_exec(corewar_t *game)
{
	int 	iter;

	cwTypeHandler			(game);
	cwReadOperation			(game, CW_BUFFER_SET[CW_VALUE_BUF_1], CW_FALSE, CW_FIRST_ARG);
	iter = 0;
	while (iter < REG_SIZE)
		printf("%02x ", CW_BUFFER_SET[CW_VALUE_BUF_1]->data[iter++]);
	game->carriages->jump	= CW_CARRIAGE_LOCATION - CW_CARRIAGE_SAVE_POINT;
	CW_CARRIAGE_LOCATION	= CW_CARRIAGE_SAVE_POINT;
}