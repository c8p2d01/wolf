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

#include "../inc/cub.h"
/**
 * @brief Create a projection reference object
 * 
 * in rendering from a perspective it is important to spread out rendered pixels
 * over the FOv evenly - that is not achieved through having them be at the same
 * angle to each other (that would focus pixels in the center)
 * this is also why for each frame we will make these calcualtions, with fixed
 * angle offset one could easily reuse ray vectors...
 * 
 * therefore we need a reference through which we can construct rays per pixel
 * 
 * here in 2d this is simpy a vector the is perbendicular to the POV
 * in 3d one would construct a projection plane through which one casts each ray
 * 
 * @param data 
 * @param plane 
 */
void create_projection_reference(t_var	*data, double *plane)
{
	normalise_2d(&data->direct.x, &data->direct.y);
	double	rotator = veclen_2d(data->direct.x, data->direct.y)
				 * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
	(plane)[0] = data->direct.x;
	plane[1] = data->direct.y * -1;
	normalise_2d(&(plane[0]), &(plane[1]));

	plane[0] *= rotator;
	plane[1] *= rotator;
	normalise_2d(&(plane[0]), &(plane[1]));
}

/**
 * @brief create a ray in relation to POV and window width
 * 
 * @param data 
 * @param num 
 * @return t_ray* 
 */
/**
 * @brief create a ray in relation to POV and window width
 * 
 * @param data 
 * @param num 
 * @return t_ray* 
 */
t_ray	rayCreator(t_var *data, int num)
{
	t_ray	ray;
	vec2d_t	orth;

	ray.number = num;
	normalise2d(&data->direct);
	orth = rotate2d(&data->direct, 90);
	resize2d(&orth, 2 * tan(deg_2_rad(FOV / 2)));
	ray.x = data->direct.x;
	ray.y = data->direct.y;
	ray.x -= orth.x / 2;
	ray.y -= orth.y / 2;
	ray.x += (orth.x / WIDTH) * num;
	ray.y += (orth.y / WIDTH) * num;
	normalise_2d(&ray.x, &ray.y);
	return (ray);
}
