/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:34:28 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 19:21:50 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int32_t	find_player(t_var *data)
{
	char	c;
	int		i;
	char	*line;

	c = 48;
	i = 0;
	if (!data || !data->map)
		return (1);
	while (i < data->map_height)
	{
		line = ft_strtrim(data->map[i], CHARSET);
		if (ft_strlen(line))
		{
			c = line[0];
			data->player.x = i;
			data->direct.x += 42 * ft_strlen(line);
		}
		if (ft_strchr(data->map[i], '2') || ft_strchr(data->map[i], '3'))
			data->direct.x += check_door(i, data);
		free(line);
		i -= -1;
	}
	if (data->direct.x != 42 || !ft_strchr("WSNE", c))
		return (ft_printf("Error\nErroneous char in map or no player found\n"));
	return (extract_player(data));
}

int32_t	extract_player(t_var *data)
{
	char	*line;
	char	c;

	line = data->map[(int)data->player.x];
	c = '0';
	if (ft_strchr(line, 'N'))
		c = 'N';
	if (ft_strchr(line, 'S'))
		c = 'S';
	if (ft_strchr(line, 'W'))
		c = 'W';
	if (ft_strchr(line, 'E'))
		c = 'E';
	data->player.y = ft_strchr(line, c) - line;
	data->player.x *= ZOOM;
	data->player.y *= ZOOM;
	data->player.x += ZOOM / 2;
	data->player.y += ZOOM / 2;
	data->player.x += 0.0001;
	data->player.y += 0.0001;
	return (init_player(data, c));
}

int32_t	init_player(t_var *data, char pov)
{
	data->direct.x = 0;
	if (pov == 'N')
		data->direct.x = -1.01;
	else if (pov == 'S')
		data->direct.x = 1.01;
	else if (pov == 'W')
		data->direct.y = -1.01;
	else if (pov == 'E')
		data->direct.y = 1.01;
	else
	{
		if (DEBUG == 1)
		{
			ft_printf("Player not found\n");
		}
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
