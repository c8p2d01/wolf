/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:47:19 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/04/05 16:54:30 by cdahlhof         ###   ########.fr       */
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
 * in 3d one would construct a projection plane through which one casts the ray
 * 
 * @param data 
 * @param plane 
 */
void create_projection_reference(t_var	*data, double **plane)
{
	*plane = ft_calloc(sizeof(double *), 2);
	if (!*plane)
		return;
	normalize_2d(&data->dir_x, &data->dir_y);
	double	rotator = veclen_2d(data->dir_x, data->dir_y)
				 * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
	*plane[0] = data->dir_x;
	*plane[1] = data->dir_y * -1;
	normalize_2d(&(*plane[0]), &(*plane[1]));

	*plane[0] *= rotator;
	*plane[1] *= rotator;
	normalize_2d(&(*plane[0]), &(*plane[1]));
}

/**
 * @brief create a ray in relation to POV and window width
 * 
 * @param data 
 * @param num 
 * @return t_ray* 
 */
t_ray	rayCreator(t_var *data, short num)
{
	t_ray			ray;
	static double	*ortho;
	
	ray.number = num;
	if (!ortho)
		create_projection_reference(data, &ortho);
	ray.x = data->dir_x + (num - WIDTH / 2) * (2 * ortho[0] / FOV);
	ray.y = data->dir_y + (num - WIDTH / 2) * (2 * ortho[1] / FOV);
	normalize_2d(&ray.x, &ray.y);
	if (DEBUG == 1)
	{
		ft_printf("casting ray from %lf\n\t\t%lf\n", data->ply_x, data->ply_y);
		ft_printf("casting ray towards %lf\n\t\t%lf\n", ray.x, ray.y);
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

int	wall_info_extension(t_var *data,t_ray *ray, double *hit, double *steps)
{
	if (ray->y > 0)				// South
	{
		if (ray->x > 0)	// East
		{
			ray->wall = data->texture_easth;
			if (ray->wallDst == steps[1])
				ray->wall = data->texture_south;
		}
		else			// West
		{
			ray->wall = data->texture_westh;
			if (ray->wallDst == steps[1])
				ray->wall = data->texture_south;
		}
	}
	else
		return (1);
	return (0);
}

int	wall_info(t_var *data,t_ray *ray, double *hit, double *steps)
{
	int	res;

	res = 0;
	if (ray->y <= 0)	// North
	{
		if (ray->x > 0)	// East
		{
			ray->wall = data->texture_easth;
			if (ray->wallDst == steps[1])
				ray->wall = data->texture_north;
		}
		else			// West
		{
			ray->wall = data->texture_westh;
			if (ray->wallDst == steps[1])
				ray->wall = data->texture_north;
		}
	}
	else				// South
		res = wall_info_extension(data, ray, hit, steps);
	return (res);
}

void	wall_walker(t_var *data, t_ray *ray, double *hit)
{
	double	steps[2];

	steps[0] = (1 - (fabs(data->ply_x) - abs((int)data->ply_x))) / fabs(ray->x);
	steps[1] = (1 - (fabs(data->ply_y) - abs((int)data->ply_y))) / fabs(ray->y);
	while (true)
	{
		ray->wallDst = steps[0];
		if (steps[1] < steps[0])
			ray->wallDst = steps[1];
		hit[0] = ray->wallDst * ray->x;
		hit[1] = ray->wallDst * ray->y;
		if (hit[0] < 0 || hit[0] >= data->map_width || hit[1] < 0 || hit[1] >= data->map_height)
		{
			if (DEBUG == 1)
				ft_printf("trace out of bounds\n");
			ray->wall = NULL;
			return ;
		}
		if (data->map[(int)hit[0]][(int)hit[1]] == '1')
			return (wall_info(data, ray, hit));
		if (ray->wallDst == steps[0])
			ray->wallDst += ray->x / fabs(ray->x);
		else
			ray->wallDst += ray->y / fabs(ray->x);
	}
}

void rayMarcher(t_var *data)
{
	t_ray	rays[WIDTH];
	double	intersection[2];
	int32_t	i;

	i = 0;
	while (i < WIDTH)
	{
		rays[i] = rayCreator(data, i);
		wall_walker(data, rays + i, intersection);
		// texture render

	}
}

//
//void	firstStep(t_var *data, double *rayR, double *dst, bool isX)
//{
//	double	delta = 1 / fabs(*rayR);
//
//	double	pos = isX ? data->ply_x : data->ply_y;
//	*dst = (1 - (fabs(pos) - abs((int)pos))) / fabs(*rayR);
//
//	if (*dst == delta)
//		*dst = 0;
//}
//
//int		rayMarcher(t_var *data, double *dst, int rayNumber)
//{
//	double	rayX, rayY;
//
//	rayCreation(data, &rayX, &rayY, rayNumber);
//
//	double	X_Wall_Distance, Y_Wall_Distance;
//	firstStep(data, &rayX, &X_Wall_Distance, true);
//	firstStep(data, &rayY, &Y_Wall_Distance, false);
//
//	double	stepX, stepY;
//	stepX = 1 / fabs(rayX);
//	stepY = 1 / fabs(rayY);
//
//	if (rayNumber == DEBUG)
//	{
//		printf("minV %lf	minH %lf	stepX %lf	stepY %lf\n", X_Wall_Distance, Y_Wall_Distance, stepX, stepY);
//	}
//
//	int		color = 0;
//	// Coordinates to check incoming angle
//	double	traceWallX, traceWallY;
//	(*dst) = 0;
//
//	while(true)
//	{
//		(*dst) = X_Wall_Distance <= Y_Wall_Distance ? X_Wall_Distance : Y_Wall_Distance;
//		if (rayY <= 0)			// North
//		{
//			if (rayX > 0)	// North-East Wall ?
//			{
//				traceWallX = /* floor */(data->ply_x + (rayX * (*dst)));
//				traceWallY = /* floor */(data->ply_y + (rayY * (*dst)));
//				if (rayNumber == DEBUG)
//				{
//					printf("NE dst %lf, xtrace %lf	ytrace %lf \n", *dst, traceWallX, traceWallY);
//				}
//				if (traceWallX >= 0 && traceWallX < WIDTH && 
//					traceWallY >= 0 && traceWallY < HEIGHT &&
//					data->map[(int)traceWallY][(int)traceWallX] == WALL)
//				{
//					color = EAST;
//					if ((*dst) == Y_Wall_Distance)
//						color = NORTH;
//					if (rayNumber == DEBUG)
//					{
//						if ((*dst) == Y_Wall_Distance)
//							{data->map[(int)traceWallY][(int)traceWallX] = 'N'; printf("N horizontal wall\n");}
//						else
//							{data->map[(int)traceWallY][(int)traceWallX] = 'E'; printf("N E vertical wall\n");}
//						printMap(data);
//						data->map[(int)traceWallY][(int)traceWallX] = WALL;
//					}
//					break ;
//				}
//			}
//			else				// North-West Wall ?
//			{
//				traceWallX = /* floor */(data->ply_x + (rayX * (*dst))) - 1;
//				traceWallY = /* floor */(data->ply_y + (rayY * (*dst)));
//				if (rayNumber == DEBUG)
//				{
//					printf("NW dst %lf, xtrace %lf	ytrace %lf \n", *dst, traceWallX, traceWallY);
//				}
//				if (traceWallX >= 0 && traceWallX < WIDTH && 
//					traceWallY >= 0 && traceWallY < HEIGHT &&
//					data->map[(int)traceWallY][(int)traceWallX] == WALL)
//				{
//					color = WEST;
//					if ((*dst) == Y_Wall_Distance)
//						color = NORTH;
//					if (rayNumber == DEBUG)
//					{
//						if ((*dst) == Y_Wall_Distance)
//							{data->map[(int)traceWallY][(int)traceWallX] = 'N'; printf("N horizontal wall\n");}
//						else
//							{data->map[(int)traceWallY][(int)traceWallX] = 'W'; printf("N W vertical wall\n");}
//						printMap(data);
//						data->map[(int)traceWallY][(int)traceWallX] = WALL;
//					}
//					break ;
//				}
//			}
//		}
//		else					// South
//		{
//			if (rayX > 0)	// South-East Wall ?
//			{
//				traceWallX = /* floor */(data->ply_x + (rayX * (*dst)));
//				traceWallY = /* floor */(data->ply_y + (rayY * (*dst))) - 1;
//				if (rayNumber == DEBUG)
//				{
//					printf("SE dst %lf, xtrace %lf	ytrace %lf \n", *dst, traceWallX, traceWallY);
//				}
//				if (traceWallX >= 0 && traceWallX < WIDTH && 
//					traceWallY >= 0 && traceWallY < HEIGHT &&
//					data->map[(int)traceWallY][(int)traceWallX] == WALL)
//				{
//					color = EAST;
//					if ((*dst) == Y_Wall_Distance)
//						color = SOUTH;
//					if (rayNumber == DEBUG)
//					{
//						if ((*dst) == Y_Wall_Distance)
//							{data->map[(int)traceWallY][(int)traceWallX] = 'S'; printf("S horizontal wall\n");}
//						else
//							{data->map[(int)traceWallY][(int)traceWallX] = 'E'; printf("S E vertical wall\n");}
//						printMap(data);
//						data->map[(int)traceWallY][(int)traceWallX] = WALL;
//					}
//					break ;
//				}
//			}
//			else				// South-West Wall ?
//			{
//				traceWallX = /* floor */(data->ply_x + (rayX * (*dst))) - 1;
//				traceWallY = /* floor */(data->ply_y + (rayY * (*dst))) - 1;
//				if (rayNumber == DEBUG)
//				{
//					printf("SW dst %lf, xtrace %lf	ytrace %lf \n", *dst, traceWallX, traceWallY);
//				}
//				if (traceWallX >= 0 && traceWallX < WIDTH && 
//					traceWallY >= 0 && traceWallY < HEIGHT &&
//					data->map[(int)traceWallY][(int)traceWallX] == WALL)
//				{
//					color = WEST;
//					if ((*dst) == Y_Wall_Distance)
//						color = SOUTH;
//					if (rayNumber == DEBUG)
//					{
//						if ((*dst) == Y_Wall_Distance)
//							{data->map[(int)traceWallY][(int)traceWallX] = 'S'; printf("S horizontal wall\n");}
//						else
//							{data->map[(int)traceWallY][(int)traceWallX] = 'W'; printf("S W vertical wall\n");}
//						printMap(data);
//						data->map[(int)traceWallY][(int)traceWallX] = WALL;
//					}
//					break ;
//				}
//			}
//		}
//		if ((*dst) == Y_Wall_Distance)
//		{
//			Y_Wall_Distance += stepY;
//		}
//		else
//		{
//			X_Wall_Distance += stepX;
//		}
//		if ((*dst) > RENDER)
//		{
//			(*dst) = RENDER + 1;
//			break ;
//		}
//	}
//	return (color);
//}
//
//void	printFrame(t_var *data)
//{
//	printf("\e[0m\n");
//	for (int y = 0; y < HEIGHT; y++)
//	{
//		printf("\t");
//		for (int x = 0; x < WIDTH; x++)
//		{
//			putPixel(data->canvas[y][x]);
//		}
//		printf("\e[0m\n");
//	}
//}
//
//void	printMap(t_var *data)
//{
//	printf("\e[48;5;21m                                                  \e[0m\n\n");
//	int		len = 0;
//	char	c;
//	while (data->map[len])
//		len++;
//	for (int y = 0; y < len; y++)
//	{
//		putPixel(WEST);
//		printf("\t");
//		for (int x = 0; x < strlen(data->map[0]); x++)
//		{
//			c = data->map[y][x];
//			printf("\e[48;5;%im  ", c == WALL ? terminalColor(200,200,200) :
//									c == ' ' ? terminalColor(100,100,100) :
//									c == 'P' ? terminalColor(255,100,100) :
//									c == 'D' ? terminalColor(100,255,100) :
//									c == 'N' ? 21 :
//									c == 'S' ? 196 :
//									c == 'W' ? 226 :
//									c == 'E' ? 46 : 16);
//		}
//		printf("\t");
//		putPixel(EAST);
//		printf("\e[0m\n");
//	}
//	printf("\n\n\e[48;5;196m                                                  \e[0m\n");
//}
//
//void	stretcher(t_var *data, int rayNumber, double dst, int color)
//{
//	int renderHeight = ((double)((double)RENDER - dst) / (double)RENDER) * HEIGHT;
//	int draws = (HEIGHT / 2) - (renderHeight / 2);
//	for (int i = draws; i <= draws + renderHeight; i++)
//	{
//		data->canvas[i][rayNumber] = color;
//	}
//}
//
//void	renderer(t_var *data)
//{
//	for (int i = 0; i < HEIGHT / 2; i++)
//	{
//		for (int x = 0; x < WIDTH; x++)
//			data->canvas[i][x] = SKY;
//		data->canvas[i][WIDTH] = 0;
//	}
//	for (int i = 0; i < HEIGHT / 2; i++)
//	{
//		for (int x = 0; x < WIDTH; x++)
//			data->canvas[i + (HEIGHT / 2)][x] = FLOOR;
//		data->canvas[i + (HEIGHT / 2)][WIDTH] = 0;
//	}
//
//	int		color = 42;
//	double	dst = RENDER + 1;
//
//			printf("\t");
//	for (int r = 0; r < WIDTH; r++)
//	{
//		color = rayMarcher(data, &dst, r);
//		if (RENDER - dst < 0)
//		{
//			stretcher(data, r, RENDER, createRGB(128,128,128));
//			continue ;
//		}
//		stretcher(data, r, RENDER, color);
//	}
//}

// int main()
// {
// 	t_var	data;
// 	double	rayX, rayY;
// 	data.dir_x = -1;
// 	data.dir_y = -1;
// 	for(int i = 0; i < WIDTH; i++)
// 	{
// 		rayCreation(&data, &rayX, &rayY, i);
// 		printf("ray %i	%lf	%lf\n", i, rayX, rayY);
// 	}
// }
