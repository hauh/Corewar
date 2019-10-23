/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCommandObject.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/23 20:20:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cwPutParam(command_t *pCommandInstance, int id, int firstArg, int secondArg, int thirdArg, int dirSize, int changeCarry, int waitingTime, int typeByte, void (*f)(corewar_t *))
{
	pCommandInstance->id			= id;
	pCommandInstance->args			= (firstArg << 24) | (secondArg << 16) | (thirdArg << 8);
	pCommandInstance->dirSize		= dirSize;
	pCommandInstance->changeCarry	= changeCarry;
	pCommandInstance->waitingTime	= waitingTime;
	pCommandInstance->typeByte		= typeByte;
	pCommandInstance->cwCallback	= f;
}

static void	cwRecognizeCommand(command_t *pCommandInstance, int command)
{
	if (command == CW_LIVE)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LIVE,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 10, CW_FALSE, &liveExec);
	else if (command == CW_LD)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LD,	CW_DIR | CW_IND,			CW_REG,						CW_FALSE,			CW_DIR_CODE_SIZE, CW_TRUE, 5, CW_TRUE, &ldExec);
	else if (command == CW_ST)
		pCommandInstance->cwPutParam(pCommandInstance, CW_ST,	CW_REG,						CW_REG | CW_IND,			CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 5, CW_TRUE, &stExec);
	else if (command == CW_ADD)
		pCommandInstance->cwPutParam(pCommandInstance, CW_ADD,	CW_REG,						CW_REG,						CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &addExec);
	else if (command == CW_SUB)
		pCommandInstance->cwPutParam(pCommandInstance, CW_SUB,	CW_REG,						CW_REG,						CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &subExec);
	else if (command == CW_AND)
		pCommandInstance->cwPutParam(pCommandInstance, CW_AND,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &andExec);
	else if (command == CW_OR)
		pCommandInstance->cwPutParam(pCommandInstance, CW_OR,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &orExec);
	else if (command == CW_XOR)
		pCommandInstance->cwPutParam(pCommandInstance, CW_XOR,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &xorExec);
	else if (command == CW_ZJMP)
		pCommandInstance->cwPutParam(pCommandInstance, CW_ZJMP,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 20, CW_FALSE, &zjmpExec);
	else if (command == CW_LDI)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LDI,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,			CW_REG,				CW_SHDIR_CODE_SIZE, CW_FALSE, 25, CW_TRUE, &ldiExec);
	else if (command == CW_STI)
		pCommandInstance->cwPutParam(pCommandInstance, CW_STI,	CW_REG,						CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,	CW_SHDIR_CODE_SIZE, CW_FALSE, 25, CW_TRUE, &stiExec);
	else if (command == CW_FORK)
		pCommandInstance->cwPutParam(pCommandInstance, CW_FORK,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 800, CW_FALSE, &forkExec);
	else if (command == CW_LLD)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LLD,	CW_DIR | CW_IND,			CW_REG,						CW_FALSE,			CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &lldExec);
	else if (command == CW_LLDI)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LLDI,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,			CW_REG,				CW_SHDIR_CODE_SIZE, CW_TRUE, 50, CW_TRUE, &lldiExec);
	else if (command == CW_LFORK)
		pCommandInstance->cwPutParam(pCommandInstance, CW_LFORK, CW_DIR,					CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 1000, CW_FALSE, &lforkExec);
	else if (command == CW_AFF)
		pCommandInstance->cwPutParam(pCommandInstance, CW_AFF,	CW_REG,						CW_FALSE,					CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 20, CW_TRUE, &affExec);
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructorCommand(command_t **ppCommandInstance)
{
	(*ppCommandInstance)->id			= 0;
	(*ppCommandInstance)->args			= 0;
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

extern void	cw_create_instance_command(command_t **ppCommandObj)
{
	if (!(*ppCommandObj = (command_t *)malloc(sizeof(command_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_COMMAND);
	(*ppCommandObj)->cwConstructorCommand	= cwConstructorCommand;
	(*ppCommandObj)->cwDestructorCommand	= cwDestructorCommand;
	(*ppCommandObj)->cwRecognizeCommand		= cwRecognizeCommand;
	(*ppCommandObj)->cwPutParam				= cwPutParam;
	(*ppCommandObj)->cwConstructorCommand	(ppCommandObj);
}

/*
**--------------------------------------------------------------------------------------
*/