/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/09/10 17:36:11 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	draw_ray(t_var *data, t_draw_ray *draw_r)
{
	t_vec2d	wall;

	wall.x = (uint32_t)data->player.x + (draw_r->ray->x * \
		draw_r->ray->wall_dst * data->config.zoom);
	wall.y = (uint32_t)data->player.y + (draw_r->ray->y * \
		draw_r->ray->wall_dst * data->config.zoom);
	draw_line(data->map_render_img, data->player, wall, draw_r->color);
}

void	draw_fov_lines(t_var *data)
{
	t_draw_ray	draw_r;

	ft_memset(data->map_render_img->pixels, 0, \
				data->map_render_img->width * \
				data->map_render_img->height * sizeof(int));
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
		draw_r.hit = '0';
		hit_wall(data, &draw_r);
		identify_wall(data, &draw_r);
		draw_r.color = ray_color(data, draw_r.i, data->config.map_opacity);
		draw_ray(data, &draw_r);
		draw_r.i += 1;
	}
}

void	prot_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x < img->width && y < img->height && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
}
