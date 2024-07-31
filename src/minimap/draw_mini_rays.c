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

void	calc_distances(t_var *data, t_draw_ray *draw_r)
{
	if (data->rays[draw_r->i].x == 0)
		draw_r->d_dist.x = 1000;
	else
		draw_r->d_dist.x = fabs(1 / data->rays[draw_r->i].x);
	if (data->rays[draw_r->i].y == 0)
		draw_r->d_dist.y = 1000;
	else
		draw_r->d_dist.y = fabs(1 / data->rays[draw_r->i].y);
	if (data->rays[draw_r->i].x < 0)
	{
		draw_r->step.x = -1;
		draw_r->s_dist.x = (data->player.x / data->config.zoom - draw_r->map.x) * draw_r->d_dist.x;
	}
	else
		draw_r->s_dist.x = (draw_r->map.x + 1.0 - data->player.x / data->config.zoom) * draw_r->d_dist.x;
	if (data->rays[draw_r->i].y < 0)
	{
		draw_r->step.y = -1;
		draw_r->s_dist.y = (data->player.y / data->config.zoom - draw_r->map.y) * draw_r->d_dist.y;
	}
	else
		draw_r->s_dist.y = (draw_r->map.y + 1.0 - data->player.y / data->config.zoom) * draw_r->d_dist.y;
}

void	hit_wall(t_var *data, t_draw_ray *draw_r)
{
	int	hit;

	draw_r->side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (draw_r->s_dist.x < draw_r->s_dist.y)
		{
			draw_r->s_dist.x += draw_r->d_dist.x;
			draw_r->map.x += draw_r->step.x;
			draw_r->side = 1;
		}
		else
		{
			draw_r->s_dist.y += draw_r->d_dist.y;
			draw_r->map.y += draw_r->step.y;
			draw_r->side = 0;
		}
		if (data->map[(int)draw_r->map.x][(int)draw_r->map.y] == '1')
			hit = 1;
	}
	if (draw_r->side)
		draw_r->s_dist.x -= draw_r->d_dist.x;
	else
		draw_r->s_dist.y -= draw_r->d_dist.y;
}

void	draw_ray(t_var *data, t_draw_ray *draw_r)
{
	vec2d_t	wall;

	if (draw_r->s_dist.x < draw_r->s_dist.y)
		data->rays[draw_r->i].wall_dst = draw_r->s_dist.x;
	else
		data->rays[draw_r->i].wall_dst = draw_r->s_dist.y;
	wall.x = (uint32_t)data->player.x + (data->rays[draw_r->i].x * \
		data->rays[draw_r->i].wall_dst * data->config.zoom);
	wall.y = (uint32_t)data->player.y + (data->rays[draw_r->i].y * \
		data->rays[draw_r->i].wall_dst * data->config.zoom);
	draw_line(data->map_render_img, data->player, wall, draw_r->color);
}

void	draw_fov_lines(t_var *data)
{
	t_draw_ray	draw_r;

	draw_r.i = 0;
	while (draw_r.i < data->config.width)
	{
		draw_r.step.x = 1;
		draw_r.step.y = 1;
		draw_r.map.x = (int)(data->player.x / data->config.zoom);
		draw_r.map.y = (int)(data->player.y / data->config.zoom);
		data->rays[draw_r.i] = rayCreator(data, draw_r.i);
		calc_distances(data, &draw_r);
		hit_wall(data, &draw_r);
		draw_r.color = ray_color(data, &draw_r);
		draw_ray(data, &draw_r);
		draw_r.i += 1;
	}
}
