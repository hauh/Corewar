/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/06 16:56:36 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cwPutParam(command_t *commandInstance, int id, int firstArg, int secondArg, int thirdArg, int dirSize, int changeCarry, int waitingTime, int typeByte, const void (*f)(corewar_t *))
{
	commandInstance->id				= id;
	commandInstance->firstArg		= firstArg;
	commandInstance->secondArg		= secondArg;
	commandInstance->thirdArg		= thirdArg;
	commandInstance->dirSize		= dirSize;
	commandInstance->changeCarry	= changeCarry;
	commandInstance->waitingTime	= waitingTime;
	commandInstance->typeByte		= typeByte;
	commandInstance->cwCallBack		= f;
}

void	cwRecognizeCommand(command_t *commandInstance, int command)
{
	if (command == CW_LIVE)
		commandInstance->cwPutParam(commandInstance, CW_LIVE, CW_DIR, CW_FALSE, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 10, CW_FALSE, &live_exec);
	else if (command == CW_LD)
		commandInstance->cwPutParam(commandInstance, CW_LD, CW_DIR | CW_IND, CW_REG, CW_FALSE, CW_DIR_SIZE, CW_TRUE, 5, CW_TRUE, &ld_exec);
	else if (command == CW_ST)
		commandInstance->cwPutParam(commandInstance, CW_ST, CW_REG, CW_REG | CW_IND, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 5, CW_TRUE, &st_exec);
	else if (command == CW_ADD)
		commandInstance->cwPutParam(commandInstance, CW_ADD, CW_REG, CW_REG, CW_REG, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &add_exec);
	else if (command == CW_SUB)
		commandInstance->cwPutParam(commandInstance, CW_SUB, CW_REG, CW_REG, CW_REG, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &sub_exec);
	else if (command = CW_AND)
		commandInstance->cwPutParam(commandInstance, CW_AND, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &and_exec);
	else if (command == CW_OR)
		commandInstance->cwPutParam(commandInstance, CW_OR, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &or_exec);
	else if (command == CW_XOR)
		commandInstance->cwPutParam(commandInstance, CW_XOR, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &xor_exec);
	else if (command == CW_ZJMP)
		commandInstance->cwPutParam(commandInstance, CW_ZJMP, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 20, CW_FALSE, &zjmp_exec);
	else if (command == CW_LDI)
		commandInstance->cwPutParam(commandInstance, CW_LDI, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_REG, CW_SHORT_DIR_SIZE, CW_FALSE, 25, CW_TRUE, &ldi_exec);
	else if (command == CW_STI)
		commandInstance->cwPutParam(commandInstance, CW_STI, CW_REG, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_SHORT_DIR_SIZE, CW_FALSE, 25, CW_TRUE, &sti_exec);
	else if (command == CW_FORK)
		commandInstance->cwPutParam(commandInstance, CW_FORK, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 800, CW_FALSE, &fork_exec);
	else if (command == CW_LLD)
		commandInstance->cwPutParam(commandInstance, CW_LLD, CW_DIR | CW_IND, CW_REG, CW_FALSE, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &lld_exec);
	else if (command == CW_LLDI)
		commandInstance->cwPutParam(commandInstance, CW_LLDI, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_REG, CW_SHORT_DIR_SIZE, CW_TRUE, 50, CW_TRUE, &lldi_exec);
	else if (command == CW_LFORK)
		commandInstance->cwPutParam(commandInstance, CW_LFORK, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 1000, CW_FALSE, &lfork_exec);
	else if (command == CW_AFF)
		commandInstance->cwPutParam(commandInstance, CW_ZJMP, CW_REG, CW_FALSE, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 20, CW_TRUE, &aff_exec);
}

void	cwConstructorCommand(command_t *commandInstance, int option, void *callFunction)
{
	commandInstance->id					= 0;
	commandInstance->firstArg			= 0;
	commandInstance->secondArg			= 0;
	commandInstance->thirdArg			= 0;
	commandInstance->dirSize			= 0;
	commandInstance->changeCarry		= 0;
	commandInstance->waitingTime		= 0;
	commandInstance->typeByte			= 0;
	commandInstance->cwCallBack			= NULL;
	commandInstance->cwPutParam			= &cwPutParam;
	commandInstance->cwRecognizeCommand = &cwRecognizeCommand;
}

void	cwDestructorCommand(command_t *commandInstance)
{
	free(commandInstance);
}

void	cwCreateInstanceCommand(command_t **commandObj)
{
	if (!(*commandObj = (command_t *)malloc(sizeof(commandObj))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_COMMAND);
	(*commandObj)->cwConstructorCommand	= &cwConstructorCommand;
	(*commandObj)->cwDestructorCommand	= &cwDestructorCommand;
}