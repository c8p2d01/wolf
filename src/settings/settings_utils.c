/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/23 20:16:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	ray_color(t_var *data, int raynum, uint8_t opacity)
{
	double	fraction;

	fraction = (float)raynum / (data->config.width) + \
													data->config.color_offset;
	if (data->config.ray_style == 0)
		return (createMultiGradient(\
			fmod(fraction, 1), \
			7, \
			0, 255, 255, 0, 0, 255, 255, 0, 255, \
			255, 0, 0, 255, 255, 0, 0, 255, 0, \
			0, 255, 255) << 8 | opacity);
	else if (data->config.ray_style == 1)
	{
		if (data->rays[raynum].wall == data->texture_north)
			return (create_rgba(42, 42, 255, opacity));
		else if (data->rays[raynum].wall == data->texture_south)
			return (create_rgba(255, 255, 42, opacity));
		else if (data->rays[raynum].wall == data->texture_easth)
			return (create_rgba(255, 42, 42, opacity));
		else if (data->rays[raynum].wall == data->texture_westh)
			return (create_rgba(42, 255, 42, opacity));
	}
	return (createGradientColor(fmod(fraction, 1), 0, 0, 0, \
			255, 255, 255) << 8 | opacity);
}

void	debug_fov(t_var *data)
{
	vec2d_t	begin;
	vec2d_t	end;

	begin.x = data->rays[0].x;
	begin.y = data->rays[0].y;
	end.x = data->rays[data->config.width - 1].x;
	end.y = data->rays[data->config.width - 1].y;
	printf("FOV Angle %lf\n", (angle2d(begin, end) * 180) / PI);
}
