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

#include "./rendering.h"

void	draw_line_b(t_var *data, vec2d_t zeroth, vec2d_t first, int ray_i)
{
	int	txtr_color;
	int	i = 0;
	int	height;
	int x;

	first.x = (int)first.x;
	zeroth.x = (int)zeroth.x;
	first.y = (int)first.y;
	zeroth.y = (int)zeroth.y;
	height = (first.x - zeroth.x);
	double step;
	step = 1.0 * data->wall->height / height;
double temp;
temp = 0;
int	vertical = (data->wall->width) * data->rays[ray_i].hit; // + (x_dir * y_dir)
x = ((int)temp * data->wall->width) + vertical; // + zeroth.x
	while (zeroth.x <= first.x)
	{
		if (x > (data->wall->height * data->wall->width) - 4)
			break;
		prot_put_pixel(data->main_render_img, (int)zeroth.y, (int)zeroth.x, data->wall_pixels[(int)x]);
		zeroth.x++;
		temp += step;
		x = ((int)temp * data->wall->width) + vertical;
	}
}

int	get_txtr_color(t_var *data, int i)
{
	int	txtr_color;

	txtr_color = (data->wall->pixels[i] << 24) | 
		(data->wall->pixels[i + 1] << 16) | 
		(data->wall->pixels[i + 2] << 8) | 
		255;
	return (txtr_color);
}

void	load_image(t_var *data)
{
	// data->wall = mlx_load_png("images/wall_resized_debug.png");
	// data->wall = mlx_load_png("images/wall_resized.png");
	// data->wall = mlx_load_png("images/brick_debug.png");
	data->wall = mlx_load_png("images/exit.png");
	// data->wall = mlx_load_png("images/wall.png");
	// data->wall = mlx_load_png("images/DEBUG_IMG.png");
	// data->wall = mlx_load_png("images/DEBUG_IMG_SPRAY.png");
	// data->wall = mlx_load_png("images/prison.png");
	// data->wall = mlx_load_png("images/colors.png");


printf("data->wall->width = %i, data->wall->height = %i, data->wall->width * data->wall->height = %i\n", data->wall->width, data->wall->height, data->wall->width * data->wall->height);
	int i = 0;
	int j = 0;
	data->wall_pixels = ft_calloc(((data->wall->height * data->wall->width)) + 4, sizeof(int));
	j = 0;
	while (j < data->wall->width * data->wall->height)
	{
		int color = get_txtr_color(data, i);
		if (color == -1)
			break;
		data->wall_pixels[j] = color;
		i+=4;
		j++;
	}
	printf("Loaded png\n");
}
