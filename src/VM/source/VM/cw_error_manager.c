/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:00:50 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/13 20:43:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_error_catcher(const char *obj_name, const char *reason,
							const char *file, int line)
{
	ft_printf("\n###ERROR### FOR SOME REASONS AN ERROR OCCURED ###ERROR###\n");
	ft_printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
	if (VERBOSE)
	{
		ft_printf("FILE: %s\n", file);
		ft_printf("LINE: %d\n", line);
		ft_printf("OBJ: %s\n", obj_name);
	}
	ft_printf("INFO: (\"%s\")\n", reason);
	exit(1);
}
