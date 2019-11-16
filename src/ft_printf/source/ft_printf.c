/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:33:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 20:16:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_buff_manage g_buff__;

int			eject(void)
{
	if (!BUFF.g_error)
		BUFF.g_bytes += write(BUFF.g_fd, BUFF.g_buff, BUFF.g_count);
	else
		return (0);
	BUFF.g_count = 0;
	return (1);
}

void		ever_handler(va_list *list, size_t *flags, int wid, int pre)
{
	if (SPEC == 'c' || SPEC == 'C' || SPEC == '%')
		char_handler(list, flags, &wid);
	else if (SPEC == 's' || SPEC == 'S')
		string_handler(list, flags, &wid, &pre);
	else if (SPEC == 'd' || SPEC == 'D' || SPEC == 'i')
		decimal_handler(list, flags, &wid, &pre);
	else if (SPEC == 'x' || SPEC == 'X' || SPEC == 'p')
		hexadecimal_handler(list, flags, &wid, &pre);
	else if (SPEC == 'f' || SPEC == 'F' || SPEC == 'e')
		double_handler(list, flags, &wid, &pre);
	else if (SPEC == 'E' || SPEC == 'g' || SPEC == 'G')
		double_handler(list, flags, &wid, &pre);
	else if (SPEC == 'u' || SPEC == 'U')
		unsigned_decimal_handler(list, flags, &wid, &pre);
	else if (SPEC == 'o' || SPEC == 'O')
		octal_handler(list, flags, &wid, &pre);
	else if (SPEC == 'b' || SPEC == 'B')
		binary_handler(list, flags, &wid, &pre);
	else if (SPEC == 'a' || SPEC == 'A')
		hexadouble_handler(list, flags, &wid, &pre);
	else if (SPEC == 'r' || SPEC == 'k')
		date_nprint(list, flags, &wid, &pre);
	else if (SPEC == 'n')
		rec_to_n(va_arg(*list, int *));
}

int			length_modifier_collector(const char **str, size_t *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		!(*flags & (J | ZZZ)) && shift(flags, 8, 'l') ? *flags |= HH : 0;
	else if (**str == 'l' && *(*str + 1) == 'l')
		!(*flags & (J | ZZZ)) && shift(flags, 8, 'l') ? *flags |= LL : 0;
	else if (**str == 'h' && *(*str - 1) != 'h' && *(*str + 1) != 'h')
		!(*flags & (J | ZZZ)) && shift(flags, 8, 'l') ? *flags |= H : 0;
	else if (**str == 'l' && *(*str - 1) != 'l' && *(*str + 1) != 'l')
		!(*flags & (J | ZZZ)) && shift(flags, 8, 'l') ? *flags |= L : 0;
	else if (**str == 'L' && shift(flags, 8, 'l'))
		*flags |= BL;
	else if (**str == 'j' && shift(flags, 8, 'l'))
		*flags |= J;
	else if (**str == 'z' && shift(flags, 8, 'l'))
		*flags |= ZZZ;
	else if (**str == 't' && shift(flags, 8, 'l'))
		*flags |= T;
	else
		return (0);
	return (1);
}

void		flags_collector(const char **str, va_list *list, size_t *flags,
			int *wi)
{
	while (!CONV(**str) && !(*flags & UND))
	{
		if (**str == '-')
			*flags |= BIA;
		else if (**str == '+')
			*flags |= PLU;
		else if (**str == ' ')
			*flags |= SPA;
		else if (**str == '#')
			*flags |= HAS;
		else if (**str == '0' && (*flags |= NUL))
			*flags |= 48;
		else if (**str == '.' && precision_collector(str, list, flags, &wi[1]))
			continue;
		else if (((**str >= 48 && **str <= 57) || **str == '*') &&
				width_collector(str, list, flags, &wi[0]))
			continue;
		else if (length_modifier_collector(str, flags))
			;
		else if (**str != 'h' && **str != 'l' && (*flags |= UND))
			print_any_char(**str, flags, &wi[0]);
		(*str)++;
	}
	(*flags & BIA || *flags & POI) && shift(flags, 8, 'r') ? *flags |= 32 : 0;
	*flags |= (**str) << 16;
}

int			ft_printf(const char *format, ...)
{
	va_list	listv;
	size_t	flags;
	int		w[2];

	va_start(listv, format);
	zeroing_buff(&w[0]);
	while (*format)
		if (*format == '%' && !(flags = 0) && format++ && (flags |= 32))
		{
			flags_collector(&format, &listv, &flags, &w[0]);
			if (flags & UND)
				continue;
			*format && format++ ? ever_handler(&listv, &flags, w[0], w[1]) : 0;
			if (g_buff__.g_error == -1)
				return (-1);
		}
		else if (*format == '@' && *(format + 1) == '{')
			colour_chooser(&format);
		else if (*format == '>' && *(format + 1) == '>' && *(format + 2) == '{')
			file_descriptor(&format, &listv);
		else if (EJECT(1))
			g_buff__.g_buff[g_buff__.g_count++] = *format++;
	va_end(listv);
	eject();
	return (g_buff__.g_bytes);
}
