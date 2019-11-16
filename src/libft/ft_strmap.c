/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:51:44 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 23:04:18 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *fresh;
	char *fresh0;

	if (!s || !f)
		return (NULL);
	if (!(fresh = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	fresh0 = fresh;
	while (*s)
	{
		*fresh = f(*s);
		++fresh;
		++s;
	}
	*fresh = 0;
	return (fresh0);
}
