/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:41:09 by cdahlhof          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:11 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_getbehind(char *str)
{
	double	ret;
	double	dez;

	ret = 0;
	dez = 10;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		ret += ((*str - 48) / dez);
		dez *= 10;
		str++;
	}
	return (ret);
}

static double	ft_final(double front, double behind, char sgn)
{
	int		sign;

	sign = 1;
	if (front < 0 || sgn == '-')
		sign = -1;
	return (front + behind * sign);
}

double	ft_atof(char *str)
{
	char	*front;
	char	*behind;
	size_t	len;
	double	ret;

	len = ft_strlen(str);
	front = malloc(sizeof(char) * len);
	if (!len || !front)
		return (0);
	ret = 0;
	behind = ft_strchr(str, '.');
	if (!behind)
	{
		free(front);
		return ((double)(ft_atoi(str)));
	}
	if (ft_strlen(behind) < len)
	{
		len -= ft_strlen(behind);
		ft_strlcpy(front, str, len + 1);
	}
	behind++;
	ret = ft_final(ft_atoi(front), ft_getbehind(behind), str[0]);
	free(front);
	return (ret);
}
