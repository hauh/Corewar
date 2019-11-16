/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:44:23 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 14:49:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	double_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'F' || SPEC == 'E' || SPEC == 'G' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & NUL) ? (*flags |= 48) : 0;
	!(*flags & POI) || *pre < 0 ? *pre = 6 : 0;
	*flags |= FLO;
	if (*flags & BL)
		print_double(va_arg(*list, long double), flags, wid, pre);
	else
		print_double(va_arg(*list, double), flags, wid, pre);
}

void	hexadouble_handler(va_list *list, size_t *flags, int *wid, int *pre)
{
	(SPEC) == 'A' ? *flags |= BIG : 0;
	!(*flags & BIA) && (*flags & NUL) ? (*flags |= 48) : 0;
	*flags |= FLO;
	if (*flags & BL)
		print_hexadouble(va_arg(*list, long double), flags, wid, pre);
	else
		print_hexadouble(va_arg(*list, double), flags, wid, pre);
}

void	inf_handler(size_t *flags)
{
	if (*flags & NNN)
	{
		if (!(*flags & BIG) && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'n')
			&& (BUFF.g_buff[BUFF.g_count++] = 'a'))
			BUFF.g_buff[BUFF.g_count++] = 'n';
		else if (EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'N'))
		{
			BUFF.g_buff[BUFF.g_count++] = 'A';
			BUFF.g_buff[BUFF.g_count++] = 'N';
		}
	}
	else if (*flags & INF)
	{
		if (!(*flags & BIG) && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'i'))
		{
			BUFF.g_buff[BUFF.g_count++] = 'n';
			BUFF.g_buff[BUFF.g_count++] = 'f';
		}
		else if (*flags & BIG && EJECT(3) && (BUFF.g_buff[BUFF.g_count++] = 'I')
				&& (BUFF.g_buff[BUFF.g_count++] = 'N'))
			BUFF.g_buff[BUFF.g_count++] = 'F';
	}
}

void	roundd2(char **str, int n)
{
	while ((*str)[n + 1] > '9' && (*str)[n + 1] != '.')
	{
		(*str)[n + 1] -= 10;
		(*str)[n] != '.' ? ++(*str)[n] : ++(*str)[n - 1];
		n--;
	}
	while (n > 0 && (*str)[n] > '9')
	{
		(*str)[n] -= 10;
		++(*str)[n - 1];
		(*str)[n - 1] < '0' ? (*str)[n - 1] += '0' : 0;
		n--;
	}
}

void	roundd(char **str, int *pre, int start, int end)
{
	int	flag;
	int	n;

	n = start + (*pre > 0 ? *pre : 0);
	flag = 0;
	if ((*str)[n + 2] >= '5')
	{
		if ((*str)[n + 2] == '5')
			while (end > n + 2)
				if ((*str)[end--] > '0' && (flag = 1))
					break ;
		if ((*str)[n + 2] > '5')
			(*str)[n + 1] != '.' ? ++(*str)[n + 1] : ++(*str)[n];
		else if ((*str)[n + 2] == '5')
		{
			if ((*str)[n + 1] != '.')
				(*str)[n + 1] % 2 != 0 || flag ? ++(*str)[n + 1] : 0;
			else
				(*str)[n] % 2 != 0 || flag ? ++(*str)[n] : 0;
		}
	}
	roundd2(str, n);
}
