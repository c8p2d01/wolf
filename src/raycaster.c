/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:47:19 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/07/23 16:05:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"
/**
 * @brief Create a projection reference object
 * 
 * in rendering from a perspective it is important to spread out rendered pixels
 * over the FOv evenly - that is not achieved through having them be at the same
 * angle to each other (that would focus pixels in the center)
 * this is also whz for each frame we will make these calcualtions, with fixed
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
	normalize_2d(&data->dir_x, &data->dir_y);
	double	rotator = veclen_2d(data->dir_x, data->dir_y)
				 * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
	(plane)[0] = data->dir_x;
	plane[1] = data->dir_y * -1;
	normalize_2d(&(plane[0]), &(plane[1]));

	plane[0] *= rotator;
	plane[1] *= rotator;
	normalize_2d(&(plane[0]), &(plane[1]));
}

/**
 * @brief create a ray in relation to POV and window width
 * 
 * @param data 
 * @param num 
 * @return t_ray* 
 */
t_ray	rayCreator(t_var *data, int num)
{
	t_ray			ray;
	static double	ortho[2];

	ray.number = num;
	create_projection_reference(data, ortho); // only do this once in the end
	ray.x = data->dir_x + (num - WIDTH / 2) * (ortho[1] / FOV);
	if (ray.x == 0)
		ray.x += 0.0001;
	ray.y = data->dir_y + (num - WIDTH / 2) * (ortho[0] / FOV);
	if (ray.y == 0)
		ray.y += 0.0001;
	normalize_2d(&ray.x, &ray.y);
	if (DEBUG == 1 && num == WIDTH / 4)
	{
		// printf("casting ray from %lf\n\t\t%lf\n", data->ply_x, data->ply_y);
		// printf("casting ray towards \t%lf\n\t\t\t%lf\n", ray.x, ray.y);
	}
	return (ray);
}

bool	close_enough(double a, double b, double closeness)
{
	double	c;

	c = a - b;
	if (fabs(c) - (1 / closeness) < 0)
		return (true);
	return (false);
}

int	wall_info_extension(t_var *data,t_ray *ray, double *steps)
{
	if (ray->y > 0)				// South
	{
		if (ray->x > 0)	// East
		{
			ray->wall = data->path_easth;
			if (ray->wallDst == steps[1])
				ray->wall = data->path_south;
		}
		else			// West
		{
			ray->wall = data->path_westh;
			if (ray->wallDst == steps[1])
				ray->wall = data->path_south;
		}
	}
	else
		return (1);
	return (0);
}

int	wall_info(t_var *data,t_ray *ray, double *steps)
{
	int	res;

	if (ray-> wallDst > 0)
		return (0);
	res = 0;
	if (ray->y <= 0)	// North
	{
		if (ray->x > 0)	// East
		{
			ray->wall = data->path_easth;
			if (ray->wallDst == steps[1])
				ray->wall = data->path_north;
		}
		else			// West
		{
			ray->wall = data->path_westh;
			if (ray->wallDst == steps[1])
				ray->wall = data->path_north;
		}
	}
	else				// South
		res = wall_info_extension(data, ray, steps);
	return (res);
}
void	falsy_ray(t_ray * ray)
{
	// if (close_enough(ray->x, 0.0f, 10000))
	// 	ray->x = 0.000001;
	// if (close_enough(ray->y, 0.0f, 10000))
	// 	ray->y = 0.000001;
}

void	falsy_play(t_var * data)
{
	if (close_enough(data->dir_x, 0.0f, 10000))
		data->dir_x = 0.000001;
	if (close_enough(data->dir_y, 0.0f, 10000))
		data->dir_y = 0.000001;
	if (close_enough(data->ply_x - ((int)data->ply_x), 0.0f, 10000))
		data->ply_x += 0.000001;
	if (close_enough(data->ply_y - ((int)data->ply_y), 0.0f, 10000))
		data->ply_y += 0.000001;
}

void	wall_walker(t_var *data, t_ray *ray, double *hit)
{
	if (ray->number == WIDTH / 4)
	{
		printf("POS\tX\t%lf\tY\t%lf\n", data->ply_x, data->ply_y);
		printf("RayDir\tX\t%lf\tY\t%lf\n", ray->x, ray->y);
		// mlx_put_pixel(data->map_img, (int)data->ply_y, (int)data->ply_x, create_rgba(255, 42, 0, 255));
		// mlx_put_pixel(data->map_img, (int)(data->ply_y + ray->y * 9), (int)(data->ply_x + ray->x * 9), create_rgba(255, 42, 0, 255));
		// mlx_put_pixel(data->map_img, (int)(data->ply_y + ray->y * 18), (int)(data->ply_x + ray->x * 18), create_rgba(255, 42, 0, 255));

		
	}
	// wall_info(data, ray, totals);
}

void	rayMarcher(t_var *data)
{
	double	intersection[2];
	int32_t	i = 0;

	// floor_ceiling();
	// falsy_play(data);
	while (i < WIDTH)
	{
		data->rays[i] = rayCreator(data, i);
		wall_walker(data, data->rays + i, intersection);
		// mlx_put_pixel(data->map_img, 
		// 	(int)(data->rays[i].y),
		// 	(int)(data->rays[i].x), create_rgba(0, 255, 0, 255));
			i++;
	}

	// t_ray test;
	// test.number = WIDTH/2;
	// test.x = 1;
	// test.y = -1;
	// normalize_2d(&test.x, &test.y);

	// wall_walker(data, &test, intersection);
}
