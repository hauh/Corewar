/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:09:05 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 22:58:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *fresh;

	if (!(fresh = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(fresh, size + 1);
	return (fresh);
}
