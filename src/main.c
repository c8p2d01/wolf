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

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_var		*data;
	static void	(*s[11])(double, double, t_var *) = {norm_setting, \
	debug_setting, fov_setting, zoom_setting, style_setting, offset_setting, \
	height_setting, width_setting, test_setting, test_setting, test_setting};

	data = param;
	if (data->settings == 1)
	{
		if (mlx_is_key_down(data->_mlx, MLX_KEY_LEFT_SHIFT))
		{
			data->config.setting += (int)xdelta;
			i_limit(&data->config.setting, 0, N_SETTINGS);
			print_setting(data);
			return ;
		}
		s[data->config.setting](xdelta, ydelta, data);
	}
}

bool	movement_keys(t_var *data)
{
	if (mlx_is_key_down(data->_mlx, MLX_KEY_UP) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_W) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_A) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_DOWN) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_S) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_D) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(data->_mlx, MLX_KEY_RIGHT))
		return (1);
	return (0);
}

void	handle_movement(t_var *data)
{
	if (mlx_is_key_down(data->_mlx, MLX_KEY_UP) \
				|| mlx_is_key_down(data->_mlx, MLX_KEY_W))
		straight(data, PRESS);
	if (mlx_is_key_down(data->_mlx, MLX_KEY_DOWN) \
				|| mlx_is_key_down(data->_mlx, MLX_KEY_S))
		straight(data, MINUS);
	if (mlx_is_key_down(data->_mlx, MLX_KEY_D))
		strafe(data, PRESS);
	if (mlx_is_key_down(data->_mlx, MLX_KEY_A))
		strafe(data, MINUS);
	if (mlx_is_key_down(data->_mlx, MLX_KEY_LEFT))
		turn(data, LEFT);
	if (mlx_is_key_down(data->_mlx, MLX_KEY_RIGHT))
		turn(data, RIGHT);
	apply_movement(data);
	data->move.x = 0;
	data->move.y = 0;
}

void	update_gifs(t_var *data)
{
	if (data->gif[0])
		gif_next_frame(data->gif[0], data->texture_north);
	if (data->gif[1])
		gif_next_frame(data->gif[1], data->texture_south);
	if (data->gif[2])
		gif_next_frame(data->gif[2], data->texture_westh);
	if (data->gif[3])
		gif_next_frame(data->gif[3], data->texture_easth);
	if (data->gif[4])
		gif_next_frame(data->gif[4], data->texture_door);
}

void	hold_hook(void *param)
{
	t_var			*data;
	struct timeval	now;
	static long		last_frame;

	data = param;
	gettimeofday(&now, NULL);
	if (now.tv_sec > data->time.tv_sec)
	{
		data->time.tv_sec = now.tv_sec;
		last_frame = 0;
	}
	if ((now.tv_usec - last_frame) > 10000 * data->gif[4]->gce.delay)
	{
		last_frame = now.tv_usec;
		update_gifs(data);
		render_view(data);
		draw_fov_lines(data);
		draw_player_triangle(data);
	}
	if (movement_keys(data))
		handle_movement(data);
}

void	toggle_map(mlx_key_data_t key, t_var *data)
{
	if (data->config.map_opacity == 0)
	{
		data->config.map_opacity = MAP_OPACITY % 256;
		filler(data);
		draw_player_triangle(data);
		draw_fov_lines(data);
	}
	else
	{
		data->config.map_opacity = 0;
		ft_memset(data->map_render_img->pixels, 0, \
			data->map_render_img->width * \
			data->map_render_img->height * sizeof(int));
		ft_memset(data->map_layout_img->pixels, 0, \
			data->map_layout_img->width * \
			data->map_layout_img->height * sizeof(int));
	}
}

void	toggle_key_hook(mlx_key_data_t key, t_var *data)
{
	if (key.action == 1)
	{
		if (key.key == MLX_KEY_M)
			toggle_map(key, data);
		else if (key.key == MLX_KEY_G)
		{
			data->settings = !data->settings;
			if (data->settings)
				print_setting(data);
		}
		else if (key.key == MLX_KEY_SPACE)
			toggle_doors(key, data);
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
	else
		toggle_key_hook(key, data);
}

void	init_config(t_var *data)
{
	if (!data)
		return ;
	data->config.setting = 0;
	data->config.fov = FOV;
	i_limit(&data->config.fov, 1, 179);
	data->config.width = WIDTH;
	data->config.height = HEIGHT;
	data->config.zoom = ZOOM;
	data->config.color_offset = 0;
	data->config.ray_style = 1;
	data->config.map_opacity = MAP_OPACITY % 256;
}

void	init_game_bulk(t_var *data)
{
	if (!data)
		return ;
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_westh = NULL;
	data->path_easth = NULL;
	data->path_door = NULL;
	data->texture_north = NULL;
	data->texture_south = NULL;
	data->texture_westh = NULL;
	data->texture_easth = NULL;
	data->texture_door = NULL;
	data->player.x = 0;
	data->player.y = 0;
	data->direct.x = 0;
	data->direct.y = 0;
	data->gif[0] = NULL;
	data->gif[1] = NULL;
	data->gif[2] = NULL;
	data->gif[3] = NULL;
	data->gif[4] = NULL;
	gettimeofday(&data->time, NULL);
}

void	init(t_var *data)
{
	if (!data)
		return ;
	init_config(data);
	init_game_bulk(data);
	data->settings = 0;
	data->rays = ft_calloc(data->config.width, sizeof(t_ray));
	data->map_width = -1;
	data->map_height = -1;
	data->map = NULL;
	data->ceiling = 42;
	data->floor = 42;
	data->_mlx = mlx_init(data->config.width, data->config.height, "MAP", true);
	if (!data->_mlx)
		exit (EXIT_FAILURE);
	data->main_static_img = mlx_new_image(data->_mlx, data->config.width, \
														data->config.height);
	data->main_render_img = mlx_new_image(data->_mlx, data->config.width, \
														data->config.height);
	ft_memset(data->main_static_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	ft_memset(data->main_render_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	mlx_image_to_window(data->_mlx, data->main_static_img, 0, 0);
	mlx_image_to_window(data->_mlx, data->main_render_img, 0, 0);
}

int	minimap(t_var *data)
{
	data->map_layout_img = mlx_new_image(data->_mlx, (data->map_width * \
					data->config.zoom), (data->map_height * data->config.zoom));
	data->map_render_img = mlx_new_image(data->_mlx, (data->map_width * \
					data->config.zoom), (data->map_height * data->config.zoom));
	mlx_image_to_window(data->_mlx, data->map_layout_img, 0, 0);
	mlx_image_to_window(data->_mlx, data->map_render_img, 0, 0);
	zoom_setting(0, 0, data);
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_var	data;

	init(&data);
	*proto_global() = &data;
	if (parse_input(argc, argv, &data))
	{
		ft_printf("parsing issues\n");
		exit (42);
	}
	print_data(&data);
	minimap(&data);
	floor_ceiling(&data);
	mlx_loop_hook(data._mlx, &hold_hook, &data);
	mlx_scroll_hook(data._mlx, &scroll_hook, &data);
	mlx_key_hook(data._mlx, &press_hook, &data);
	mlx_loop(data._mlx);
	mlx_terminate(data._mlx);
	return (EXIT_SUCCESS);
}
