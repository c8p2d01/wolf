/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/09/09 11:57:20 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_var		*data;
	static void	(*s[11])(double, double, t_var *) = {norm_setting, \
	debug_setting, fov_setting, zoom_setting, style_setting, offset_setting, \
	height_setting, width_setting, move_setting, turn_setting, \
	turn_mouse_setting};

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

int	ray_color(t_var *data, int raynum, uint8_t opacity)
{
	double	fraction;

	fraction = (float)raynum / (data->config.width) + \
													data->config.color_offset;
	if (data->config.ray_style == 0)
		return (create_multi_gradient(\
			fmod(fraction, 1), \
			7, \
			0, 255, 255, 0, 0, 255, 255, 0, 255, \
			255, 0, 0, 255, 255, 0, 0, 255, 0, \
			0, 255, 255) << 8 | opacity);
	else if (data->config.ray_style == 1)
	{
		if (data->rays[raynum].wall == data->textures[north])
			return (create_rgba(42, 42, 255, opacity));
		else if (data->rays[raynum].wall == data->textures[south])
			return (create_rgba(255, 255, 42, opacity));
		else if (data->rays[raynum].wall == data->textures[east])
			return (create_rgba(255, 42, 42, opacity));
		else if (data->rays[raynum].wall == data->textures[west])
			return (create_rgba(42, 255, 42, opacity));
	}
	return (create_gradient_color(fmod(fraction, 1), new_color(0, 0, 0), \
			new_color(255, 255, 255)) << 8 | opacity);
}

void	debug_fov(t_var *data)
{
	t_vec2d	begin;
	t_vec2d	end;

	begin.x = data->rays[0].x;
	begin.y = data->rays[0].y;
	end.x = data->rays[data->config.width - 1].x;
	end.y = data->rays[data->config.width - 1].y;
	printf("FOV Angle %lf\n", (angle2d(begin, end) * 180) / PI);
}
