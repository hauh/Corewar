/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:22:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 23:16:47 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *fresh;

	if (!s)
		return (NULL);
	if (!(fresh = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	*(fresh + len) = 0;
	s += start + len;
	while (len)
	{
		--len;
		--s;
		*(fresh + len) = *s;
	}
	return (fresh);
}
