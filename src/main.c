/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:31:46 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/04/04 16:43:10 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/*
	\    \   /     /	
	 \  0------#  /		0------#0------#0------#
	  \ |  N   | /		|  N   ||  N   ||  N   |
	   X|W   E |X		|W   E ||W   E ||W   E |
	  / |  S   | \		|  S   ||  S   ||  S   |
	 /  #------#  \		#------##------##------#
	/    /   \     \	
	0 -> coordinate in map
	/ or \ -> incoming rays

	from different ray incomig angles different sides should be hit and tracked
	e.g. from south east walls should compare against coordinate + 1 in either direction

	check intersection only at raylengths where a wall could be
	-> find a vectorlength for the neares horizontal and neares vertical and from there on iterate in steps
*/

// void	render(t_var *var)
// {
// 	// Sky and Floor coloring
// 	for (int i = 0; i < HEIGHT / 2; i++)
// 	{
// 		memset(var->canvas[i], SKY, WIDTH);
// 		var->canvas[i][WIDTH] = 0;
// 	}
// 	for (int i = 0; i < HEIGHT / 2; i++)
// 	{
// 		memset(var->canvas[i + (HEIGHT / 2)], FLOOR, WIDTH);
// 		var->canvas[i + (HEIGHT / 2)][WIDTH] = 0;
// 	}
// 	// rays
// 
// 	// projection plane on which to cast rays to avoid fishEye view
// 	double rotx = var->orientationY;
// 	double roty = -var->orientationX;
// 	double planelen = pow(pow(var->orientationX, 2) + pow(var->orientationY, 2), 0.5) * sin((FOV * PI /180) / 2) / cos((FOV * PI /180) / 2);
// 	double tmp = pow(pow(rotx, 2) + pow(roty, 2), 0.5);
// 	rotx /= tmp;
// 	roty /= tmp;
// 	rotx *= planelen;
// 	roty *= planelen;
// 
// 	// ray direction vector, normed
// 	double rx, ry;
// 	// first step to walls (startlength)
// 	double h, v;
// 	// stepsize in between same kinds of walls
// 	double delta_h, delta_v;
// 
// 	for (int r = 1; r <= WIDTH; r++)
// 	{
// 		rx = var->orientationX + rotx - ((rotx * 2) / WIDTH) * r;
// 		ry = var->orientationY + roty - ((roty * 2) / WIDTH) * r;
// 		double temp = pow(pow(rx, 2) + pow(ry, 2), 0.5);
// 		rx /= temp;
// 		ry /= temp;
// 
// 		h = (1 - (fabs(var->positionX) - abs((int)var->positionX))) / fabs(rx);
// 		v = (1 - (fabs(var->positionY) - abs((int)var->positionY))) / fabs(ry);
// 		//printf("pV %lf %lf    pH %lf %lf\t", var->positionX + rx * v, var->positionY + ry * v, var->positionX + rx * h, var->positionY + ry * h);
// 		delta_h = 1 / fabs(rx);
// 		delta_v = 1 / fabs(ry);
// 		//printf("S %lf    pos %lf    V0 %lf %lf    V1 %lf %lf    V2 %lf %lf\t", rx * v, var->positionX, var->positionX + rx * v, var->positionY + ry * v, var->positionX + rx * (v + delta_v), var->positionY + ry * (v + delta_v), var->positionX + rx * (v + 2 * delta_v), var->positionY + ry * (v + 2 * delta_v));
// 		if (h == delta_h)
// 			h = 0;
// 		if (v == delta_v)
// 			v = 0;
// 
// 		int	t = 0;
// 		int		tx, ty;
// 		double dst = 0;
// 		while (1)
// 		{
// 			if (v < h)
// 				dst = v;
// 			else
// 				dst = h;
// 			//dst == v ? printf("	V %lf %lf\t", (var->positionX + rx * dst), (var->positionY + ry * dst)) : printf("	H %lf %lf\t", (var->positionX + rx * dst), (var->positionY + ry * dst));
// 
// 			if (ry > 0)	// N
// 			{
// 				if (rx > -0.f)	// NE
// 				{
// 					tx = (int)(var->positionX + rx * dst);
// 					ty = (int)(var->positionY + ry * dst);
// 					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
// 					{
// 						//printf("WALL NE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
// 						// printf("    seen pos %i %i ", (int)(var->positionX + rx * dst), (int)(var->positionY + ry * dst));
// 						t = createRGB(255,255,0);
// 						if (dst == v)
// 							t = createRGB(255,255,0);;
// 						// write(1, "\n", 1);
// 						break;
// 					}
// 				}
// 				else		// NW
// 				{
// 					tx = (int)(var->positionX + rx * dst) - 1;
// 					ty = (int)(var->positionY + ry * dst);
// 					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
// 					{
// 						//printf("WALL NW %lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
// 						// printf("    seen pos %i %i ", -1 + (int)(var->positionX + rx * dst), (int)(var->positionY + ry * dst));
// 						t = createRGB(0,255,0);
// 						if (dst == v)
// 							t = createRGB(0,0,255);
// 						// write(1, "\n", 1);
// 						break;
// 					}
// 				}
// 			}
// 			else		// S
// 			{
// 				if (rx > 0)	// SE
// 				{
// 					tx = (int)(var->positionX + rx * dst);
// 					ty = (int)(var->positionY + ry * dst) - 1;
// 					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
// 					{
// 						 //printf("WALL SE	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
// 						// printf("    seen pos %i %i ", (int)(var->positionX + rx * dst), -1 + (int)(var->positionY + ry * dst));
// 						t = createRGB(255,255,0);
// 						if (dst == v)
// 							t = createRGB(255,0,0);
// 						// write(1, "\n", 1);
// 						break;
// 					}
// 				}
// 				else		// SW
// 				{
// 					tx = (int)(var->positionX + rx * dst) - 1;
// 					ty = (int)(var->positionY + ry * dst) - 1;
// 					if (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT && var->map[ty][tx] == WALL)
// 					{
// 						//printf("WALL SW	%lf %lf dst %lf\t", rx, ry, pow(pow(rx * dst, 2) + pow(ry * dst, 2), 0.5));
// 						// printf("    seen pos %i %i ", -1 + (int)(var->positionX + rx * dst), -1 + (int)(var->positionY + ry * dst));
// 						t = createRGB(0,255,0);
// 						if (dst == v)
// 							t = createRGB(255,0,0);
// 						// write(1, "\n", 1);
// 						break;
// 					}
// 				}
// 			}
// 			if (dst == v)
// 				v += delta_v;
// 			else
// 				h += delta_h;
// 			if (dst > RENDER)
// 			{
// 				dst = RENDER + 1;
// 				break ;
// 			}
// 			// if (r > 14)
// 			// 	printf("%s DEBUG %s\n rx %lf ry %lf dst %lf\n", RED, NORMAL, rx, ry, dst);
// 		}
// 		// RD - dst -> wall height
// 		if (RENDER - dst < 0)
// 			continue ;
// 		int renhgt = ((RENDER -  dst) / RENDER) * HEIGHT;
// 		int draws = (HEIGHT / 2) - (renhgt / 2);
// 		for (int i = draws; i <= draws + renhgt; i++)
// 		{
// 			//printf("dst %lf  renhght %i start %i \n", dst, renhgt, draws);
// 			var->canvas[i][r] = t;
// 		}
// 	}
// 	// for (int i = 0; i < (int)strlen(var->canvas[0]); i++)
// 	// {
// 	// 	printf("\e[38;5;%im%i", (((i - (i % 10)) * 2) % 256), i % 10);
// 	// }
// }

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int32_t	main(int argc, char **argv)
{
	t_var	data;

	if (parse_input(argc, argv, &data))
		return (EXIT_FAILURE);
	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(data.mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(data.mlx, g_img, 0, 0);
	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
