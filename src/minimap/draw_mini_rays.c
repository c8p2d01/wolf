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
		draw_r->s_dist.x = (data->ply_x / ZOOM - draw_r->map.x) * draw_r->d_dist.x;
	}
	else
		draw_r->s_dist.x = (draw_r->map.x + 1.0 - data->ply_x / ZOOM) * draw_r->d_dist.x;
	if (data->rays[draw_r->i].y < 0)
	{
		draw_r->step.y = -1;
		draw_r->s_dist.y = (data->ply_y / ZOOM - draw_r->map.y) * draw_r->d_dist.y;
	}
	else
		draw_r->s_dist.y = (draw_r->map.y + 1.0 - data->ply_y / ZOOM) * draw_r->d_dist.y;
}

void	print_map(t_var *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->map_height)
	{
		y = 0;
		while (y < data->map_width)
		{
			printf("%c", data->map[x][y]);
			y++;
		}
		x++;
		printf("\n");
	}
}

void	hit_wall(t_var *data, t_draw_ray *draw_r)
{
	int	hit;
	int	side = 0;

	hit = 0;
	while (hit == 0)
	{
		if (draw_r->s_dist.x < draw_r->s_dist.y)
		{
			draw_r->s_dist.x += draw_r->d_dist.x;
			draw_r->map.x += draw_r->step.x;
			side = 1;
		}
		else
		{
			draw_r->s_dist.y += draw_r->d_dist.y;
			draw_r->map.y += draw_r->step.y;
			side = 0;
		}
		if (data->map[draw_r->map.x][draw_r->map.y] == '1')
			hit = 1;
	}
	if (side)
		draw_r->s_dist.x -= draw_r->d_dist.x;
	else
		draw_r->s_dist.y -= draw_r->d_dist.y;
}

void	draw_ray(t_var *data, t_draw_ray *draw_r)
{
	t_vctr	p_zero;
	t_vctr	p_goal;

	if (draw_r->s_dist.x < draw_r->s_dist.y)
		data->rays[draw_r->i].wallDst = draw_r->s_dist.x;
	else
		data->rays[draw_r->i].wallDst = draw_r->s_dist.y;
	p_zero.x = (int)data->ply_x;
	p_zero.y = (int)data->ply_y;
	p_goal.x = (int)data->ply_x + (data->rays[draw_r->i].x * \
		data->rays[draw_r->i].wallDst * ZOOM);
	p_goal.y = (int)data->ply_y + (data->rays[draw_r->i].y * \
		data->rays[draw_r->i].wallDst * ZOOM);
	draw_line(data, p_zero, p_goal, \
		create_rgba((draw_r->i % 128) * 2, 222, 222, 222));
}

void	draw_fov_lines(t_var *data)
{
	t_draw_ray	draw_r;

	draw_r.i = 0;
	while (draw_r.i < WIDTH)
	{
		draw_r.step.x = 1;
		draw_r.step.y = 1;
		draw_r.map.x = (int)(data->ply_x / ZOOM);
		draw_r.map.y = (int)(data->ply_y / ZOOM);
		data->rays[draw_r.i] = rayCreator(data, draw_r.i);
		calc_distances(data, &draw_r);
		hit_wall(data, &draw_r);
		draw_ray(data, &draw_r);
		draw_r.i += 1;
	}
}
