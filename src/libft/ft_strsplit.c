/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:10:08 by smorty            #+#    #+#             */
/*   Updated: 2019/05/18 15:55:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(char const *s, char c)
{
	unsigned int n;

	n = 0;
	while (*s)
	{
		if ((*s != c) && ((*(s + 1) == c) || (*(s + 1) == 0)))
			++n;
		++s;
	}
	return (n);
}

static char			*create_word(char const *s, char c)
{
	unsigned int	size;
	char			*word;

	size = 0;
	while (*(s + size) && *(s + size) != c)
		++size;
	if (!(word = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	*(word + size) = 0;
	while (size)
	{
		--size;
		*(word + size) = *(s + size);
	}
	return (word);
}

static void			free_words(char **fresh, unsigned int i)
{
	while (i)
	{
		--i;
		free(fresh[i]);
	}
	free(fresh);
}

static char			**split_string(char const *s, unsigned int words, char c)
{
	unsigned int	i;
	char			**fresh;

	if (!(fresh = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			++s;
		if (!(fresh[i] = create_word(s, c)))
		{
			free_words(fresh, i);
			return (NULL);
		}
		while (*s && *s != c)
			++s;
		++i;
	}
	fresh[i] = NULL;
	return (fresh);
}

char				**ft_strsplit(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (split_string(s, count_words(s, c), c));
}
