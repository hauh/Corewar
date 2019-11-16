/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:39:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 17:26:12 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new;

	len = ft_strlen(s);
	if (n > len)
		n = len;
	if (!(new = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	*(new + n) = 0;
	while (n)
	{
		--n;
		*(new + n) = *(s + n);
	}
	return (new);
}
