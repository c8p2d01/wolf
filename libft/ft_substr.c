/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:43:37 by cdahlhof          #+#    #+#             */
/*   Updated: 2022/05/10 17:43:38 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	if (start >= (unsigned int)size || !s)
		len = 0;
	else if (size < (start + len))
		len = size - start;
	dest = (char *)ft_calloc(sizeof(char), (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
