/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_variables_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:27:27 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	color_unacceptable(t_var *data, char **elmnts)
{
	if (!ft_strncmp(elmnts[0], "F", 2))
	{
		data->floor = calculate_color(elmnts[1]);
		if (data->floor == -1)
			return (1);
	}
	else if (!ft_strncmp(elmnts[0], "C", 2))
	{
		data->ceiling = calculate_color(elmnts[1]);
		if (data->ceiling == -1)
			return (1);
	}
	return (0);
}

int	color_identification(t_var *data, char **elmnts)
{
	if (color_unacceptable(data, elmnts))
		return (1);
	else if (!ft_strncmp(elmnts[0], "F", 2))
		data->floor = calculate_color(elmnts[1]);
	else
		data->ceiling = calculate_color(elmnts[1]);
	return (0);
}

/**
 * assign values to the placeholders in 'data' according to indicators parsed
 */
int32_t	set_variable(t_var *data, char **elmnts)
{
	if (ft_strlen(elmnts[0]) <= 2)
	{
		if (!ft_strncmp(elmnts[0], "NO", 3))
			data->path_north = ft_strdup(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "SO", 3))
			data->path_south = ft_strdup(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "EA", 3))
			data->path_easth = ft_strdup(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "WE", 3))
			data->path_westh = ft_strdup(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "DO", 3))
			data->path_door = ft_strdup(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "F", 2) || \
		!ft_strncmp(elmnts[0], "C", 2))
		{
			if (color_identification(data, elmnts))
				return (1);
		}
		else
			return (free_2dstr(elmnts), 1);
	}
	else
		return (free_2dstr(elmnts), 1);
	free_2dstr(elmnts);
	return (0);
}

int	nbr_out_of_bounds(char **values)
{
	if ((ft_atoi(values[0]) < 0 || ft_atoi(values[0]) > 255) || \
	(ft_atoi(values[1]) < 0 || ft_atoi(values[1]) > 255) || \
	(ft_atoi(values[2]) < 0 || ft_atoi(values[2]) > 255))
		return (1);
	return (0);
}

/**
 * extract the color out of the text format rrr,ggg,bbb
 * into one integer where byte represents one color (+alpha value)
 */
int32_t	calculate_color(char *rgb)
{
	char	**values;
	int		color;

	if (!rgb)
		return (0);
	values = ft_split(rgb, ',');
	if (!values || ft_2d_array_size((void **)values) != 3)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
			ft_printf("Color Format Error\n");
		return (-1);
	}
	else if (nbr_out_of_bounds(values))
	{
		free_2dstr(values);
		return (-1);
	}
	else
	{
		color = (ft_atoi(values[0]) % 256) << 24 |(ft_atoi(values[1]) % 256) \
								<< 16 | (ft_atoi(values[2]) % 256) << 8 | 255;
	}
	free_2dstr(values);
	return (color);
}
