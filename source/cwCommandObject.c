/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/10 19:25:11 by vrichese         ###   ########.fr       */
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
	commandInstance->cwCallback		= f;
}

void	cwRecognizeCommand(command_t *commandInstance, int command)
{
	if (command == CW_LIVE)
		commandInstance->cwPutParam(commandInstance, CW_LIVE, CW_DIR, CW_FALSE, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 10, CW_FALSE, &liveExec);
	else if (command == CW_LD)
		commandInstance->cwPutParam(commandInstance, CW_LD, CW_DIR | CW_IND, CW_REG, CW_FALSE, CW_DIR_SIZE, CW_TRUE, 5, CW_TRUE, &ldExec);
	else if (command == CW_ST)
		commandInstance->cwPutParam(commandInstance, CW_ST, CW_REG, CW_REG | CW_IND, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 5, CW_TRUE, &stExec);
	else if (command == CW_ADD)
		commandInstance->cwPutParam(commandInstance, CW_ADD, CW_REG, CW_REG, CW_REG, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &addExec);
	else if (command == CW_SUB)
		commandInstance->cwPutParam(commandInstance, CW_SUB, CW_REG, CW_REG, CW_REG, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &subExec);
	else if (command == CW_AND)
		commandInstance->cwPutParam(commandInstance, CW_AND, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &andExec);
	else if (command == CW_OR)
		commandInstance->cwPutParam(commandInstance, CW_OR, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &orExec);
	else if (command == CW_XOR)
		commandInstance->cwPutParam(commandInstance, CW_XOR, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR | CW_IND, CW_REG, CW_DIR_SIZE, CW_TRUE, 6, CW_TRUE, &xorExec);
	else if (command == CW_ZJMP)
		commandInstance->cwPutParam(commandInstance, CW_ZJMP, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 20, CW_FALSE, &zjmpExec);
	else if (command == CW_LDI)
		commandInstance->cwPutParam(commandInstance, CW_LDI, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_REG, CW_SHORT_DIR_SIZE, CW_FALSE, 25, CW_TRUE, &ldiExec);
	else if (command == CW_STI)
		commandInstance->cwPutParam(commandInstance, CW_STI, CW_REG, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_SHORT_DIR_SIZE, CW_FALSE, 25, CW_TRUE, &stiExec);
	else if (command == CW_FORK)
		commandInstance->cwPutParam(commandInstance, CW_FORK, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 800, CW_FALSE, &forkExec);
	else if (command == CW_LLD)
		commandInstance->cwPutParam(commandInstance, CW_LLD, CW_DIR | CW_IND, CW_REG, CW_FALSE, CW_DIR_SIZE, CW_TRUE, 10, CW_TRUE, &lldExec);
	else if (command == CW_LLDI)
		commandInstance->cwPutParam(commandInstance, CW_LLDI, CW_REG | CW_DIR | CW_IND, CW_REG | CW_DIR, CW_REG, CW_SHORT_DIR_SIZE, CW_TRUE, 50, CW_TRUE, &lldiExec);
	else if (command == CW_LFORK)
		commandInstance->cwPutParam(commandInstance, CW_LFORK, CW_DIR, CW_FALSE, CW_FALSE, CW_SHORT_DIR_SIZE, CW_FALSE, 1000, CW_FALSE, &lforkExec);
	else if (command == CW_AFF)
		commandInstance->cwPutParam(commandInstance, CW_ZJMP, CW_REG, CW_FALSE, CW_FALSE, CW_DIR_SIZE, CW_FALSE, 20, CW_TRUE, &affExec);
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructorCommand(command_t **ppCommandInstance)
{
	(*ppCommandInstance)->id			= 0;
	(*ppCommandInstance)->firstArg		= 0;
	(*ppCommandInstance)->secondArg		= 0;
	(*ppCommandInstance)->thirdArg		= 0;
	(*ppCommandInstance)->dirSize		= 0;
	(*ppCommandInstance)->changeCarry	= 0;
	(*ppCommandInstance)->waitingTime	= 0;
	(*ppCommandInstance)->typeByte		= 0;
	(*ppCommandInstance)->cwCallback	= NULL;
}

static void	cwDestructorCommand(command_t **ppCommandInstance)
{
	free(*ppCommandInstance);
	*ppCommandInstance = NULL;
}

void	cwCreateInstanceCommand(command_t **ppCommandObj)
{
	if (!(*ppCommandObj = (command_t *)malloc(sizeof(ppCommandObj))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_COMMAND);
	(*ppCommandObj)->cwConstructorCommand	= (const void *)&cwConstructorCommand;
	(*ppCommandObj)->cwDestructorCommand	= (const void *)&cwDestructorCommand;
	(*ppCommandObj)->cwRecognizeCommand		= (const void *)&cwRecognizeCommand;
	(*ppCommandObj)->cwPutParam				= (const void *)&cwPutParam;
	(*ppCommandObj)->cwConstructorCommand	(ppCommandObj);
}

/*
**--------------------------------------------------------------------------------------
*/