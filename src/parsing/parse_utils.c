#include "../../inc/parsing.h"

void	print_data(t_var *data)
{
	int	i;

	// ft_printf("NO %s\t%p\n", data->path_north, data->texture_north);
	// ft_printf("SO %s\t%p\n", data->path_south, data->texture_south);
	// ft_printf("WE %s\t%p\n", data->path_westh, data->texture_westh);
	// ft_printf("EA %s\t%p\n", data->path_easth, data->texture_easth);
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
		data->path_door == NULL || \
		texture_init(data->path_door, &data->textures[door]) || \
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
	free_2dstr(data->map);
	// if (data->path_north)
	// 	free(data->path_north);
	// if (data->path_south)
	// 	free(data->path_south);
	// if (data->path_easth)
	// 	free(data->path_easth);
	// if (data->path_westh)
	// 	free(data->path_westh);
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
	return (1);
}

int	get_texure_pos(t_var *data, char *tex)
{
	char	*paths[5];
	int		i;

	paths[0] = data->path_north;
	paths[1] = data->path_south;
	paths[2] = data->path_westh;
	paths[3] = data->path_easth;
	paths[4] = data->path_door;
	i = 0;
	while (i < 5)
	{
		if (paths[i] == tex)
			break ;
		i++;
	}
	if (i < 5)
		return (i);
	return (0);
}

int32_t	gif_init(char *file, mlx_texture_t **dest)
{
	t_var	*data;
	int		gif_i;

	data = *proto_global();
	gif_i = get_texure_pos(data, file);
	data->gif[gif_i] = gd_open_gif(file);
	if (!data->gif[gif_i])
		printf("gif error\n");
	*dest = ft_calloc(1, sizeof(mlx_texture_t));
	(*dest)->height = data->gif[gif_i]->height;
	(*dest)->width = data->gif[gif_i]->width;
	(*dest)->bytes_per_pixel = 3;
	(*dest)->pixels = ft_calloc((*dest)->height * (*dest)->width, \
												(*dest)->bytes_per_pixel + 1);
	ft_memset((*dest)->pixels, 128, (*dest)->height * (*dest)->width * \
												(*dest)->bytes_per_pixel + 1);
	gif_next_frame(data->gif[gif_i], *dest);
	return (0);
}

int32_t	texture_init(char *file, mlx_texture_t **dest)
{
	int		fd;
	char	*end;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
			ft_printf("File not found\n");
		return (1);
	}
	close(fd);
	end = ft_strrchr(file, '.');
	if (!ft_strncmp(end, ".png", 4))
		*dest = mlx_load_png(file);
	else if (!ft_strncmp(end, ".gif", 4))
		gif_init(file, dest);
	else
		return (1);
	if (!dest)
		return (1);
	free(file);
	return (0);
}

void	update_map_width(t_var *data, t_list *map_text)
{
	int32_t	len;
	char	*line;
	t_list	*text;

	if (!data || !map_text)
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
