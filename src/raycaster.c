/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:47:19 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/03/11 01:47:30 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void create_projection_reference(t_var	*data, double **plane)
{
	*plane = ft_calloc(sizeof(double *), 2);
	if (!*plane)
		return;
	normalize_2d(&data->orientationX, &data->orientationY);
	double	rotator = veclen_2d(data->orientationX, data->orientationY) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
	*plane[0] = data->orientationY;
	*plane[1] = data->orientationX * -1;
	normalize_2d(&(*plane[0]), &(*plane[1]));

	*plane[0] *= rotator;
	*plane[1] *= rotator;
	normalize_2d(&(*plane[0]), &(*plane[1]));
}

t_ray	*rayCreator(t_var	*data, short num)
{
	t_ray			*ray;
	static double	*plane;
	
	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return (NULL);
	ray->number = num;
	if (!plane)
		create_projection_reference(data, &plane);
}

//void	rayCreation(t_var	*data, double *rayX, double *rayY, int rayNumber)
//{
//	static double projectionX,projectionY;
//	static bool projectionCalc;
//
//	if (!projectionCalc)
//	{
//		normalize(2, &data->orientationX, &data->orientationY);
//		double	rotator = veclen(2, data->orientationX, data->orientationY) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
//		projectionX = data->orientationY;
//		projectionY = data->orientationX * -1;
//		normalize(2, &projectionX, &projectionY);
//
//		projectionX *= rotator;
//		projectionY *= rotator;
//		normalize(2, &projectionX, &projectionY);
//		projectionCalc = true;
//	}
//
//	*rayX = data->orientationX + projectionX - ((projectionX * 2) / WIDTH) * rayNumber;
//	*rayY = data->orientationY + projectionY - ((projectionY * 2) / WIDTH) * rayNumber;
//
//	normalize(2, rayX, rayY);
//	if (DEBUG == rayNumber)
//	{
//		printf("Created Ray	x %lf 	y %lf \n", *rayX, *rayY);
//	}
//}
//
//void	firstStep(t_var *data, double *rayR, double *dst, bool isX)
//{
//	double	delta = 1 / fabs(*rayR);
//
//	double	pos = isX ? data->positionX : data->positionY;
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
//				traceWallX = /* floor */(data->positionX + (rayX * (*dst)));
//				traceWallY = /* floor */(data->positionY + (rayY * (*dst)));
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
//				traceWallX = /* floor */(data->positionX + (rayX * (*dst))) - 1;
//				traceWallY = /* floor */(data->positionY + (rayY * (*dst)));
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
//				traceWallX = /* floor */(data->positionX + (rayX * (*dst)));
//				traceWallY = /* floor */(data->positionY + (rayY * (*dst))) - 1;
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
//				traceWallX = /* floor */(data->positionX + (rayX * (*dst))) - 1;
//				traceWallY = /* floor */(data->positionY + (rayY * (*dst))) - 1;
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
// 	data.orientationX = -1;
// 	data.orientationY = -1;
// 	for(int i = 0; i < WIDTH; i++)
// 	{
// 		rayCreation(&data, &rayX, &rayY, i);
// 		printf("ray %i	%lf	%lf\n", i, rayX, rayY);
// 	}
// }
