/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:35:48 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:41:12 by cdahlhof         ###   ########.fr       */
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
	draw_r->side = 0;
	while (ft_strchr("03NSWE", draw_r->hit))
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
		draw_r->hit = map_char(data, (int)draw_r->map.y, (int)draw_r->map.x);
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
		if (draw_r->hit == '2')
			draw_r->ray->wall = data->textures[door];
		else if (draw_r->ray->x >= 0)
			draw_r->ray->wall = data->textures[south];
		else
			draw_r->ray->wall = data->textures[north];
	}
	else if (!draw_r->ray->wall)
	{
		if (draw_r->hit == '2')
			draw_r->ray->wall = data->textures[door];
		else if (draw_r->ray->y >= 0)
			draw_r->ray->wall = data->textures[east];
		else
			draw_r->ray->wall = data->textures[west];
	}
	identify_wall_fraction(data, draw_r);
}

void	identify_wall_fraction(t_var *data, t_draw_ray *draw_r)
{
	t_vec2d	wall;

	wall.x = data->player.x + (draw_r->ray->x * \
		draw_r->ray->wall_dst * data->config.zoom);
	wall.y = data->player.y + (draw_r->ray->y * \
		draw_r->ray->wall_dst * data->config.zoom);
	if (draw_r->side)
	{
		if (draw_r->ray->x >= 0)
			draw_r->ray->wall_percent = 1 - fmod(wall.y / \
														data->config.zoom, 1);
		else
			draw_r->ray->wall_percent = fmod(wall.y / \
														data->config.zoom, 1);
	}
	else
	{
		if (draw_r->ray->y >= 0)
			draw_r->ray->wall_percent = fmod(wall.x / \
														data->config.zoom, 1);
		else
			draw_r->ray->wall_percent = 1 - fmod(wall.x / \
														data->config.zoom, 1);
	}
}
