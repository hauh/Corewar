/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:58:52 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 16:47:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	const char *begin;

	begin = src;
	if (dst && src)
	{
		if (n)
		{
			while ((n - 1) && *src)
			{
				*dst = *src;
				++dst;
				++src;
				--n;
			}
			*dst = 0;
		}
		while (*src)
			++src;
	}
	return (src - begin);
}
