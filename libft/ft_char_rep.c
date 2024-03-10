/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_rep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:20 by cdahlhof          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:21 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_rep(char *str, char target, char replacement)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == target)
			str[i] = replacement;
		i++;
	}
}
