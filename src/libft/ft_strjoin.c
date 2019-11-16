/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:54:58 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 15:37:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	char	*fresh0;

	if (!s1 || !s2)
		return (NULL);
	fresh = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!fresh)
		return (NULL);
	fresh0 = fresh;
	while (*s1)
	{
		*fresh = *s1;
		++fresh;
		++s1;
	}
	while (*s2)
	{
		*fresh = *s2;
		++fresh;
		++s2;
	}
	*fresh = 0;
	return (fresh0);
}
