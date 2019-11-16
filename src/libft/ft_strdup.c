/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 21:18:19 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 17:47:41 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	char *new;
	char *new0;

	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	new0 = new;
	while (*s)
	{
		*new = *s;
		++new;
		++s;
	}
	*new = 0;
	return (new0);
}
