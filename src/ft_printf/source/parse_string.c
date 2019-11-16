/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:11:36 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/28 13:55:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		width_collector(const char **str, va_list *list, size_t *flags,
		int *wid)
{
	int check;

	if (**str == '*')
	{
		*wid = va_arg(*list, int);
		if (*wid < 0)
		{
			*wid *= -1;
			!(*flags & BIA) ? (*flags |= BIA) : 0;
		}
		(*str)++;
	}
	else
	{
		if ((check = ft_atoi(*str)) > 0)
			*wid = check;
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

int		precision_collector(const char **str, va_list *list, size_t *flags,
		int *pre)
{
	*flags |= POI;
	(*str)++;
	if (**str == '*')
	{
		*pre = va_arg(*list, int);
		*pre < 0 ? *flags ^= POI : 0;
		(*str)++;
	}
	else
	{
		*pre = ft_atoi(*str);
		while (**str >= 48 && **str <= 57 && !CONV(**str))
			(*str)++;
	}
	return (1);
}

void	file_descriptor(const char **str, va_list *list)
{
	*str += 3;
	if (**str == '*')
		BUFF.g_fd = va_arg(*list, int);
	else if (**str >= '0' && **str <= '9')
		BUFF.g_fd = ft_atoi(*str);
	while (**str && *(*str - 1) != '}')
		(*str)++;
}

void	set_colour(char *col)
{
	ft_strcmp(col, "red") == 0 ? BUFF.g_bytes += write(1, "\033[0;31m", 7) : 0;
	if (ft_strcmp(col, "bold red") == 0)
		BUFF.g_bytes += write(1, "\033[1;31m", 7);
	else if (ft_strcmp(col, "green") == 0)
		BUFF.g_bytes += write(1, "\033[0;32m", 7);
	else if (ft_strcmp(col, "bold green") == 0)
		BUFF.g_bytes += write(1, "\033[1;32m", 7);
	else if (ft_strcmp(col, "yellow") == 0)
		BUFF.g_bytes += write(1, "\033[0;33m", 7);
	else if (ft_strcmp(col, "bold yellow") == 0)
		BUFF.g_bytes += write(1, "\033[1;33m", 7);
	else if (ft_strcmp(col, "blue") == 0)
		BUFF.g_bytes += write(1, "\033[0;34m", 7);
	else if (ft_strcmp(col, "bold blue") == 0)
		BUFF.g_bytes += write(1, "\033[1;34m", 7);
	else if (ft_strcmp(col, "magenta") == 0)
		BUFF.g_bytes += write(1, "\033[0;35m", 7);
	else if (ft_strcmp(col, "bold magenta") == 0)
		BUFF.g_bytes += write(1, "\033[1;35m", 7);
	else if (ft_strcmp(col, "cyan") == 0)
		BUFF.g_bytes += write(1, "\033[0;36m", 7);
	else if (ft_strcmp(col, "bold cyan") == 0)
		BUFF.g_bytes += write(1, "\033[1;36m", 7);
	else if (ft_strcmp(col, "eoc") == 0 && EJECT(__BUFF_SIZE__))
		BUFF.g_bytes += write(1, "\033[0m", 4);
}

void	colour_chooser(const char **str)
{
	char	*colour;
	char	*tmp;
	int		size;

	size = 32;
	if (!(tmp = (char *)malloc(sizeof(char) * size)))
	{
		BUFF.g_error = -1;
		return ;
	}
	colour = tmp;
	*str += 2;
	while (**str && **str != '}' && size-- > 0)
		*tmp++ = *(*str)++;
	**str ? (*str)++ : 0;
	if (size == 0 && (BUFF.g_error = -1))
		return ;
	*tmp = 0;
	set_colour(colour);
	free(colour);
}
