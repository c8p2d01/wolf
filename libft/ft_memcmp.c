/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:42:25 by cdahlhof          #+#    #+#             */
/*   Updated: 2022/05/10 17:42:27 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c;
	unsigned char	*d;

	i = 0;
	c = (unsigned char *)s1;
	d = (unsigned char *)s2;
	while (n > i)
	{
		if (c[i] != d[i])
			return (c[i] - d[i]);
		i++;
	}
	return (0);
}
