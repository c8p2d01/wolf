/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:31:46 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/06/06 17:21:19 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

/*
	\     \   /     /	
	 \  0-------#  /	0-------#0-------#0-------#
	  \ |   N   | /		|   N   ||   N   ||   N   |
	   X| W   E |X		| W   E || W   E || W   E |
	  / |   S   | \		|   S   ||   S   ||   S   |
	 /  #-------#  \	#-------##-------##-------#
	/     /   \     \	
	0 -> coordinate in map
	/ or \ -> incoming rays

	from different ray incomig angles different sides should be hit and tracked
	e.g. from south east walls should compare against coordinate + 1 in either direction

	check intersection only at raylengths where a wall could be
	-> find a vectorlength for the neares horizontal and neares vertical and from there on iterate in steps
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define HEIGHT 256

void	debug_stick(t_var *data)
{
	int	pos[2];

	mlx_get_mouse_pos(data->mlx, pos, pos + 1);
	printf("clicked window %s at position %i : %i\n",
		"map", pos[0], pos[1]);
}

void	hook(void *param)
{
	t_var	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		return ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		step(data, 1);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		step(data, -1);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		turn(data, 3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		turn(data, -3);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_TAB))
		memset(data->map_img->pixels, 128, data->map_img->width * data->map_img->height * sizeof(int));
	else if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		debug_stick(data);
	else
		return;
	rayMarcher(data);
}

void	init(t_var *data)
{
	if (!data)
		return ;
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_westh = NULL;
	data->path_easth = NULL;
	data->texture_north = NULL;
	data->texture_south = NULL;
	data->texture_westh = NULL;
	data->texture_easth = NULL;
	data->ply_x = 0;
	data->ply_y = 0;
	data->dir_x = 0;
	data->dir_y = 0;
	data->map_width = -1;
	data->map_height = -1;
	data->map = NULL;
	data->ceiling = -1;
	data->floor = -1;
}

int	bonus(t_var *data)
{
	data->mlx = mlx_init((int)(data->map_width * ZOOM),
					(int)(data->map_height * ZOOM), "MAP", true); //bonus
	if (!data->mlx)
		exit (EXIT_FAILURE);
	data->map_img = mlx_new_image(data->mlx, (int)(data->map_width * ZOOM), (int)(data->map_height * ZOOM));
	memset(data->map_img->pixels, 128, data->map_img->width * data->map_img->height * sizeof(int));
	mlx_image_to_window(data->mlx, data->map_img, 0, 0);
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_var	data;

	init(&data);
	if (parse_input(argc, argv, &data))
		exit (EXIT_FAILURE);
	print_data(&data);

	bonus(&data);

	rayMarcher(&data);

	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
