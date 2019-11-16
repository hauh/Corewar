/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:11:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/02 12:59:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*to;

	to = (unsigned char *)dst;
	while (n--)
		*to++ = *(unsigned char *)src++;
	return (dst);
}
