/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:05:46 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 19:14:47 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

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
	data->config.map_opacity = 0;
	data->config.movement_speed = MOVEMENT_SPEED;
	data->config.turn_speed = TURN_SPEED;
	data->config.turn_mouse_speed = TURN_MOUSE_SPEED;
	data->config.framespeed = 50000;
}

void	init_game_bulk(t_var *data)
{
	if (!data)
		return ;
	data->shutdown = false;
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_westh = NULL;
	data->path_easth = NULL;
	data->path_door = NULL;
	data->textures[north] = NULL;
	data->textures[south] = NULL;
	data->textures[west] = NULL;
	data->textures[east] = NULL;
	data->textures[door] = NULL;
	data->has_door = false;
	data->player.x = 0;
	data->player.y = 0;
	data->direct.x = 0;
	data->direct.y = 0;
	data->gif[north] = NULL;
	data->gif[south] = NULL;
	data->gif[west] = NULL;
	data->gif[east] = NULL;
	data->gif[door] = NULL;
	gettimeofday(&data->time, NULL);
}

static void	init0(t_var *data)
{
	if (!data)
		return ;
	init_config(data);
	init_game_bulk(data);
	data->mouse = 0;
	data->settings = 0;
	data->rays = ft_calloc(data->config.width, sizeof(t_ray));
	data->map_width = -1;
	data->map_height = -1;
	data->map = NULL;
	data->ceiling = 42;
	data->floor = 42;
}

void	init(t_var *data)
{
	if (!data)
		return ;
	init0(data);
	data->_mlx = mlx_init(data->config.width, data->config.height, "MAP", true);
	if (!data->_mlx)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
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
