/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:31:40 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:31:42 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	print_setting(t_var *data)
{
	static const char	*settings[] = {
		"NORMAL", "DEBUG", "FOV", "ZOOM", "RAY_STYLE", "OFFSET", "HEIGHT", \
		"WIDTH", "MOVEMENT_SPEED", "TURN_SPEED", "TURN_MOUSE_SPEED", NULL
	};
	int					i;

	printf("\e[1;1H\e[2J\tSettings Menu\n\t");
	i = 0;
	while (i < ft_2d_array_size((void **)settings))
	{
		printf("   ");
		if (i == data->config.setting)
			printf("\e[38;2;42;255;42m[");
		printf("%s", settings[i]);
		if (i == data->config.setting)
			printf("]\e[0m");
		printf("   ");
		i++;
	}
	printf("\n");
}

void	print_map_chars(char c)
{
	if (c == '1')
		printf("\e[38;2;%i;%i;%im", (MAP_WALL >> 16) % 256, \
						(MAP_WALL >> 8) % 256, (MAP_WALL >> 0) % 256);
	if (c == '2')
		printf("\e[38;2;%i;%i;%im", (MAP_DOOR >> 16) % 256, \
						(MAP_DOOR >> 8) % 256, (MAP_DOOR >> 0) % 256);
	if (c == '3')
		printf("\e[38;2;%i;%i;%im", (MAP_OPEN >> 16) % 256, \
						(MAP_OPEN >> 8) % 256, (MAP_OPEN >> 0) % 256);
	else if (ft_strchr("0NESW", c))
		printf("\e[38;2;%i;%i;%im", (MAP_GRND >> 16) % 256, \
						(MAP_GRND >> 8) % 256, (MAP_GRND >> 0) % 256);
}

void	print_map(t_var *data)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	while (x < data->map_height)
	{
		y = 0;
		while (y < data->map_width)
		{
			c = map_char(data, y, x);
			print_map_chars(c);
			printf("%c\e[0m", c);
			y++;
		}
		x++;
		printf("\n");
	}
}
