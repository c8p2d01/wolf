
#include "parsing.h"

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
		line = ft_strtrim(data->map[i], " 01234\n");
		if (ft_strlen(line))
		{
			c = line[0];
			data->ply_x = i;
			data->dir_x += 42 * ft_strlen(line);
		}
		free(line);
		i -= -1;
	}
	if (data->dir_x != 42 || !ft_strchr("WSNE", c))
		return (ft_printf("Error\nErroneus char in map\n") * 0 + 1);
	return (extract_player(data));
}

int32_t	extract_player(t_var *data)
{
	char	*line;
	char	c;

	line = data->map[(int)data->ply_x];
	c = '0';
	if (ft_strchr(line, 'N'))
		c = 'N';
	if (ft_strchr(line, 'S'))
		c = 'S';
	if (ft_strchr(line, 'W'))
		c = 'W';
	if (ft_strchr(line, 'E'))
		c = 'E';
	data->ply_y = ft_strchr(line, c) - line;
	data->ply_x *= ZOOM;
	data->ply_y *= ZOOM;
	data->ply_x += ZOOM / 2;
	data->ply_y += ZOOM / 2;
	return (init_player(data, c));
}

int32_t	init_player(t_var *data, char pov)
{
	printf("facing %c \n", pov);
	if (pov == 'N')
		data->dir_x = -1;
	else if (pov == 'S')
		data->dir_x = 1;
	else if (pov == 'W')
		data->dir_y = -1;
	else if (pov == 'E')
		data->dir_y = 1;
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
