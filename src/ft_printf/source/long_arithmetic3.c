/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:09:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/07 12:19:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int					compute_nbr(long double nbr)
{
	nbr *= 16;
	nbr -= (int)nbr;
	if ((int)(nbr * 16) % 2)
		return (1);
	else
		return (0);
}

void				normalize(t_long *a)
{
	long long		tmp;
	int				i;

	i = 0;
	while (i < ((*a).len - 1))
	{
		if ((*a).nbr[i] >= 10)
		{
			tmp = (*a).nbr[i] / 10;
			(*a).nbr[i + 1] += tmp;
			(*a).nbr[i] -= tmp * 10;
		}
		else if ((*a).nbr[i] < 0)
		{
			tmp = (((*a).nbr[i] + 1) / 10) - 1;
			(*a).nbr[i + 1] += tmp;
			(*a).nbr[i] -= tmp * 10;
		}
		++i;
	}
}

t_long				sum(t_long a, t_long b)
{
	t_long			s;
	int				i;

	s.len = a.len > b.len ? a.len + 1 : b.len + 1;
	if (!(s.nbr = (long long *)malloc(sizeof(long long) * s.len)))
		exit(1);
	ft_bzero(s.nbr, sizeof(long long) * s.len);
	i = -1;
	while (++i < s.len)
		s.nbr[i] = (i < a.len ? a.nbr[i] : 0) + (i < b.len ? b.nbr[i] : 0);
	normalize(&s);
	return (s);
}

void				restore_parity(t_long *a, int len)
{
	long long		*new_nbr;
	int				x;
	int				y;
	int				z;

	if (!(new_nbr = (long long *)malloc(sizeof(long long) * ((*a).len + len))))
		exit(1);
	ft_bzero(new_nbr, sizeof(long long) * ((*a).len + len));
	x = 0;
	y = len;
	while (y--)
		new_nbr[x++] = 0;
	z = (*a).len - 1;
	while (z >= 0 && (*a).nbr[z] == 0)
		z--;
	y = 0;
	while (y <= z)
		new_nbr[x++] = (*a).nbr[y++];
	free((*a).nbr);
	(*a).nbr = new_nbr;
	(*a).len += len;
}
