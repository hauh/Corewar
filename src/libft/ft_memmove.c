/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:35:37 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 18:04:28 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *s;
	char *d;

	if (src != dst)
	{
		d = (char *)dst;
		s = (char *)src;
		if (src > dst)
			while (n)
			{
				--n;
				*d = *s;
				++d;
				++s;
			}
		else
			while (n)
			{
				--n;
				*(d + n) = *(s + n);
			}
	}
	return (dst);
}
