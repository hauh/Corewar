/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:13:32 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 17:53:10 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, char const *src, size_t n)
{
	char *dst0;

	dst0 = dst;
	while (*dst)
		++dst;
	while (*src && n)
	{
		--n;
		*dst = *src;
		++dst;
		++src;
	}
	*dst = 0;
	return (dst0);
}
