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
				mlx_put_pixel(data->map_layout_img, y * ZOOM + y_count, \
				x * ZOOM + x_count, create_rgba(255, 0, 0, MAP_OPACITY * data->map_visibility));
			else if (ft_strchr("0NSEW", c))
				mlx_put_pixel(data->map_layout_img, y * ZOOM + y_count, \
				x * ZOOM + x_count, create_rgba( 0, 255, 255, MAP_OPACITY * data->map_visibility));
			else
				mlx_put_pixel(data->map_layout_img, y * ZOOM + y_count, \
				x * ZOOM + x_count, create_rgba( 0, 0, 0, 0));
			y_count++;
		}
		x_count++;
	}
}

int	set_ds_vectors(t_vctr *d, t_vctr *s, t_vctr *zeroth, t_vctr *first)
{
	double	err;

	if (zeroth->x < first->x) //step sizes
		s->x = 1;
	else
		s->x = -1;
	if (zeroth->y < first->y)
		s->y = 1;
	else
		s->y = -1;
	if (d->x > d->y)
		err = d->x / 2;
	else
		err = -d->y / 2;
	return (err);
}

void	update_e2_y(double *err, t_vctr *d, t_vctr *s, t_vctr *zeroth)
{
	*err -= d->y;
	zeroth->x += s->x;
}

void	update_e2_x(double *err, t_vctr *d, t_vctr *s, t_vctr *zeroth)
{
	*err += d->x;
	zeroth->y += s->y;
}
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	t_vctr	d;
	t_vctr	s;
	t_vctr	zeroth;
	t_vctr	first;
	double	err;
	double	e2;

	d.x = abs(x1 - x0);
	d.y = abs(y1 - y0);
	first.x = x1;
	first.y = y1;
	zeroth.x = x0;
	zeroth.y = y0;
	err = set_ds_vectors(&d, &s, &zeroth, &first);
	while (1)
	{
		mlx_put_pixel(img, zeroth.y, zeroth.x, color);
		if (zeroth.x == first.x && zeroth.y == first.y)
			break;
		e2 = err;
		if (e2 > -d.x) 
			update_e2_y(&err, &d, &s, &zeroth);
		if (e2 < d.y)
			update_e2_x(&err, &d, &s, &zeroth);
	}
}

void draw_player_triangle(t_var *data)
{
	double	p[2];
	double	rad;
	t_vctr	back_left;
	t_vctr	back_right;
	t_vctr	front;

	front.x = data->player.x + data->direct.x * 5;
	front.y = data->player.y + data->direct.y * 5;
	rad = deg_2_rad(140); // Back left of player
	p[0] = data->direct.x * cos(rad) - data->direct.y * sin(rad);
	p[1] = data->direct.x * sin(rad) + data->direct.y * cos(rad);
	back_left.x = data->player.x + p[0] * 5;
	back_left.y = data->player.y + p[1] * 5;
	rad = deg_2_rad(220); // Back right of player
	p[0] = data->direct.x * cos(rad) - data->direct.y * sin(rad);
	p[1] = data->direct.x * sin(rad) + data->direct.y * cos(rad);
	back_right.x = data->player.x + p[0] * 5;
	back_right.y = data->player.y + p[1] * 5;
	draw_line(data->map_render_img, front.x, front.y, back_left.x, \
	back_left.y, create_rgba(0, 255, 255, 220 * data->map_visibility));
	draw_line(data->map_render_img, front.x, front.y, back_right.x, \
	back_right.y, create_rgba(0, 255, 255, 220 * data->map_visibility));
	draw_line(data->map_render_img, back_left.x, back_left.y, back_right.x, \
	back_right.y, create_rgba(0, 255, 255, 220 * data->map_visibility));
}

/*
	-------------------------
	| rad = deg_2_rad(140);	|
	| rad = 2.443461		|
	| cos(rad) = -0.766044	|
	| sin(rad) = 0.642788	|
	-------------------------
	| rad = deg_2_rad(220);	|
	| rad = 3.839724		|
	| cos(rad) = -0.766044	|
	| sin(rad) = -0.642788	|
	-------------------------
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
