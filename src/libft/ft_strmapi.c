/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:06 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 18:10:49 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*fresh;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	if (!(fresh = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	*(fresh + i) = 0;
	while (i)
	{
		--i;
		*(fresh + i) = f(i, s[i]);
	}
	return (fresh);
}
