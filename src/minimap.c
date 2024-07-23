/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/23 19:36:37 by tsimitop         ###   ########.fr       */
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

void	draw_player_triangle(t_var *data)
{
	int		temp_x;
	int		temp_y;
	double	p[2];
	double	rad;

	temp_x = 0;
	temp_y = 0;
	temp_y = data->dir_y * 5;
	temp_x = data->dir_x * 5;
	mlx_put_pixel(data->map_img, data->ply_y, data->ply_x, create_rgba(50, 255, 0, 255)); //CENTER OF PLAYER
	mlx_put_pixel(data->map_img, data->ply_y + temp_y, data->ply_x + temp_x, create_rgba(50, 255, 0, 255)); //FRONT OF PLAYER
	mlx_put_pixel(data->map_img, data->ply_y - temp_y, data->ply_x - temp_x, create_rgba(100, 150, 150, 255)); //BACK OF PLAYER
	rad = deg_2_rad(140);
	p[0] = data->dir_x * cos(rad) - data->dir_y * sin(rad);
	p[1] = data->dir_x * sin(rad) + data->dir_y * cos(rad);
	mlx_put_pixel(data->map_img, data->ply_y + p[1] * 5, data->ply_x + p[0] * 5, create_rgba(255, 0, 0, 255)); //BACK OF PLAYER left
	rad = deg_2_rad(220);
	p[0] = data->dir_x * cos(rad) - data->dir_y * sin(rad);
	p[1] = data->dir_x * sin(rad) + data->dir_y * cos(rad);
	mlx_put_pixel(data->map_img, data->ply_y + p[1] * 5, data->ply_x + p[0] * 5, create_rgba(0, 0, 255, 255)); //BACK OF PLAYER right
}

/*
player triangle creation

get player position in pixels?
divide ZOOM in 4
get center point
get direction
set nose at 3/4
set isosceles base corners at 3/4 diagonally opposite the nose
connect points with lines

*/

/*
N
Player Position 190.000000, 110.000000
Player View -1.000000, 0.000000

E
Player Position 190.000000, 110.000000
Player View 0.000000, 1.000000

S
Player Position 190.000000, 110.000000
Player View 1.000000, 0.000000

W
Player Position 190.000000, 110.000000
Player View 0.000000, -1.000000

*/
