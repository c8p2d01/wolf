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
	zoom_x = x * data->config.zoom;
	zoom_y = y * data->config.zoom;
	while (x_count < data->config.zoom)
	{
		y_count = 0;
		while (y_count < data->config.zoom)
		{
			if (c == '1')
				prot_put_pixel(data->map_layout_img, zoom_y + y_count, \
				zoom_x + x_count, MAP_WALL << 8 | MAP_OPACITY);
			else if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
				prot_put_pixel(data->map_layout_img, zoom_y + y_count, \
				zoom_x + x_count, MAP_GRND << 8 | MAP_OPACITY);
			else
				prot_put_pixel(data->map_layout_img, zoom_y + y_count, \
				zoom_x + x_count,  MAP_OPACITY);
			y_count++;
		}
		x_count++;
	}
}

void	prot_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x < img->width && y < img->height && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
	// else
	// 	printf("\e[38;2;255;42;42mpixel OOB Error\e[0m \tX %u\tY %u\n", x, y);
}
