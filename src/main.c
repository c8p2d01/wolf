/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:31:46 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/07/23 19:09:59 by cdahlhof         ###   ########.fr       */
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
	e.g. from south east walls should compare against coordinate + 1 in either
	direction

	check intersection only at raylengths where a wall could be
	-> find a vectorlength for the neares horizontal and neares vertical and
	from there on iterate in steps
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

// void	debug_stick(t_var *data)
// {
// 	int	pos[2];

// 	mlx_get_mouse_pos(data->_mlx, pos, pos + 1);
// 	printf("clicked window %s at position %i : %i\n",
// 		"map", pos[0], pos[1]);
// }

void	hold_hook(void *param)
{
	t_var	*data;

	data = param;
	if (mlx_is_key_down(data->_mlx, MLX_KEY_UP) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_A) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_DOWN) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_D) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(data->_mlx, MLX_KEY_UP))
			straight(data, PRESS);
		if (mlx_is_key_down(data->_mlx, MLX_KEY_DOWN))
			straight(data, MINUS);
		if (mlx_is_key_down(data->_mlx, MLX_KEY_D))
			strafe(data, PRESS);
		if (mlx_is_key_down(data->_mlx, MLX_KEY_A))
			strafe(data, MINUS);
		if (mlx_is_key_down(data->_mlx, MLX_KEY_LEFT))
			turn(data, LEFT);
		if (mlx_is_key_down(data->_mlx, MLX_KEY_RIGHT))
			turn(data, RIGHT);
		memset(data->map_render_img->pixels, 0, data->map_render_img->width * \
								data->map_render_img->height * sizeof(int));
		apply_movement(data);
		if (data->map_visibility)
			draw_player_triangle(data);
		data->move.x = 0;
		data->move.y = 0;
	}
}

void	press_hook(mlx_key_data_t key, void *param)
{
	t_var	*data;

	data = param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(data->_mlx);
		free_data(data);
		return ;
	}
	else if (key.action && (key.key == MLX_KEY_LEFT \
							|| key.key == MLX_KEY_RIGHT))
	{
		if (key.key == MLX_KEY_LEFT)
			turn(data, LEFT);
		if (key.key == MLX_KEY_RIGHT)
			turn(data, RIGHT);
	}
	else if (key.key == MLX_KEY_M)
	{
		if (mlx_is_key_down(data->_mlx, MLX_KEY_LEFT_SHIFT))
			data->map_visibility = 0;
		else
			data->map_visibility = 1;
		filler(data);
		draw_player_triangle(data);
	}
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
	data->player.x = 0;
	data->player.y = 0;
	data->direct.x = 0;
	data->direct.y = 0;
	data->map_width = -1;
	data->map_height = -1;
	data->map = NULL;
	data->ceiling = 42;
	data->floor = 42;
	data->map_visibility = 1;
	data->_mlx = mlx_init(WIDTH, HEIGHT, "MAP", true); //minimap
	if (!data->_mlx)
		exit (EXIT_FAILURE);
	data->main_static_img = mlx_new_image(data->_mlx, WIDTH, HEIGHT);
	data->main_render_img = mlx_new_image(data->_mlx, WIDTH, HEIGHT);
	memset(data->main_render_img->pixels, 0, WIDTH * HEIGHT * sizeof(int));
}

int	minimap(t_var *data)
{
	data->map_layout_img = mlx_new_image(data->_mlx, (data->map_width * ZOOM), (data->map_height * ZOOM));
	data->map_render_img = mlx_new_image(data->_mlx, (data->map_width * ZOOM), (data->map_height * ZOOM));
	filler(data);
	draw_player_triangle(data);

	mlx_image_to_window(data->_mlx, data->map_layout_img, 0, 0);
	mlx_image_to_window(data->_mlx, data->map_render_img, 0, 0);
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_var	data;

	init(&data);
	if (parse_input(argc, argv, &data))
	{
		ft_printf("parsing issues\n");
		exit (42);
	}
	print_data(&data);

	mlx_image_to_window(data._mlx, data.main_static_img, 0, 0);
	mlx_image_to_window(data._mlx, data.main_render_img, 0, 0);
	minimap(&data);
	floor_ceiling(&data);

	mlx_loop_hook(data._mlx, &hold_hook, &data);
	// mlx_mouse_hook(data.main_mlx, )
	mlx_key_hook(data._mlx, &press_hook, &data);
	mlx_loop(data._mlx);
	mlx_terminate(data._mlx);
	return (EXIT_SUCCESS);
}
