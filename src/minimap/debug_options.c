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
	if (data->map_ray_state == 1)
		return (createMultiGradient( \
			((float)draw_r->i / (WIDTH)), 6, \
			0,   0, 255, \
			255,   0, 255, \
			255,   0,   0, \
			255, 255,   0, \
			0, 255,   0, \
			0, 255, 255 ) << 8 | MAP_OPACITY);
	return (create_rgba(draw_r->i, 255, 255, MAP_OPACITY));
}

void	debug_fov(t_var *data)
{
	vec2d_t begin;
	begin.x = data->rays[0].x;
	begin.y = data->rays[0].y;
	vec2d_t end;
	end.x = data->rays[WIDTH - 1].x;
	end.y = data->rays[WIDTH - 1].y;
	printf("FOV Angle %lf\n", (angle2d(begin, end) * 180) / PI);
}
