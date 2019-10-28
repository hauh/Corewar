/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:13:19 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/28 19:40:06 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_put_param(command_t *p_command_instance, int id, int first_arg, int second_arg, int third_arg, int dir_size, int change_carry, int waiting_time, int type_byte, void (*f)(corewar_t *))
{
	p_command_instance->id = id;
	p_command_instance->args = (first_arg << 24) | (second_arg << 16) | (third_arg << 8);
	p_command_instance->dir_size = dir_size;
	p_command_instance->change_carry = change_carry;
	p_command_instance->waiting_time = waiting_time;
	p_command_instance->type_byte = type_byte;
	p_command_instance->cw_callback = f;
}

static void	cw_recognize_command(command_t *p_command_instance, int command)
{
	if (command == CW_LIVE)
		p_command_instance->cw_put_param(p_command_instance, CW_LIVE,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 10, CW_FALSE, &liveExec);
	else if (command == CW_LD)
		p_command_instance->cw_put_param(p_command_instance, CW_LD,	CW_DIR | CW_IND,			CW_REG,						CW_FALSE,			CW_DIR_CODE_SIZE, CW_TRUE, 5, CW_TRUE, &ldExec);
	else if (command == CW_ST)
		p_command_instance->cw_put_param(p_command_instance, CW_ST,	CW_REG,						CW_REG | CW_IND,			CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 5, CW_TRUE, &stExec);
	else if (command == CW_ADD)
		p_command_instance->cw_put_param(p_command_instance, CW_ADD,	CW_REG,						CW_REG,						CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &addExec);
	else if (command == CW_SUB)
		p_command_instance->cw_put_param(p_command_instance, CW_SUB,	CW_REG,						CW_REG,						CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &subExec);
	else if (command == CW_AND)
		p_command_instance->cw_put_param(p_command_instance, CW_AND,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &andExec);
	else if (command == CW_OR)
		p_command_instance->cw_put_param(p_command_instance, CW_OR,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &orExec);
	else if (command == CW_XOR)
		p_command_instance->cw_put_param(p_command_instance, CW_XOR,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR | CW_IND,	CW_REG,				CW_DIR_CODE_SIZE, CW_TRUE, 6, CW_TRUE, &xorExec);
	else if (command == CW_ZJMP)
		p_command_instance->cw_put_param(p_command_instance, CW_ZJMP,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 20, CW_FALSE, &zjmpExec);
	else if (command == CW_LDI)
		p_command_instance->cw_put_param(p_command_instance, CW_LDI,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,			CW_REG,				CW_SHDIR_CODE_SIZE, CW_FALSE, 25, CW_TRUE, &ldiExec);
	else if (command == CW_STI)
		p_command_instance->cw_put_param(p_command_instance, CW_STI,	CW_REG,						CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,	CW_SHDIR_CODE_SIZE, CW_FALSE, 25, CW_TRUE, &stiExec);
	else if (command == CW_FORK)
		p_command_instance->cw_put_param(p_command_instance, CW_FORK,	CW_DIR,						CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 800, CW_FALSE, &forkExec);
	else if (command == CW_LLD)
		p_command_instance->cw_put_param(p_command_instance, CW_LLD,	CW_DIR | CW_IND,			CW_REG,						CW_FALSE,			CW_DIR_CODE_SIZE, CW_TRUE, 10, CW_TRUE, &lldExec);
	else if (command == CW_LLDI)
		p_command_instance->cw_put_param(p_command_instance, CW_LLDI,	CW_REG | CW_DIR | CW_IND,	CW_REG | CW_DIR,			CW_REG,				CW_SHDIR_CODE_SIZE, CW_TRUE, 50, CW_TRUE, &lldiExec);
	else if (command == CW_LFORK)
		p_command_instance->cw_put_param(p_command_instance, CW_LFORK, CW_DIR,					CW_FALSE,					CW_FALSE,			CW_SHDIR_CODE_SIZE, CW_FALSE, 1000, CW_FALSE, &lforkExec);
	else if (command == CW_AFF)
		p_command_instance->cw_put_param(p_command_instance, CW_AFF,	CW_REG,						CW_FALSE,					CW_FALSE,			CW_DIR_CODE_SIZE, CW_FALSE, 2, CW_TRUE, &affExec);
}

static void	cw_constructor(command_t **pp_command_instance)
{
	(*pp_command_instance)->id = 0;
	(*pp_command_instance)->args = 0;
	(*pp_command_instance)->dir_size = 0;
	(*pp_command_instance)->change_carry = 0;
	(*pp_command_instance)->waiting_time = 0;
	(*pp_command_instance)->type_byte = 0;
	(*pp_command_instance)->cw_callback = NULL;
}

static void	cw_destructor(command_t **pp_command_instance)
{
	free(*pp_command_instance);
	*pp_command_instance = NULL;
}

extern void	cw_create_instance_command(command_t **pp_command_obj)
{
	if (!(*pp_command_obj = (command_t *)malloc(sizeof(command_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_COMMAND);
	(*pp_command_obj)->cw_constructor = cw_constructor;
	(*pp_command_obj)->cw_destructor = cw_destructor;
	(*pp_command_obj)->cw_recognize = cw_recognize_command;
	(*pp_command_obj)->cw_put_param = cw_put_param;
	(*pp_command_obj)->cw_constructor(pp_command_obj);
}
