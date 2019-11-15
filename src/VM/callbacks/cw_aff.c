/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:30:05 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 15:31:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	aff_exec(t_corewar *p_game_obj)
{
	GA_WORK_UNIT_O->cw_parse_types(GA_WORK_UNIT_O, GA_ARENA_OBJ_O);
	if (GA_WORK_UNIT_O->error_ocurred)
		return ;
	GA_WORK_UNIT_O->cw_read_operation(GA_WORK_UNIT_O, GA_ARENA_OBJ_O,
		p_game_obj->AR_VALUE_BUF_1_O, GA_FIRST_ARG);
	if (p_game_obj->aff_hide)
		ft_printf("%c", p_game_obj->AR_VALUE_BUF_1_O->s_types.char_value);
}
