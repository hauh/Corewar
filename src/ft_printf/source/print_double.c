/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 14:51:11 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		bits_handler(t_bits *tally, long double *nbr, size_t *flags,
			int *pre)
{
	(*tally).carria = 64;
	(*tally).nbr.nb = *nbr;
	(*tally).mantis = *(long long *)&(*tally).nbr.nb;
	(*tally).tmp_ex = (*tally).nbr.array[4] - 16383;
	(*tally).exhibi = (*tally).tmp_ex;
	(*tally).middle = (*tally).exhibi > 0 ? (*tally).exhibi / 2 + 1 : 2;
	(*tally).negati = (*tally).nbr.array[4] >> 15;
	if ((*tally).exhibi == -0x4000 && !(*pre = 0))
	{
		if (!((*tally).mantis << 1))
			*flags |= INF;
		else
			*flags |= NNN;
	}
	(*tally).negati && !(*flags & NNN) ? *flags |= NEG : 0;
	if ((*tally).exhibi < 0)
		(*tally).size = ((*tally).exhibi - 63) * -1;
	else if ((*tally).exhibi <= 63 && (*tally).exhibi >= 0)
	{
		(*tally).size = 64;
		(*tally).size < *pre ? (*tally).size += *pre : 0;
	}
	else
		(*tally).size = (*tally).exhibi;
}

void		main_loop_(t_long *whole, t_long *fract, t_bits *tally)
{
	while ((*tally).carria-- > 0)
	{
		if ((*tally).mantis & (1L << (*tally).carria))
			(*tally).exhibi >= 0 ? restorer(whole, (*tally).exhibi, 2)
			: restorer(fract, -(*tally).exhibi, 5);
		(*tally).exhibi--;
	}
}

int			fill_in_with_a_number(char **str, t_long *whole, t_long *fract,
			t_bits *tally)
{
	int count;

	count = 1;
	while (--((*whole).len) >= 0)
		(*str)[count++] = (*whole).nbr[(*whole).len] + '0';
	(*str)[count++] = '.';
	(*tally).middle = count;
	(*fract).power -= (*fract).len;
	(*tally).size = (*fract).len + ((*fract).power > 0 ? (*fract).power : 0);
	while ((*fract).power-- > 0)
		(*str)[count++] = '0';
	while (--((*fract).len) >= 0)
		(*str)[count++] = (*fract).nbr[(*fract).len] + '0';
	free((*whole).nbr);
	free((*fract).nbr);
	return (count);
}

int			putfloat(char **str, t_bits *tally, size_t *flags, int *pre)
{
	t_long	whole;
	t_long	fract;
	int		count;

	init_long(&whole, 0);
	init_long(&fract, 0);
	main_loop_(&whole, &fract, tally);
	count = fill_in_with_a_number(str, &whole, &fract, tally);
	if (SPEC == 'e' || SPEC == 'E')
	{
		(*tally).tmp_ex = count;
		return (scientific_record(str, tally, flags, pre));
	}
	if (SPEC == 'g' || SPEC == 'G')
	{
		(*tally).tmp_ex = count;
		return (choose_betw_f_e(str, tally, flags, pre));
	}
	roundd(str, pre, ((*tally).middle - 2), ((*tally).middle + (*tally).size));
	while (++fract.len < *pre)
		(*str)[count++] = '0';
	*pre == 0 && !(*flags & HAS) ? (*tally).middle-- : 0;
	return ((*tally).middle + *pre);
}

void		print_double(long double nbr, size_t *flags, int *wid, int *pre)
{
	t_bits	tally;
	char	*med;
	int		i;
	int		j;

	j = 0;
	i = 1;
	bits_handler(&tally, &nbr, flags, pre);
	if (!(*flags & (INF | NNN)))
		!(med = (char *)malloc(tally.size * 4)) ? exit(1) : 0;
	!(*flags & (INF | NNN)) ? ft_bzero(med, tally.size) : 0;
	!(*flags & (INF | NNN)) ? j = putfloat(&med, &tally, flags, pre) : 0;
	!(*flags & (INF | NNN)) && med[0] >= '0' ? i = 0 : 0;
	adjustment_wid_pre(flags, wid, pre, j - i);
	fill_width(flags, wid);
	(*flags & (INF | NNN)) && EJECT(3) ? inf_handler(flags) : 0;
	SPEC == 'e' || SPEC == 'E' ? j += 4 : 0;
	while (i < j && EJECT(1) && !(*flags & (INF | NNN)))
		BUFF.g_buff[BUFF.g_count++] = med[i++];
	while ((*wid)-- > 0 && EJECT(1))
		BUFF.g_buff[BUFF.g_count++] = (*flags << 56) >> 56;
	!(*flags & (INF | NNN)) ? free(med) : 0;
}
