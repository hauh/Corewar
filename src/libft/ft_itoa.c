/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:10:42 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 16:41:09 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	size;
	long			tmp;
	char			*fresh;

	tmp = n;
	size = (n <= 0);
	while (n)
	{
		n /= 10;
		++size;
	}
	if (!(fresh = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	*(fresh + size) = 0;
	*fresh = (tmp < 0 ? '-' : '0');
	if (tmp < 0)
		tmp = ~tmp + 1;
	while (tmp)
	{
		--size;
		*(fresh + size) = tmp % 10 + '0';
		tmp /= 10;
	}
	return (fresh);
}
