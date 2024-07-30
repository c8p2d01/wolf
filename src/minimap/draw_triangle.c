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

int	set_ds_vectors(t_vctr *d, t_vctr *s, t_vctr *zeroth, t_vctr *first)
{
	double	err;

	if ((int)zeroth->x < (int)first->x)
		s->x = 1;
	else
		s->x = -1;
	if ((int)zeroth->y < (int)first->y)
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
	zeroth->x += (int)s->x;
}

void	update_e2_x(double *err, t_vctr *d, t_vctr *s, t_vctr *zeroth)
{
	*err += d->x;
	zeroth->y += (int)s->y;
}

void	draw_line(t_var *data, t_vctr zeroth, t_vctr first, int color)
{
	t_vctr	d;
	t_vctr	s;
	t_intvctr int_zeroth;
	double	err;
	double	e2;

	first.x = (int)first.x;
	zeroth.x = (int)zeroth.x;
	first.y = (int)first.y;
	zeroth.y = (int)zeroth.y;
	d.x = abs((int)first.x - (int)zeroth.x);
	d.y = abs((int)first.y - (int)zeroth.y);
	err = set_ds_vectors(&d, &s, &zeroth, &first);
	while (1)
	{
		int_zeroth.y = ((int)zeroth.y);
		int_zeroth.x = ((int)zeroth.x);
		mlx_put_pixel(data->map_img, int_zeroth.y, int_zeroth.x, color);
		if ((int)zeroth.x == (int)first.x && (int)zeroth.y == (int)first.y)
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

	front.x = data->ply_x + data->dir_x * 5;
	front.y = data->ply_y + data->dir_y * 5;
	rad = deg_2_rad(140);
	p[0] = data->dir_x * cos(rad) - data->dir_y * sin(rad);
	p[1] = data->dir_x * sin(rad) + data->dir_y * cos(rad);
	back_left.x = data->ply_x + p[0] * 5;
	back_left.y = data->ply_y + p[1] * 5;
	rad = deg_2_rad(220);
	p[0] = data->dir_x * cos(rad) - data->dir_y * sin(rad);
	p[1] = data->dir_x * sin(rad) + data->dir_y * cos(rad);
	back_right.x = data->ply_x + p[0] * 5;
	back_right.y = data->ply_y + p[1] * 5;
	draw_line(data, front, back_left, create_rgba(0, 255, 255, 220)); // Front to Back Left
	draw_line(data, front, back_right, create_rgba(0, 255, 255, 220)); // Front to Back Right
	draw_line(data, back_left, back_right, create_rgba(0, 255, 255, 220)); // Back Left to Back Right
}
