/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser_betw_f_e.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:39:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/07 12:57:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		pass_zero(char **med, size_t *flags, int *pre, int sta)
{
	int n;

	n = sta + (*pre > 0 ? *pre : 0);
	if (!(*flags & HAS))
	{
		while ((*med)[n--] == '0')
			(*pre)--;
		(*med)[n + 1] == '.' ? (*pre)-- : 0;
	}
}

void		my_roundd(char **med, t_bits *tally, int sta)
{
	int		i;

	i = sta - 1;
	if ((*med)[i] != '.')
	{
		++(*med)[i];
		while ((*med)[i] >= 16)
		{
			(*med)[i - 1] != '.' ? ++(*med)[i - 1] : ++(*med)[i - 2] && i--;
			(*med)[i] -= 16;
			i--;
		}
	}
	else
	{
		++(*med)[i - 1];
		if ((*med)[i - 1] >= 16)
		{
			(*tally).exhibi += 4;
			(*med)[i - 1] -= 16;
		}
	}
}

int			expo(char **med, int sta, int end)
{
	int expo;
	int i;

	i = 1;
	expo = 0;
	(*med)[0] > '0' ? i = 0 : 0;
	if ((*med)[i] != '0')
	{
		while ((*med)[expo] != '.' && expo < sta)
			expo++;
		expo -= 2;
	}
	else
	{
		while ((*med)[expo] <= '0' && expo < end)
			expo++;
		if ((*med)[expo] < '1' || (*med)[expo] > '9')
			return (0);
		expo -= 2;
		(*med)[2] != '.' ? expo += 1 : 0;
		expo *= -1;
	}
	return (expo);
}

void		choose_betw_f_g2(char **str, t_bits *tally, size_t *flags, int *pre)
{
	int i;
	int count;

	count = (*tally).tmp_ex;
	*pre > 0 ? *pre -= 1 : 0;
	(*tally).exhibi = swimming_dot(str, pre, (*tally).middle,
	(*tally).middle + (*tally).size);
	(*tally).tmp_ex = (*tally).exhibi;
	(*tally).middle = 3;
	roundd(str, pre, (*tally).middle - 2, (*tally).middle + (*tally).size +
	((*tally).exhibi > 0 ? (*tally).exhibi : 0));
	if ((*str)[0] > '0')
	{
		(*str)[2] = (*str)[1];
		(*str)[1] = '.';
		(*tally).tmp_ex++;
		(*tally).middle = 2;
	}
	i = 0;
	while (i++ < *pre)
		(*str)[count++] = '0';
	pass_zero(str, flags, pre, (*tally).middle - 1);
	(*tally).exhibi != 0 ? add_expo(str, flags, tally, pre) &&
	((*pre) += 4) : 0;
}

int			choose_betw_f_e(char **str, t_bits *tally, size_t *flags, int *pre)
{
	int		i;
	int		cou;

	cou = (*tally).tmp_ex;
	(*tally).exhibi = expo(str, (*tally).middle, (*tally).middle +
	(*tally).size);
	if ((*tally).exhibi < *pre && (*tally).exhibi >= -4)
	{
		*pre > 0 ? *pre -= ((*tally).exhibi + 1) : 0;
		roundd(str, pre, ((*tally).middle - 2), ((*tally).middle +
		(*tally).size));
		if ((*str)[0] > '0')
			(*pre)--;
		i = 0;
		while (i++ < *pre)
			(*str)[cou++] = '0';
		pass_zero(str, flags, pre, (*tally).middle - 1);
	}
	else
		choose_betw_f_g2(str, tally, flags, pre);
	return ((*tally).middle + *pre);
}
