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

int	ray_color(t_var *data, t_draw_ray *draw_r)
{
	double	fraction;

	fraction = (float)draw_r->i / (data->config.width) + \
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
	return (create_rgba(draw_r->i / 5, draw_r->i / 5, draw_r->i / \
															5, MAP_OPACITY));
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
