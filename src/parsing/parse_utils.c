/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:28:49 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:29:50 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_data(t_var *data)
{
	int	i;

	printf("Ceiling\t%i\t\e[48;2;%i;%i;%im      \e[0m\n", \
					data->ceiling, (data->ceiling >> 24) % 256, \
					(data->ceiling >> 16) % 256, (data->ceiling >> 8) % 256);
	printf("Floor\t%i\t\e[48;2;%i;%i;%im      \e[0m\n", \
						data->floor, (uint8_t)data->floor, \
						(data->floor >> 16) % 256, (data->floor >> 8) % 256);
	ft_printf("map width %d\n", data->map_width * ZOOM);
	ft_printf("map height %d\n", data->map_height * ZOOM);
	print_map(data);
	printf("\nPlayer Position %lf, %lf\n", data->player.x, data->player.y);
	printf("Player View %lf, %lf\n", data->direct.x, data->direct.y);
}

/**
 * check if any necessary value is still empty
 */
bool	checks(t_var *data)
{
	if (data->path_north == NULL || \
		texture_init(data->path_north, &data->textures[north]) || \
		data->path_south == NULL || \
		texture_init(data->path_south, &data->textures[south]) || \
		data->path_westh == NULL || \
		texture_init(data->path_westh, &data->textures[west]) || \
		data->path_easth == NULL || \
		texture_init(data->path_easth, &data->textures[east]) || \
		data->has_door && (data->path_door == NULL || \
		texture_init(data->path_door, &data->textures[door])) || \
		data->player.x == 0 || \
		data->player.y == 0 || \
		(data->direct.x == 0 && \
		data->direct.y == 0) || \
		data->map_width == -1 || \
		data->map_height == -1 || \
		data->map == NULL || \
		data->ceiling == 42 || \
		data->floor == 42)
		return (1);
	return (0);
}

int32_t	incomplete(t_var *data)
{
	if (!data)
		return (1);
	if (checks(data))
	{
		if (DEBUG == 1)
			ft_printf("One or more rendering components are missing/faulty\n");
		return (print_data(data), 1);
	}
	return (0);
}

int32_t	free_half_data(t_var *data)
{
	free_2dstr(data->map);
	if (data->path_north)
		free(data->path_north);
	if (data->path_south)
		free(data->path_south);
	if (data->path_easth)
		free(data->path_easth);
	if (data->path_westh)
		free(data->path_westh);
	return (1);
}

int32_t	free_data(t_var *data)
{
	if (data->textures[north])
		mlx_delete_texture(data->textures[north]);
	if (data->textures[south])
		mlx_delete_texture(data->textures[south]);
	if (data->textures[east])
		mlx_delete_texture(data->textures[east]);
	if (data->textures[west])
		mlx_delete_texture(data->textures[west]);
	if (data->textures[door])
		mlx_delete_texture(data->textures[door]);
	if (data->rays)
		free(data->rays);
	ft_lstclear(&data->text, free);
	if (data->map)
		free(data->map);
	return (1);
}
