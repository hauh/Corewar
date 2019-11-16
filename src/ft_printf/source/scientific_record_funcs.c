/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scientific_record_funcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:47:44 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/07 12:57:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		swimming_dot2(char **str, int *pre, int end)
{
	int i;
	int swim;
	int expo;

	expo = 0;
	while ((*str)[expo] <= '0' && expo < end)
		expo++;
	if ((*str)[expo] < '1' || (*str)[expo] > '9')
		return (0);
	((*str)[1] = (*str)[expo]);
	*pre > 0 ? ((*str)[2] = '.') : 0;
	i = 3;
	swim = expo + 1;
	while (swim < end)
		(*str)[i++] = (*str)[swim++];
	while (i < end)
		(*str)[i++] = '0';
	expo -= 2;
	(*str)[2] != '.' ? expo += 1 : 0;
	expo *= -1;
	return (expo);
}

int		swimming_dot(char **str, int *pre, int sta, int end)
{
	int swim;
	int expo;

	expo = 0;
	if ((*str)[1] != '0')
	{
		while ((*str)[expo] != '.' && expo < sta)
			expo++;
		swim = expo + 1;
		while (--swim > 2)
			(*str)[swim] = (*str)[swim - 1];
		*pre > 0 || (*str)[2] != '.' ? (*str)[swim] = '.' : 0;
		expo -= 2;
	}
	else
		expo = swimming_dot2(str, pre, end);
	return (expo);
}

int		add_expo(char **str, size_t *flags, t_bits *tally, int *pre)
{
	int c;

	c = (*tally).middle + (pre > 0 ? *pre : 0);
	(*str)[c++] = 'e';
	*flags & BIG ? (*str)[c - 1] = 'E' : 0;
	(*str)[c++] = '+';
	(*tally).tmp_ex < 0 ? ((*tally).tmp_ex *= -1) && ((*str)[c - 1] = '-') : 0;
	if ((*tally).tmp_ex >= 10 && (*tally).tmp_ex < 100)
	{
		(*str)[c++] = (*tally).tmp_ex / 10 + '0';
		(*str)[c++] = (*tally).tmp_ex % 10 + '0';
	}
	else if ((*tally).tmp_ex >= 100)
	{
		(*str)[c++] = (*tally).tmp_ex / 100 + '0';
		(*str)[c++] = ((*tally).tmp_ex % 100) / 10 + '0';
		(*str)[c++] = ((*tally).tmp_ex % 100) % 10 + '0';
		(*pre)++;
	}
	else
	{
		(*str)[c++] = '0';
		(*str)[c++] = (*tally).tmp_ex + '0';
	}
	return (1);
}

int		scientific_record(char **str, t_bits *tally, size_t *flags, int *pre)
{
	int count;

	count = (*tally).tmp_ex;
	(*tally).exhibi = swimming_dot(str, pre, (*tally).middle, (*tally).middle
	+ (*tally).size);
	(*tally).middle = 3;
	roundd(str, pre, (*tally).middle - 2, (*tally).middle + (*tally).size +
	((*tally).exhibi > 0 ? (*tally).exhibi : 0));
	if ((*str)[0] > '0')
	{
		(*str)[2] = (*str)[1];
		(*str)[1] = '.';
		(*tally).exhibi++;
		(*tally).middle = 2;
	}
	(*tally).tmp_ex = (*tally).exhibi;
	while ((*tally).exhibi++ < *pre)
		(*str)[count++] = '0';
	*pre <= 0 && !(*flags & HAS) ? (*tally).middle-- : 0;
	add_expo(str, flags, tally, pre);
	return ((*tally).middle + *pre);
}
