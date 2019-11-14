/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_command_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:36:54 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 18:38:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_put_param(t_command *p_command_instance,
							size_t attributes, void (*f)(t_corewar *))
{
	CO_ID_I = attributes >> 56 & 0xff;
	CO_ARGS_I = ((attributes >> 48 & 0xff) << 24) |
				((attributes >> 40 & 0xff) << 16) |
				((attributes >> 32 & 0xff) << 8);
	CO_CALLBACK_I = f;
	CO_DIR_SIZE_I = attributes >> 24 & 0xff;
	CO_TYPE_BYTE_I = attributes & 0x3f;
	CO_CHANGE_CARRY_I = attributes >> 16 & 0xff;
	CO_WAITING_TIME_I = attributes >> 6 & 0x3ff;
}

static int	cw_recognize_command3(t_command *p_c_i, int com, size_t at)
{
	if (com == CO_FORK)
		p_c_i->cw_put_param(p_c_i, at
	| (CO_FORK << 56) | (CW_DIR << 48) | (CW_SHDIR_CODE_SIZE << 24)
	| (CW_FALSE << 16) | (800 << 6) | (CW_FALSE), &fork_exec);
	else if (com == CO_LLD)
		p_c_i->cw_put_param(p_c_i, at
	| (CO_LLD << 56) | ((CW_DIR | CW_IND) << 48) | (CW_REG << 40)
	| (CW_DIR_CODE_SIZE << 24) | (CW_TRUE << 16) | (10 << 6)
	| (CW_TRUE), &lld_exec);
	else if (com == CO_LLDI)
		p_c_i->cw_put_param(p_c_i, at
	| (CO_LLDI << 56) | ((CW_REG | CW_DIR | CW_IND) << 48) | ((CW_REG
	| CW_DIR) << 40) | (CW_REG << 32) | (CW_SHDIR_CODE_SIZE << 24)
	| (CW_TRUE << 16) | (50 << 6) | (CW_TRUE), &lldi_exec);
	else if (com == CO_LFORK)
		p_c_i->cw_put_param(p_c_i, at
	| (CO_LFORK << 56) | (CW_DIR << 48) | (CW_SHDIR_CODE_SIZE << 24)
	| (1000 << 6), &lfork_exec);
	else if (com == CO_AFF)
		p_c_i->cw_put_param(p_c_i, at
	| (CO_AFF << 56) | (CW_REG << 48) | (CW_DIR_CODE_SIZE << 24)
	| (2 << 6) | (CW_TRUE), &aff_exec);
	return (1);
}

static int	cw_recognize_command2(t_command *p_c_i, int com, size_t at)
{
	if (com == CO_AND)
		p_c_i->cw_put_param(p_c_i, at | (CO_AND << 56) | ((CW_REG | CW_DIR
	| CW_IND) << 48) | ((CW_REG | CW_DIR | CW_IND) << 40) | (CW_REG << 32)
	| (4 << 24) | (CW_TRUE << 16) | (6 << 6) | (CW_TRUE), &and_exec);
	else if (com == CO_OR)
		p_c_i->cw_put_param(p_c_i, at | (CO_OR << 56) | ((CW_REG | CW_DIR
	| CW_IND) << 48) | ((CW_REG | CW_DIR | CW_IND) << 40) | (CW_REG << 32)
	| (4 << 24) | (CW_TRUE << 16) | (6 << 6) | (CW_TRUE), &or_exec);
	else if (com == CO_XOR)
		p_c_i->cw_put_param(p_c_i, at | (CO_XOR << 56) | ((CW_REG | CW_DIR
	| CW_IND) << 48) | ((CW_REG | CW_DIR | CW_IND) << 40) | (CW_REG << 32)
	| (4 << 24) | (CW_TRUE << 16) | (6 << 6) | (CW_TRUE), &xor_exec);
	else if (com == CO_ZJMP)
		p_c_i->cw_put_param(p_c_i, at | (CO_ZJMP << 56) | (CW_DIR << 48)
	| (CW_SHDIR_CODE_SIZE << 24) | (20 << 6), &zjmp_exec);
	else if (com == CO_LDI)
		p_c_i->cw_put_param(p_c_i, at | (CO_LDI << 56) | ((CW_REG | CW_DIR
	| CW_IND) << 48) | ((CW_REG | CW_DIR) << 40) | (CW_REG << 32)
	| (CW_SHDIR_CODE_SIZE << 24) | (25 << 6) | (CW_TRUE), &ldi_exec);
	else if (com == CO_STI)
		p_c_i->cw_put_param(p_c_i, at | (CO_STI << 56) | (CW_REG << 48)
	| ((CW_REG | CW_DIR | CW_IND) << 40) | ((CW_REG | CW_DIR) << 32)
	| (CW_SHDIR_CODE_SIZE << 24) | (25 << 6) | (CW_TRUE), &sti_exec);
	com > CO_STI ? cw_recognize_command3(p_c_i, com, at) : CW_FALSE;
	return (0);
}

static void	cw_recognize_command(t_command *p_command_instance, int command)
{
	size_t	attr;

	if (!(attr = 0) && command == CO_LIVE)
		p_command_instance->cw_put_param(p_command_instance, attr
	| (CO_LIVE << 56) | (CW_DIR << 48) | (CW_DIR_CODE_SIZE << 24)
	| (10 << 6), &live_exec);
	else if (command == CO_LD)
		p_command_instance->cw_put_param(p_command_instance, attr
	| (CO_LD << 56) | ((CW_DIR | CW_IND) << 48) | (CW_REG << 40)
	| (CW_FALSE << 32) | (CW_DIR_CODE_SIZE << 24) | (CW_TRUE << 16)
	| (5 << 6) | (CW_TRUE), &ld_exec);
	else if (command == CO_ST)
		p_command_instance->cw_put_param(p_command_instance, attr
	| (CO_ST << 56) | (CW_REG << 48) | ((CW_REG | CW_IND) << 40)
	| (CW_DIR_CODE_SIZE << 24) | (5 << 6) | (CW_TRUE), &st_exec);
	else if (command == CO_ADD)
		p_command_instance->cw_put_param(p_command_instance, attr
	| (CO_ADD << 56) | (CW_REG << 48) | (CW_REG << 40) | (CW_REG << 32)
	| (4 << 24) | (CW_TRUE << 16) | (10 << 6) | (CW_TRUE), &add_exec);
	else if (command == CO_SUB)
		p_command_instance->cw_put_param(p_command_instance, attr
	| (CO_SUB << 56) | (CW_REG << 48) | (CW_REG << 40) | (CW_REG << 32)
	| (4 << 24) | (CW_TRUE << 16) | (10 << 6) | (CW_TRUE), &sub_exec);
	else if (cw_recognize_command2(p_command_instance, command, attr))
		;
}

extern void	cw_command_functions_linker(t_command *p_command_instance)
{
	p_command_instance->cw_recognize = cw_recognize_command;
	p_command_instance->cw_put_param = cw_put_param;
}
