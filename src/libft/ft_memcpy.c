/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:17:58 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 18:04:35 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;

	if (dst != src)
	{
		s = (unsigned const char *)src;
		d = (unsigned char *)dst;
		while (n)
		{
			--n;
			*d = *s;
			++d;
			++s;
		}
	}
	return (dst);
}
