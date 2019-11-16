/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:22:48 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 16:10:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long tmp;

	if (!n)
		write(fd, "0", 1);
	else
	{
		tmp = (n < 0) ? -1 : 1;
		while (n)
		{
			tmp = tmp * 10 + n % 10;
			n /= 10;
		}
		if (tmp < 0)
		{
			write(fd, "-", 1);
			tmp = ~tmp + 1;
		}
		while (tmp != 1)
		{
			n = tmp % 10 + '0';
			write(fd, &n, 1);
			tmp /= 10;
		}
	}
}
