/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:09:01 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/07/22 17:05:42 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	create_rgba(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double deg_2_rad(float degree)
{
	return(degree * (PI / 180) );
}

bool	close_enough(double a, double b, double closeness)
{
	double	c;

	c = a - b;
	if (fabs(c) - (1 / closeness) < 0)
		return (true);
	return (false);
}

void	turn(t_var *data, float degree)
{
	double	p[2];
	double	rad;

	rad = deg_2_rad(degree);

	p[0] = data->dir_x * cos(rad) - data->dir_y * sin(rad);
	p[1] = data->dir_x * sin(rad) + data->dir_y * cos(rad);
	if (data->dir_x == 0)
		data->dir_x = 0.00001;
	if (data->dir_y == 0)
		data->dir_y = 0.00001;
	normalize_2d(p, p + 1);
	data->dir_x = p[0];
	data->dir_y = p[1];
}

