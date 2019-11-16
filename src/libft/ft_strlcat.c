/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:32:54 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 20:02:51 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t n)
{
	size_t len;

	len = ft_strlen(dst);
	if (n < len)
		return (n + ft_strlen(src));
	dst += len;
	n -= len;
	while (*src)
	{
		if (n > 1)
		{
			--n;
			*dst = *src;
			++dst;
		}
		++src;
		++len;
	}
	*dst = 0;
	return (len);
}
