/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:53:37 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 18:08:23 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	while (n)
	{
		--n;
		*(unsigned char *)dst = *(unsigned char *)src;
		if (*(unsigned char *)dst == (unsigned char)c)
			return (dst + 1);
		++dst;
		++src;
	}
	return (NULL);
}
