/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:36:35 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 14:49:21 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	constructor(size_t *flags)
{
	if (*flags & NEG && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '-';
	if (*flags & HAS && BASE == 8 && !(*flags & ZER) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '0';
	if (!(*flags & NEG) && *flags & PLU && (BASE == 10 || *flags & FLO) &&
		!(*flags & NNN) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = '+';
	if (!(*flags & NEG) && !(*flags & PLU) && *flags & SPA && (BASE == 10
		|| *flags & FLO) && !(*flags & NNN) && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = ' ';
	if ((((*flags & HAS && BASE == 16 && !(*flags & (BIG | ZER))) ||
	*flags & PTR) && EJECT(2)) || (SPEC == 'a' && !(*flags & (INF | NNN))))
	{
		BUFF.g_buff[BUFF.g_count++] = '0';
		BUFF.g_buff[BUFF.g_count++] = 'x';
	}
	else if ((*flags & HAS && BASE == 16 && !(*flags & ZER)
		&& EJECT(2)) || (SPEC == 'A' && !(*flags & (INF | NNN))))
	{
		BUFF.g_buff[BUFF.g_count++] = '0';
		BUFF.g_buff[BUFF.g_count++] = 'X';
	}
	else if (*flags & HAS && BASE == 2 && EJECT(2) &&
		(BUFF.g_buff[BUFF.g_count++] = '0'))
		BUFF.g_buff[BUFF.g_count++] = *flags & BIG ? 'B' : 'b';
}

void	adjustment_wid_pre(size_t *flags, int *wid, int *pre, int len)
{
	!(*flags & FLO) || *flags & INF || *flags & NNN ? *pre -= len : 0;
	*flags & NEG ? (*wid)-- : 0;
	*flags & INF || *flags & NNN ? (*wid) -= 3 : 0;
	(SPEC == 'e' || SPEC == 'E') && !(*flags & (INF | NNN)) ? *wid -= 4 : 0;
	BASE == 8 && *flags & HAS && !(*flags & ZER) ? (*pre)-- : 0;
	*wid -= len > 0 ? len : 0;
	*wid -= *pre > 0 && !(*flags & FLO) ? *pre : 0;
	if (*flags & SPA && !(*flags & PLU) && !(*flags & NEG) && !(*flags & PTR)
		&& !(*flags & NNN) && BASE != 8 && BASE != 16)
		*wid -= 1;
	if (*flags & PLU && !(*flags & (NEG | NNN)) && (BASE == 10 || *flags & FLO))
		*wid -= 1;
	if (SIGN == 32)
	{
		*flags & HAS && BASE == 8 && !(*flags & (ZER | FLO)) ? *wid -= 1 : 0;
		*wid -= (*flags & HAS && (BASE == 16 || BASE == 2) && !(*flags & ZER)
		&& !(*flags & FLO)) ? 2 : 0;
		*wid -= (SPEC == 'a' || SPEC == 'A') && !(*flags & (NNN | INF)) ? 2 : 0;
	}
	else
	{
		if ((*flags & HAS && !(*flags & FLO) && !(*flags & ZER) && BASE != 10)
			|| ((SPEC == 'a' || SPEC == 'A') && !(*flags & (INF | NNN))))
			*wid -= ((BASE == 8) ? 1 : 2);
	}
}

void	fill_width(size_t *flags, int *wid)
{
	if ((*flags & INF || *flags & NNN) && shift(flags, 8, 'r'))
		*flags |= 32;
	if (!(*flags & BIA))
	{
		if (SIGN == 32)
		{
			while ((*wid)-- > 0 && EJECT(1))
				BUFF.g_buff[BUFF.g_count++] = SIGN;
			constructor(flags);
		}
		else
		{
			constructor(flags);
			while ((*wid)-- > 0 && EJECT(1))
				BUFF.g_buff[BUFF.g_count++] = SIGN;
		}
	}
	else
		constructor(flags);
}

void	zeroing_buff(int *wid_pre)
{
	BUFF.g_count = 0;
	BUFF.g_bytes = 0;
	BUFF.g_fd = 1;
	BUFF.g_error = 0;
	wid_pre[0] = 0;
	wid_pre[1] = 0;
}

int		shift(size_t *flags, int howmuch, char direction)
{
	if (direction == 'l')
	{
		*flags <<= howmuch;
		*flags >>= howmuch;
	}
	else if (direction == 'r')
	{
		*flags >>= howmuch;
		*flags <<= howmuch;
	}
	return (1);
}
