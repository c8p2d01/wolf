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

int	ray_color(t_var *data, int i)
{
	double	fraction;

	fraction = (float)i / (data->config.width) + \
													data->config.color_offset;
	if (data->config.ray_style == 0)
		return (createMultiGradient(\
			fmod(fraction, 1), \
			7, \
			0, 255, 255, \
			0, 0, 255, \
			255, 0, 255, \
			255, 0, 0, \
			255, 255, 0, \
			0, 255, 0, \
			0, 255, 255) << 8 | MAP_OPACITY);
	else if (data->config.ray_style == 1)
	{
		if (data->rays[i].wall == data->path_north)
			return (create_rgba(42, 42, 255, MAP_OPACITY));
		else if (data->rays[i].wall == data->path_south)
			return (create_rgba(255, 255, 42, MAP_OPACITY));
		else if (data->rays[i].wall == data->path_easth)
			return (create_rgba(255, 42, 42, MAP_OPACITY));
		else if (data->rays[i].wall == data->path_westh)
			return (create_rgba(42,255,  42, MAP_OPACITY));
	}
	return (createGradientColor(fmod(fraction, 1), 0, 0, 0, \
			255, 255, 255) << 8 | MAP_OPACITY);
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
