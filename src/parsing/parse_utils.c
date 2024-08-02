#include "parsing.h"

void	print_data(t_var *data)
{
	int	i;

	ft_printf("NO %s\n", data->path_north);
	ft_printf("SO %s\n", data->path_south);
	ft_printf("WE %s\n", data->path_westh);
	ft_printf("EA %s\n", data->path_easth);
	printf("Ceiling\t%li\t\e[48;2;%i;%i;%im      \e[0m\n", \
					data->ceiling, (data->ceiling >> 24) % 256, \
					(data->ceiling >> 16) % 256, (data->ceiling >> 8) % 256);
	printf("Floor\t%li\t\e[48;2;%i;%i;%im      \e[0m\n", \
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
int32_t	incomplete(t_var *data)
{
	if (!data)
		return (1);
	if (data->path_north == NULL || \
		texture_init(data->path_north, data->texture_north) || \
		data->path_south == NULL || \
		texture_init(data->path_south, data->texture_south) || \
		data->path_westh == NULL || \
		texture_init(data->path_westh, data->texture_westh) || \
		data->path_easth == NULL || \
		texture_init(data->path_easth, data->texture_easth) || \
		data->player.x == 0 || \
		data->player.y == 0 || \
		(data->direct.x == 0 && \
		data->direct.y == 0) || \
		data->map_width == -1 || \
		data->map_height == -1 || \
		data->map == NULL || \
		data->ceiling == 42 || \
		data->floor == 42)
	{
		if (DEBUG == 1)
			ft_printf("One or more rendering components are missing/faulty\n");
		return (print_data(data), 1);
	}
	return (0);
}

int32_t	free_data(t_var *data)
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
	if (data->texture_north)
		mlx_delete_texture(data->texture_north);
	if (data->texture_south)
		mlx_delete_texture(data->texture_south);
	if (data->texture_easth)
		mlx_delete_texture(data->texture_easth);
	if (data->texture_westh)
		mlx_delete_texture(data->texture_westh);
	return (1);
}

int32_t	texture_init(char *file, mlx_texture_t *dest)
{
	int		fd;
	char	*end;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("File not found\n");
		}
		return (1);
	}
	close(fd);
	end = ft_strrchr(file, '.');
	if (!ft_strncmp(end, ".png", 4))
		dest = mlx_load_png(file);
	else
		return (1);
	if (!dest)
		return (1);
	return (0);
}

void	update_map_width(t_var *data, t_list *map_text)
{
	int32_t	len;
	char	*line;
	t_list	*text;

	if (!data || !line)
		return ;
	text = map_text;
	while (text)
	{
		line = (char *)text->content;
		len = ft_strlen(line);
		if (data->map_width < len)
			data->map_width = len;
		text = text->next;
	}
}
