/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:31:34 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 17:48:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimc(char const *s, char c)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	while (*s == c)
		++s;
	while (s[i])
		++i;
	while (i && s[i - 1] == c)
		--i;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	*(new + i) = 0;
	while (i)
	{
		--i;
		*(new + i) = *(s + i);
	}
	return (new);
}
