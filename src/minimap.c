/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/23 13:13:42 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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

void	mini_filler(t_var *data, int x, int y, char c)
{
	int	zoom_x;
	int	x_count;
	int	zoom_y;
	int	y_count;

	x_count = 0;
	y_count = 0;
	zoom_x = x * ZOOM;
	zoom_y = y * ZOOM;
	while (x_count < ZOOM)
	{
		y_count = 0;
		while (y_count < ZOOM)
		{
			if (c == '1')
				mlx_put_pixel(data->map_img, y * ZOOM + y_count, \
				x * ZOOM + x_count, create_rgba(255, 0, 0, 50));
			else
				mlx_put_pixel(data->map_img, y * ZOOM + y_count, \
				x * ZOOM + x_count, create_rgba( 0, 255, 255, 50));
			y_count++;
		}
		x_count++;
	}
}
