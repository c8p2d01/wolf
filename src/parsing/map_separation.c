#include "../../inc/parsing.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	non_space_character(t_var *data, char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map && map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != ' ')
				return (printf("Map cannot be separated by spaces\n"), 1);
			y++;
		}
		x++;
	}
	return (0);
}

int	check_space_separation(t_var *data)
{
	int			i;
	t_intvctr	position;
	t_intvctr	map_size;
	char		**map_cpy;

	i = 0;
	map_cpy = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!map_cpy)
		return (1);
	while (i < data->map_height)
	{
		if (!data->map[i])
			break ;
		map_cpy[i] = ft_strdup(data->map[i]);
		i++;
	}
	i = 0;
	while (map_cpy[0][i] && map_cpy[0][i] != '1')
		i++;
	map_size.x = data->map_height;
	map_size.y = data->map_width;
	fill_iter(map_cpy, map_size, 0, i);
	if (non_space_character(data, map_cpy))
		return (free_split(map_cpy), 1);
	return (free_split(map_cpy), 0);
}
