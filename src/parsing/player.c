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
			data->player.x = i;
			data->direct.x += 42 * ft_strlen(line);
		}
		free(line);
		i -= -1;
	}
	if (data->direct.x != 42 || !ft_strchr("WSNE", c))
		return (ft_printf("Error\nErroneus char in map\n") * 0 + 1);
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
	return (init_player(data, c));
}

int32_t	init_player(t_var *data, char pov)
{
	data->direct.x = 0;
	printf("facing %c \n", pov);
	if (pov == 'N')
		data->direct.x = -1.001;
	else if (pov == 'S')
		data->direct.x = 1.001;
	else if (pov == 'W')
		data->direct.y = -1.001;
	else if (pov == 'E')
		data->direct.y = 1.001;
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
