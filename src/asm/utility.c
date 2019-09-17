/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:07:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/17 21:41:54 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	skip_whitespaces(char **line)
{
	int skipped;

	skipped = 0;
	while (**line && IS_BLANK(**line))
	{
		++(*line);
		++skipped;
	}
	return (skipped);
}

int	skip_letters(char **line)
{
	int skipped;

	skipped = 0;
	while (**line && **line != SEPARATOR_CHAR && !IS_BLANK(**line))
	{
		++(*line);
		++skipped;
	}
	return (skipped);
}
