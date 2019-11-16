/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:11:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/27 16:38:40 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		print_sig_dig(intmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[20];
	int		j;

	j = 0;
	nbr < 0 ? *flags |= NEG : 0;
	nbr == 0 && !(*flags & POI && *pre == 0) ? tra[j++] = '0' : 0;
	while (nbr != 0)
	{
		tra[j++] = nbr % 10 * ((*flags & NEG) > 0 ? -1 : 1) + '0';
		nbr /= 10;
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '0';
	while (--j >= 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = tra[j];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = (*flags << 56) >> 56;
}

void		print_uns_dig(uintmax_t nbr, size_t *flags, int *wid, int *pre)
{
	char	tra[64];
	int		j;

	if (!(j = 0) && nbr == 0 && !(*flags & POI && *pre == 0) && !(*flags & PTR)
		&& (*flags |= ZER))
		tra[j++] = '0';
	nbr == 0 && BASE == 16 && !(*flags & PTR) ? (*flags |= ZER) : 0;
	nbr == 0 && *flags & PTR ? tra[j++] = '0' : 0;
	nbr == 0 && *flags & PTR && (*flags & POI && *pre == 0) ? j-- : 0;
	while (nbr != 0)
	{
		if (nbr % BASE > 9)
			tra[j++] = nbr % BASE + ((*flags & BIG) ? 55 : 87);
		else
			tra[j++] = nbr % BASE + '0';
		nbr /= BASE;
	}
	adjustment_wid_pre(flags, wid, pre, j);
	fill_width(flags, wid);
	while ((*pre)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = '0';
	while (--j >= 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = tra[j];
	while ((*wid)-- > 0 && EJECT(1))
		g_buff__.g_buff[g_buff__.g_count++] = SIGN;
}

void		rec_to_n(int *n)
{
	EJECT(__BUFF_SIZE__);
	*n = BUFF.g_bytes;
}
