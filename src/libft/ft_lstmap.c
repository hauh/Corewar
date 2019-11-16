/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:50:54 by smorty            #+#    #+#             */
/*   Updated: 2019/04/14 19:16:03 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh;

	if (!f || !lst)
		return (NULL);
	fresh = f(lst);
	fresh->next = ft_lstmap(lst->next, f);
	if (!fresh->next && lst->next)
	{
		free(fresh);
		return (NULL);
	}
	return (fresh);
}
