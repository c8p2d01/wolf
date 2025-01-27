/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:32:34 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:32:36 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	style_setting(double xdelta, double ydelta, t_var *data)
{
	printf("\e[3;1H\e[9J");
	data->config.ray_style += 1;
	i_limit(&data->config.ray_style, 0, 3);
	data->config.ray_style %= 3;
	printf("chosen Style %d", data->config.ray_style);
	memset(data->map_render_img->pixels, 0, data->map_render_img->width * \
							data->map_render_img->height * sizeof(int));
}

void	offset_setting(double xdelta, double ydelta, t_var *data)
{
	printf("\e[3;1H\e[9J");
	if (data->config.ray_style == 0)
	{
		data->config.color_offset += 4 * ydelta / data->config.width;
		while (data->config.color_offset < 0)
			data->config.color_offset += 1;
		data->config.color_offset = fmod(data->config.color_offset, 1);
		memset(data->map_render_img->pixels, 0, \
			data->map_render_img->width * \
			data->map_render_img->height * sizeof(int));
	}
	else
		printf("Setting only adjustable, when RAY_STYLE is set \
															to rainbow mode\n");
}

void	height_setting(double xdelta, double ydelta, t_var *data)
{
	int32_t	sh;
	int32_t	sw;

	mlx_get_monitor_size(0, &sw, &sh);
	printf("\e[3;1H\e[9J");
	data->config.height += (int)ydelta;
	i_limit(&data->config.height, 1, sh);
	mlx_set_window_size(data->_mlx, data->config.width, data->config.height);
	mlx_resize_image(data->main_static_img, data->config.width, \
														data->config.height);
	mlx_resize_image(data->main_render_img, data->config.width, \
														data->config.height);
	memset(data->main_static_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	floor_ceiling(data);
	zoom_setting(0, 0, data);
}

void	width_setting(double xdelta, double ydelta, t_var *data)
{
	int32_t	sh;
	int32_t	sw;

	mlx_get_monitor_size(0, &sw, &sh);
	printf("\e[3;1H\e[9J");
	if (ydelta > 0 && data->config.width >= WIDTH)
	{
		data->rays = ft_realloc(data->rays, \
		data->config.width * sizeof(t_ray), (int)ydelta * sizeof(t_ray));
	}
	data->config.width += (int)ydelta;
	i_limit(&data->config.width, 1, sw);
	mlx_set_window_size(data->_mlx, data->config.width, data->config.height);
	mlx_resize_image(data->main_static_img, data->config.width, \
														data->config.height);
	mlx_resize_image(data->main_render_img, data->config.width, \
														data->config.height);
	memset(data->main_static_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	memset(data->main_render_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	floor_ceiling(data);
	zoom_setting(0, 0, data);
}
