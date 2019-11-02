/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_buffer_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:16:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/02 16:27:28 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_erase_data(t_buffer *p_buffer_instance)
{
	ft_memset(BU_DATA, 0, CW_REG_SIZE);
}

extern void	cw_buffer_functions_linker(t_buffer *p_buffer_instance)
{
	p_buffer_instance->cw_erase_data = cw_erase_data;
}
