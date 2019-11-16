/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:55:36 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 18:05:46 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *dst0;

	dst0 = dst;
	while (*src && n)
	{
		--n;
		*dst = *src;
		++dst;
		++src;
	}
	while (n)
	{
		--n;
		*dst = 0;
		++dst;
	}
	return (dst0);
}
