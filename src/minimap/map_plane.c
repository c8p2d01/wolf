/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/09/10 17:06:43 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	filler(t_var *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->map_height)
	{
		y = 0;
		while (y < data->map_width)
		{
			mini_filler(data, x, y, data->map[x][y]);
			y++;
		}
		x++;
	}
}

void	layout_color(t_var *data, int zoom_x, int zoom_y, char c)
{
	if (c == '1')
		prot_put_pixel(data->map_layout_img, zoom_y, \
		zoom_x, MAP_WALL << 8 | data->config.map_opacity);
	else if (c == '2')
		prot_put_pixel(data->map_layout_img, zoom_y, \
		zoom_x, MAP_DOOR << 8 | data->config.map_opacity);
	else if (c == '3')
		prot_put_pixel(data->map_layout_img, zoom_y, \
		zoom_x, MAP_OPEN << 8 | data->config.map_opacity);
	else if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		prot_put_pixel(data->map_layout_img, zoom_y, \
		zoom_x, MAP_GRND << 8 | data->config.map_opacity);
	else
		prot_put_pixel(data->map_layout_img, zoom_y, \
		zoom_x, 0);
}

void	mini_filler(t_var *data, int x, int y, char c)
{
	int	zoom_x;
	int	x_count;
	int	zoom_y;
	int	y_count;

	x_count = 0;
	y_count = 0;
	zoom_x = x * data->config.zoom;
	zoom_y = y * data->config.zoom;
	while (x_count < data->config.zoom)
	{
		y_count = 0;
		while (y_count < data->config.zoom)
		{
			layout_color(data, zoom_x + x_count, zoom_y + y_count, c);
			y_count++;
		}
		x_count++;
	}
}

void	redraw_minimap(t_var *data)
{
	data->config.map_opacity = MAP_OPACITY % 256;
	filler(data);
	draw_player_triangle(data);
	draw_fov_lines(data);
}

void	toggle_map(mlx_key_data_t key, t_var *data)
{
	if (data->config.map_opacity == 0)
		redraw_minimap(data);
	else
	{
		data->config.map_opacity = 0;
		ft_memset(data->map_render_img->pixels, 0, \
			data->map_render_img->width * \
			data->map_render_img->height * sizeof(int));
		ft_memset(data->map_layout_img->pixels, 0, \
			data->map_layout_img->width * \
			data->map_layout_img->height * sizeof(int));
	}
}
