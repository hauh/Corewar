/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:03:03 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 21:59:05 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *s0;

	s0 = s;
	while (*s)
		++s;
	if (!c)
		return ((char *)s);
	while (s != s0)
	{
		--s;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
