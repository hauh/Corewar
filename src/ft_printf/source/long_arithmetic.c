/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:10:22 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/07 12:21:59 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int					compensation(t_long *a, int zero)
{
	long long		*new_nbr;
	int				x;
	int				y;
	int				z;

	if (!(new_nbr = (long long *)malloc(sizeof(long long) * ((*a).len - zero))))
		exit(1);
	ft_bzero(new_nbr, sizeof(long long) * ((*a).len - zero));
	x = 0;
	y = 0;
	z = zero;
	while (zero--)
		y++;
	while (y <= (*a).len - 1)
		new_nbr[x++] = (*a).nbr[y++];
	free((*a).nbr);
	(*a).nbr = new_nbr;
	(*a).len -= z;
	return (1);
}

void				multi(t_long a, t_long b, t_long *res)
{
	int				i;
	int				j;

	ft_bzero((*res).nbr, sizeof(long long) * (*res).len);
	i = -1;
	while (++i < a.len)
	{
		j = -1;
		while (++j < b.len)
			(*res).nbr[i + j] += a.nbr[i] * b.nbr[j];
	}
}

t_long				karatsuba(t_long a, t_long b)
{
	t_karatsuba_var	var;

	var.res.len = a.len + b.len;
	!(var.res.nbr = (long long *)malloc(8 * var.res.len)) ? exit(1) : 0;
	if (a.len < KARATSUBA_MIN || b.len < KARATSUBA_MIN)
		multi(a, b, &var.res);
	else
	{
		init_var(&a, &var, 1);
		init_var(&b, &var, 0);
		var.res1 = karatsuba(var.a_l, var.b_l);
		var.res2 = karatsuba(var.a_r, var.b_r);
		var.sum1 = sum(var.a_l, var.a_r);
		var.sum2 = sum(var.b_l, var.b_r);
		var.res3 = karatsuba(var.sum1, var.sum2);
		sub(sub(&var.res3, var.res1), var.res2);
		ft_memcpy(var.res.nbr, var.res1.nbr, var.res1.len * 8);
		ft_memcpy(var.res.nbr + var.res1.len, var.res2.nbr, var.res2.len * 8);
		var.i = -1;
		while (++(var.i) < var.res3.len)
			var.res.nbr[var.a_l.len + var.i] += var.res3.nbr[var.i];
		tidy_up(&var);
	}
	normalize(&var.res);
	return (var.res);
}

void				main_loop(t_long *a, t_long *b, int power)
{
	t_long			tmp;
	int				zero;

	zero = 0;
	while (power)
	{
		if (power & 1)
		{
			if ((*a).len > (*b).len && (zero = (*a).len - (*b).len))
				restore_parity(b, zero);
			else if ((*a).len < (*b).len && (zero = (*b).len - (*a).len))
				restore_parity(a, zero);
			tmp = karatsuba(*a, *b);
			free((*a).nbr);
			*a = tmp;
			zero ? compensation(a, zero) && !(zero = 0) : 0;
			zero_passer(a);
		}
		tmp = karatsuba(*b, *b);
		free((*b).nbr);
		*b = tmp;
		zero_passer(b);
		power >>= 1;
	}
}

void				restorer(t_long *nbr, int power, int base)
{
	t_long			tmp;
	t_long			a;
	t_long			b;

	init_long(&a, 1);
	init_long(&b, base);
	main_loop(&a, &b, power);
	if (base == 5)
		restore_parity(nbr, power - (*nbr).power);
	tmp = sum(*nbr, a);
	free((*nbr).nbr);
	*nbr = tmp;
	free(a.nbr);
	free(b.nbr);
	zero_passer(nbr);
	base == 5 ? (*nbr).power = power : 0;
}
