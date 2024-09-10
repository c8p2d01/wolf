/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:32:25 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:34:26 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	move_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;

	printf("\e[3;1H\n\n");
	temp = data->config.movement_speed + ydelta;
	if (temp > 0 && temp <= 1)
	{
		printf("movement speed = %f\n", temp);
		data->config.movement_speed += ydelta;
	}
}

void	turn_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;

	printf("\e[3;1H\n\n");
	temp = data->config.turn_speed + ydelta;
	if (temp > 0 && temp <= 3)
	{
		printf("turn speed = %f\n", temp);
		data->config.turn_speed += ydelta;
	}
}

void	turn_mouse_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;

	printf("\e[3;1H\n\n");
	temp = data->config.turn_mouse_speed + ydelta;
	if (temp > 0 && temp <= 3)
	{
		printf("mouse turn speed = %f\n", temp);
		data->config.turn_mouse_speed += ydelta;
	}
}
