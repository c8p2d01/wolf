/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:47:19 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/07/05 07:20:10 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/**
 * @brief create a ray in relation to POV and window width
 * 
 * @param data 
 * @param num 
 * @return t_ray* 
 */
t_ray	ray_creator(t_var *data, int num)
{
	t_ray	ray;
	vec2d_t	orth;

	ray.number = num;
	normalise2d(&data->direct);
	orth = rotate2d(&data->direct, 90);
	resize2d(&orth, -2 * tan(deg_2_rad(data->config.fov / 2)));
	ray.x = data->direct.x;
	ray.y = data->direct.y;
	ray.x -= orth.x / 2;
	ray.y -= orth.y / 2;
	ray.x += (orth.x / data->config.width) * num;
	ray.y += (orth.y / data->config.width) * num;
	ray.wall = NULL;
	ray.wall_percent = 0.5;
	normalise_2d(&ray.x, &ray.y);
	return (ray);
}
