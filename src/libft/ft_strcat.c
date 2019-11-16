/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:14:21 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 17:52:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dst, char const *src)
{
	char *dst0;

	dst0 = dst;
	while (*dst)
		++dst;
	while (*src)
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = 0;
	return (dst0);
}
