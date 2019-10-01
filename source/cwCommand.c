/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/01 17:18:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cwPutOption(size_t *option, size_t waiting_time, size_t dir_size, size_t id, size_t first_arg, size_t second_arg, size_t third_arg, size_t change_carry, size_t availability_types)
{
	*option 					|= PUT_WAITING_TIME(waiting_time);
	*option 					|= PUT_DIR_SIZE(dir_size);
	*option 					|= PUT_ID(id);
	*option 					|= PUT_FIRST_ARG(first_arg);
	*option 					|= PUT_SECOND_ARG(second_arg);
	*option 					|= PUT_THIRD_ARG(third_arg);
	*option 					|= PUT_CHANGE_CARRY(change_carry);
	*option 					|= PUT_AVAI_TYPES(availability_types);
}

void			cwInitializationCommand(command_t *command, size_t option, void *function)
{
	command->id					= GET_ID(option);
	command->first_arg			= GET_FIRST_ARG(option);
	command->second_arg			= GET_SECOND_ARG(option);
	command->third_arg			= GET_THIRD_ARG(option);
	command->dir_size			= GET_DIR_SIZE(option);
	command->change_carry		= GET_CHANGE_CARRY(option);
	command->waiting_time		= GET_WAITING_TIME(option);
	command->availability_types	= GET_AVAI_TYPES(option);
	command->function			= (void (*)(corewar_t *))function;
}

void			cwInitializationCommands(corewar_t *game)
{
	command_t	*new_command;
	size_t		option;
	int			iter;

	iter = 1;
	while (iter <= COMMAND_AMOUNT)
	{
		if (!(new_command = (command_t *)malloc(sizeof(command_t))))
			cwErrorCatcher(CW_NOT_ALLOCATED, CW_COMMAND);
		game->commands[iter] = new_command;
		option = 0;
		if (iter == LIVE)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, LIVE, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &live_exec);
		}
		else if (iter == LD)
		{
			cwPutOption(&option, 5, DIRECTION_SIZE, LD, TRUE, TRUE, FALSE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &ld_exec);
		}
		else if (iter == ST)
		{
			cwPutOption(&option, 5, DIRECTION_SIZE, ST, TRUE, TRUE, FALSE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &st_exec);
		}
		else if (iter == ADD)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, ADD, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &add_exec);
		}
		else if (iter == SUB)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, SUB, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &sub_exec);
		}
		else if (iter == AND)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, AND, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &and_exec);
		}
		else if (iter == OR)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, OR, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &or_exec);
		}
		else if (iter == XOR)
		{
			cwPutOption(&option, 6, DIRECTION_SIZE, XOR, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &xor_exec);
		}
		else if (iter == ZJMP)
		{
			cwPutOption(&option, 20, SHORT_DIR_SIZE, ZJMP, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &zjmp_exec);
		}
		else if (iter == LDI)
		{
			cwPutOption(&option, 25, SHORT_DIR_SIZE, LDI, TRUE, TRUE, TRUE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &ldi_exec);
		}
		else if (iter == STI)
		{
			cwPutOption(&option, 25, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &sti_exec);
		}
		else if (iter == FORK)
		{
			cwPutOption(&option, 800, SHORT_DIR_SIZE, FORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &fork_exec);
		}
		else if (iter == LLD)
		{
			cwPutOption(&option, 10, DIRECTION_SIZE, LLD, TRUE, TRUE, FALSE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &lld_exec);
		}
		else if (iter == LLDI)
		{
			cwPutOption(&option, 50, SHORT_DIR_SIZE, STI, TRUE, TRUE, TRUE, TRUE, TRUE);
			cwInitializationCommand(new_command, option, &lldi_exec);
		}
		else if (iter == LFORK)
		{
			cwPutOption(&option, 1000, SHORT_DIR_SIZE, LFORK, TRUE, FALSE, FALSE, FALSE, FALSE);
			cwInitializationCommand(new_command, option, &lfork_exec);
		}
		else if (iter == AFF)
		{
			cwPutOption(&option, 2, DIRECTION_SIZE, AFF, TRUE, FALSE, FALSE, FALSE, TRUE);
			cwInitializationCommand(new_command, option, &aff_exec);
		}
		++iter;
	}
}