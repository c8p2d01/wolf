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
	if (zeroth.x >= 0)
		height = (first.x - zeroth.x);
	else
		height = (first.x + zeroth.x);
	double step;
	step = 1.0 * data->wall->height / height;
	// i = ((int)data->rays[ray_i].hit) / (data->wall->width / 4);
	// printf("Hit: %f\n", data->rays[ray_i].hit);
double temp;
temp = 0;
// x = (int)(temp * data->wall->width); // + zeroth.x
// x = (int)(temp * data->wall->width) * fmod(data->rays[ray_i].hit, 1); // + zeroth.x
// x = (int)(temp * data->wall->width * fmod(data->rays[ray_i].hit, 1) + zeroth.x);
// printf("%i\n", x);
	// i = data->wall->width * fmod(data->rays[ray_i].hit, 1); //NOOOOOOOOOO
// int	vertical = (data->wall->width) * fmod(data->rays[ray_i].hit, 1);
// double magnitude;
// magnitude = sqrt((data->rays[ray_i].x * data->rays[ray_i].x) + (data->rays[ray_i].y * data->rays[ray_i].y));
// double x_dir;
// x_dir = data->rays[ray_i].x / magnitude;
// double y_dir;
// y_dir = data->rays[ray_i].y / magnitude;

int	vertical = (data->wall->width) * fmod(data->rays[ray_i].hit, 1); // + (x_dir * y_dir)
// printf("data->wall->width: %i\n", data->wall->width);
// printf("fmod(data->rays[ray_i].hit, 1): %f\n", fmod(data->rays[ray_i].hit, 1));
// printf("(x_dir * y_dir): %f\n", (x_dir * y_dir));
// printf("vertical: %i\n", vertical);
x = ((int)temp * data->wall->width) + vertical; // + zeroth.x
	while (zeroth.x <= first.x)
	{
		if (x > (data->wall->height * data->wall->width) - 4)
		{
			// printf("X: %i\n", x);
			break;
		}
		// printf("X: %d\n", data->wall_pixels[(int)x]);
		prot_put_pixel(data->main_render_img, (int)zeroth.y, (int)zeroth.x, data->wall_pixels[(int)x]);
		// printf("Y is X: %d | Y: %d\n", (int)zeroth.x, (int)zeroth.y);
		zeroth.x++;
		// prot_put_pixel(data->main_render_img, (int)zeroth.y, (int)zeroth.x, get_txtr_color(data, i));
		// j = ((int)y * data->wall->width + dir_wall);
		// i++;
		temp += step;
		// x = (int)(temp * data->wall->width) + zeroth.x;
		// x = ((int)temp * data->wall->width) + vertical;
		// x = (int)(temp * data->wall->width) + vertical;
		// x += (int)temp;
		x = ((int)temp * data->wall->width) + vertical;
	}
	// printf("Painted pixels for col %d is %d\n", i, tmp);
}

int	get_txtr_color(t_var *data, int i)
{
	int	txtr_color;

	// if (!data->wall->pixels ||!data->wall->pixels[i] || !data->wall->pixels[i + 1] || !data->wall->pixels[i + 2] || !data->wall->pixels[i + 3])
	// 		return (-1);
	txtr_color = (data->wall->pixels[i] << 24) | 
		(data->wall->pixels[i + 1] << 16) | 
		(data->wall->pixels[i + 2] << 8) | 
		255;
	return (txtr_color);
}


// void	draw_line_b(t_var *data, vec2d_t zeroth, vec2d_t first, int color)
// {
// 	int	txtr_color;
// 	int	i = 0;
// 	int	height;

// 	first.x = (int)first.x;
// 	zeroth.x = (int)zeroth.x;
// 	first.y = (int)first.y;
// 	zeroth.y = (int)zeroth.y;
// 	if (zeroth.x >= 0)
// 		height = (first.x - zeroth.x);
// 	else
// 		height = (first.x + zeroth.x);
// 	double step;
// 	// if (height > HEIGHT)
// 	// 	step = height / data->wall->height;
// 	// else
// 		step = data->wall->height / height;
// 	// int y = 0;
// 	// double dir_wall = data->wall->width * fmod(data->rays->x, 1);
// 	int j = 0;
// 	// int j = ((int)y * data->wall->width + dir_wall);
// 	// calculate where my ray is pointing at, and where does that correspond to my 3Dwall and to my texture
// 	i = ((int)data->rays[data->wall->width / FOV].hit * height) * (data->wall->width / 4);
// 	while (zeroth.x <= first.x)
// 	{
// 		txtr_color = get_txtr_color(data, i);
// 		if (txtr_color == -1)
// 			break ;
// 		prot_put_pixel(data->main_render_img, (int)zeroth.y, (int)zeroth.x, txtr_color);
// 		// prot_put_pixel(data->main_render_img, (int)zeroth.y, (int)zeroth.x, get_txtr_color(data, i));
// 		// y = step;
// 		// j = ((int)y * data->wall->width + dir_wall);
// 		// printf("j = %i\n", (int)j);
// 		zeroth.x++;
// 		// i += ((4 * step) + ((zeroth.x / data->wall->width * 4)));
// 		i += 4 * step;
// 	}
// }

void	load_image(t_var *data)
{
	// data->wall = mlx_load_png("images/wall_resized_debug.png");
	// data->wall = mlx_load_png("images/wall_resized.png");
	data->wall = mlx_load_png("images/brick_debug.png");
	// data->wall = mlx_load_png("images/exit.png");
	// data->wall = mlx_load_png("images/wall.png");
	// data->wall = mlx_load_png("images/DEBUG_IMG.png");
	// data->wall = mlx_load_png("images/DEBUG_IMG_SPRAY.png");
	// data->wall = mlx_load_png("images/prison.png");
	// data->wall = mlx_load_png("images/colors.png");


printf("data->wall->width = %i, data->wall->height = %i, data->wall->width * data->wall->height = %i\n", data->wall->width, data->wall->height, data->wall->width * data->wall->height);
	int i = 0;
	int j = 0;
	// while (data->wall->pixels[j])
	// {
	// 	j++;
	// }
	data->wall_pixels = ft_calloc(((data->wall->height * data->wall->width)) + 4, sizeof(int));
	j = 0;
	// while (j * data->wall->width * data->wall->height) //data->wall->pixels && data->wall->pixels[i]
	while (j < data->wall->width * data->wall->height) //data->wall->pixels && data->wall->pixels[i]
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
