/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/07/23 20:16:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rendering.h"

void	draw_line_b(t_var *data, int height, int raynum)
{
	uint8_t			*pixel;
	mlx_texture_t	*tex;
	int				x = raynum;
	int				y;
	double			perc_x;
	double			perc_y;
	int				midpoint;

	if (!data || !data->rays || !(&(data->rays[raynum])))
		return ;
	tex = data->rays[raynum].wall;
	if (!tex || !tex->pixels || !tex->width || !tex->height || !tex->bytes_per_pixel)
	{
		return ;
	}
	midpoint = (data->main_render_img->height / 2) - (height / 2);
	for(int y = 0; y < height; y++)
	{
		if (!data || !data->rays || midpoint + y < 0 || midpoint + y > data->main_render_img->height)
			continue ;
		
		perc_y = (double)y / (double)height;
		perc_x = data->rays[raynum].wall_percent;
		lf_limit(&perc_x, 0, 1);
		lf_limit(&perc_y, 0, 1);
		pixel = &tex->pixels[((int)(perc_x * (int)tex->width) + 
				(int)(perc_y * tex->height) * (int)tex->width) 
				* (int)tex->bytes_per_pixel];
		prot_put_pixel(data->main_render_img,
			x,
			midpoint + y,
			create_rgba(pixel[0], pixel[1], pixel[2], 255));
	}
}
