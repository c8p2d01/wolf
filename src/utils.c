/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:09:01 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/07/22 17:05:42 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int32_t	create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	deg_2_rad(float degree)
{
	return (degree * (PI / 180));
}

char	map_char(t_var *data, int y, int x)
{
	if (0 > x || x >= data->map_height || \
		0 > y || y >= data->map_width)
	{
		return ('1');
	}
	return (data->map[x][y]);
}

t_var	**proto_global(void)
{
	static t_var	*data;

	return (&data);
}

void	cleanup(t_var *data)
{
	free_data(data);
	mlx_close_window(data->_mlx);
	exit(1);
}
