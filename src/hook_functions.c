/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:05:40 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:05:45 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

bool	movement_keys(t_var *data);
void	handle_movement(t_var *data);
void	update_gifs(t_var *data);

void	loop_hook(void *param)
{
	t_var			*data;
	struct timeval	now;
	static long		last_frame;

	data = param;
	if (data->shutdown)
		cleanup(data);
	gettimeofday(&now, NULL);
	if (now.tv_sec > data->time.tv_sec)
	{
		data->time.tv_sec = now.tv_sec;
		last_frame = 0;
	}
	if ((now.tv_usec - last_frame) > data->config.framespeed)
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

void	update_gifs(t_var *data)
{
	if (data->gif[north])
		gif_next_frame(data->gif[north], data->textures[north]);
	if (data->gif[south])
		gif_next_frame(data->gif[south], data->textures[south]);
	if (data->gif[west])
		gif_next_frame(data->gif[west], data->textures[west]);
	if (data->gif[east])
		gif_next_frame(data->gif[east], data->textures[east]);
	if (data->gif[door])
		gif_next_frame(data->gif[door], data->textures[door]);
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
