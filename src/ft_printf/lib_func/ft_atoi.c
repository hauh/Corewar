/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:53:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/05/30 18:28:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int							ft_atoi(const char *str)
{
	int						minus;
	int						res;
	size_t					check;

	minus = 1;
	res = 0;
	check = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = -1;
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - '0');
		check = (check * 10) + (*str++ - '0');
		if (check > 9223372036854775807)
		{
			if (minus == 1)
				return (-1);
			if (minus == -1)
				return (0);
		}
	}
	return (res * minus);
}
