/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:53:32 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 16:43:15 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *s)
{
	char	*begin;

	begin = s;
	if (s)
	{
		if (ft_islower(*s))
			*s -= 32;
		++s;
		while (*s)
		{
			if (ft_islower(*s) && !ft_isalnum(*(s - 1)))
				*s -= 32;
			else if (ft_isupper(*s) && ft_isalnum(*(s - 1)))
				*s += 32;
			++s;
		}
	}
	return (begin);
}
