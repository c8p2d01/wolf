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
	if (draw_r->ray->x == 0)
		draw_r->d_dist.x = 1000;
	else
		draw_r->d_dist.x = fabs(1 / draw_r->ray->x);
	if (draw_r->ray->y == 0)
		draw_r->d_dist.y = 1000;
	else
		draw_r->d_dist.y = fabs(1 / draw_r->ray->y);
	if (draw_r->ray->x < 0)
		draw_r->step.x = -1;
	if (draw_r->ray->x < 0)
		draw_r->s_dist.x = (data->player.x / data->config.zoom - \
											draw_r->map.x) * draw_r->d_dist.x;
	else
		draw_r->s_dist.x = (draw_r->map.x + 1.0 - data->player.x / \
										data->config.zoom) * draw_r->d_dist.x;
	if (draw_r->ray->y < 0)
		draw_r->step.y = -1;
	if (draw_r->ray->y < 0)
		draw_r->s_dist.y = (data->player.y / data->config.zoom - \
											draw_r->map.y) * draw_r->d_dist.y;
	else
		draw_r->s_dist.y = (draw_r->map.y + 1.0 - data->player.y / \
										data->config.zoom) * draw_r->d_dist.y;
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
		if (map_char(data, (int)draw_r->map.x, (int)draw_r->map.y) == '1')
			hit = 1;
	}
	if (draw_r->side)
		draw_r->s_dist.x -= draw_r->d_dist.x;
	else
		draw_r->s_dist.y -= draw_r->d_dist.y;
	if (draw_r->s_dist.x < draw_r->s_dist.y)
		draw_r->ray->wall_dst = draw_r->s_dist.x;
	else
		draw_r->ray->wall_dst = draw_r->s_dist.y;
}

void	identify_wall(t_var *data, t_draw_ray *draw_r)
{
	if (draw_r->s_dist.x < draw_r->s_dist.y)
		draw_r->ray->wall_dst = draw_r->s_dist.x;
	else
		draw_r->ray->wall_dst = draw_r->s_dist.y;
	if (draw_r->side && !draw_r->ray->wall)
	{
		if (draw_r->ray->x >= 0)
			draw_r->ray->wall = data->texture_south;
		else
			draw_r->ray->wall = data->texture_north;
	}
	else if (!draw_r->ray->wall)
	{
		if (draw_r->ray->y >= 0)
			draw_r->ray->wall = data->texture_easth;
		else
			draw_r->ray->wall = data->texture_westh;
	}
}

void	draw_ray(t_var *data, t_draw_ray *draw_r)
{
	vec2d_t	wall;

	if (draw_r->s_dist.x < draw_r->s_dist.y)
		draw_r->ray->wall_dst = draw_r->s_dist.x;
	else
		draw_r->ray->wall_dst = draw_r->s_dist.y;
	wall.x = /* (uint32_t) */data->player.x + (draw_r->ray->x * \
		draw_r->ray->wall_dst * data->config.zoom);
	wall.y = /* (uint32_t) */data->player.y + (draw_r->ray->y * \
		draw_r->ray->wall_dst * data->config.zoom);
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
		data->rays[draw_r.i] = ray_creator(data, draw_r.i);
		draw_r.ray = &data->rays[draw_r.i];
		calc_distances(data, &draw_r);
		hit_wall(data, &draw_r);
		draw_r.color = ray_color(data, &draw_r);
		// draw_ray(data, &draw_r);
		draw_r.i += 1;
	}
}
