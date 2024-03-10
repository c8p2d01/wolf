/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:42:10 by cdahlhof          #+#    #+#             */
/*   Updated: 2022/05/10 17:42:12 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;

	if (lst == NULL)
		return (NULL);
	dest = ft_lstnew(f(lst->content));
	if (dest == NULL)
		return (NULL);
	if (lst->next != NULL)
	{
		dest->next = ft_lstmap(lst->next, f, del);
		if (dest->next == NULL)
		{
			del(dest->content);
			free(dest);
			return (NULL);
		}
	}
	else
		dest->next = NULL;
	return (dest);
}
