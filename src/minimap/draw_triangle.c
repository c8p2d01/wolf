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

int	set_ds_vectors(vec2d_t *d, vec2d_t *s, vec2d_t *zeroth, vec2d_t *first)
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

void	update_e2_y(double *err, vec2d_t *d, vec2d_t *s, vec2d_t *zeroth)
{
	*err -= d->y;
	zeroth->x += (int)s->x;
}

void	update_e2_x(double *err, vec2d_t *d, vec2d_t *s, vec2d_t *zeroth)
{
	*err += d->x;
	zeroth->y += (int)s->y;
}

void	draw_line(mlx_image_t *img, vec2d_t zeroth, vec2d_t first, int color)
{
	vec2d_t	d;
	vec2d_t	s;
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
		prot_put_pixel(img, (int)zeroth.y, (int)zeroth.x, color);
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
	vec2d_t	back_left;
	vec2d_t	back_right;
	vec2d_t	front;

	front.x = data->player.x + data->direct.x * (data->config.zoom / 4);
	front.y = data->player.y + data->direct.y * (data->config.zoom / 4);
	rad = deg_2_rad(140);
	p[0] = data->direct.x * cos(rad) - data->direct.y * sin(rad);
	p[1] = data->direct.x * sin(rad) + data->direct.y * cos(rad);
	back_left.x = data->player.x + p[0] * (data->config.zoom / 4);
	back_left.y = data->player.y + p[1] * (data->config.zoom / 4);
	rad = deg_2_rad(220);
	p[0] = data->direct.x * cos(rad) - data->direct.y * sin(rad);
	p[1] = data->direct.x * sin(rad) + data->direct.y * cos(rad);
	back_right.x = data->player.x + p[0] * (data->config.zoom / 4);
	back_right.y = data->player.y + p[1] * (data->config.zoom / 4);
	draw_line(data->map_render_img, front, back_left, \
					create_rgba(0, 255, 255, 220)); // Front to Back Left
	draw_line(data->map_render_img, front, back_right, \
					create_rgba(0, 255, 255, 220)); // Front to Back Right
	draw_line(data->map_render_img, back_left, back_right, \
					create_rgba(0, 255, 255, 220)); // Back Left to Back Right
}
