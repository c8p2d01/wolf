/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:09:01 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/05/21 20:14:11 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int32_t	argument_count(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("Wrong number of arguments\n");
		}
		return (1);
	}
	return (0);
}

int32_t	file_name(char **file)
{
	if (!file || !(*file))
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("Wrong number of arguments\n");
		}
		return (1);
	}
	if (ft_strlen(file[1]) < 4 || \
		ft_strncmp(&(file[1][ft_strlen(file[1]) - 4]), ".cub", 4) != 0)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("File name wrong\n");
		}
		return (1);
	}
	return (0);
}

int32_t	file_read(char *file, t_list **text, int *map_width)
{
	int		fd;
	char	*line;

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
	line = get_next_line(fd);
	while (line)
	{
		if (*map_width < (int)ft_strlen(line))
			*map_width = ft_strlen(line);
		ft_lstadd_back(text, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

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
	else
	{
		color = ft_atoi(values[0]) % 256 << 16 | \
			ft_atoi(values[1]) % 256 << 8 | \
			ft_atoi(values[2]) % 256;
	}
	free_2dstr(values);
	return (color);
}

int32_t	set_variable(t_var *data, char **elmnts)
{
	if (ft_strlen(elmnts[0]) == 2)
	{
		if (ft_strncmp(elmnts[0], "NO", 3))
			data->path_north = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "SO", 3))
			data->path_south = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "EA", 3))
			data->path_easth = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "WE", 3))
			data->path_westh = ft_strdup(elmnts[1]);
	}
	else if (ft_strlen(elmnts[0]) == 1)
	{
		if (elmnts[0][0] == 'F')
			data->floor = calculate_color(elmnts[1]);
		if (elmnts[0][0] == 'C')
			data->ceiling = calculate_color(elmnts[1]);
	}
	return (0);
}

int32_t	check_variable(t_var *data, char *line)
{
	char	**elmnts;
	int		i;

	elmnts = ft_split(line, ' ');
	if (!elmnts)
		return (1);
	if (ft_2d_array_size((void**)(void **)elmnts) != 2 || \
		ft_strlen(elmnts[0]) > 2 || \
		!((ft_strlen(elmnts[0]) == 2 && ft_strchr("OOEA", elmnts[0][1])) || \
			(ft_strlen(elmnts[0]) == 1 && ft_strchr("NSWEFC", elmnts[0][0]))))
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("Variable not identifyable\n");
			i = -1;
			while (elmnts[++i])
				ft_printf("Variable component NR %d: %s\n", i + 1, elmnts[i]);
			ft_printf("%s\n", ft_strchr("NSWEFC", elmnts[0][0]));
		}
		free_2dstr(elmnts);
		return (1);
	}
	return (set_variable(data, elmnts));
}

int32_t	parse_values(t_list *text, t_var *data, int *map_start)
{
	char	*line;

	while (text)
	{
		line = ft_strtrim((char *)text->content, "\t\n\v\f\r ");
		if (!line)
			return (1);
		if (ft_strlen(line) == 0)
		{
			text = text->next;
			*map_start = *map_start + 1;
			continue ;
		}
		if (ft_strchr("01", line[0]))
			break ;
		if (check_variable(data, line))
			return (free(line), 1);
		text = text->next;
		*map_start = *map_start + 1;
		free(line);
	}
	return (0);
}

int32_t	construct_map(t_var *data, t_list *text, int map_start)
{
	int32_t	i;

	i = 0;
	while (i++ < map_start)
		text = text->next;
	data->map_height = ft_lstsize(text) - map_start;
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		return (1);
	i = 0;
	while (text)
	{
		data->map[i] = (char *)text->content;
		text = text->next;
		i++;
	}
	return (0);
}

int32_t	init_player(t_var *data, char pov)
{
	printf("facing %c \n", pov);
	if (pov == 'N')
		{data->dir_x = -1;}
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

int32_t	find_player(t_var *data)
{
	int		height;
	char	*line;

	if (!data || !data->map)
		return (1);
	data->ply_x = 0;
	while (data->ply_x < data->map_height)
	{
		line = ft_strtrim(data->map[(int)data->ply_x], " 01234\n");
		if (ft_strlen(line))
			break ;
		free(line);
		data->ply_x += 1;
	}
	if (!ft_strchr("WSNE", line[0]))
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
			ft_printf("Erroneus char in map, map-line %d\n", (int)data->ply_x + 1);
		return (1);
	}
	if (line)
		free(line);
	return (extract_player(data));
}

char	*column_to_line(char **table, int index)
{
	int		l;
	char	*res;

	res = ft_calloc(ft_2d_array_size((void**)table) + 1, sizeof(char));
	l = 0;
	while (table[l])
	{
		if ((int)ft_strlen(table[l]) <= index || table[l][index] == '\n')
			res[l] = ' ';
		else
			res[l] = table[l][index];
		l++;
	}
	return (res);
}

char	**rotate_table(char **base)
{
	char	**res;
	int		i;
	int		l;
	int		ii;

	i = 0;
	l = 0;
	while (base[i])
	{
		if (l < (int)ft_strlen(base[i]))
			l = ft_strlen(base[i]);
		i++;
	}
	res = ft_calloc(l + 1, sizeof(char *));
	ii = 0;
	while (ii < l)
	{
		res[ii] = column_to_line(base, ii);
		ii++;
	}
	return (res);
}

int	map_checking_x(char **map)
{
	int		i[2];
	char	**subs;
	char	*trimm;

	i[0] = 0;
	while (i[0] >= 0 && map[i[0]])
	{
		subs = ft_split(map[i[0]], ' ');
		if (!subs)
			break ;
		i[1] = 0;
		while (i[0] >= 0 && subs[i[1]])
		{
			trimm = ft_strtrim(subs[i[1]], "0234");
			if (ft_strlen(subs[i[1]]) != ft_strlen(trimm))
				i[0] = -42;
			free(trimm);
			i[1]++;
		}
		free_2dstr(subs);
		i[0]++;
	}
	if (i[0] >= 0)
		return (0);
	return (1);
}

int	check_map(t_var *data)
{
	char	**rotated;
	int		res;

	rotated = rotate_table(data->map);
	data->map_width = ft_2d_array_size((void **)rotated) - 1; // unchecked '-1' validation testing required
	res = map_checking_x(data->map) + map_checking_x(rotated);
	free_2dstr(rotated);
	if (res)
	{
		if (DEBUG == 1)
			ft_printf_fd(2, "Invalid Map, only walled-in tiles are accepted\n");
		ft_printf_fd(2, "Error\n");
	}
	return (res);
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

int32_t	texture_init(char *file, mlx_texture_t* dest)
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
	return (0);
}

void	print_data(t_var *data)
{
	int	i;

	ft_printf("NO %s\n", data->texture_north);
	ft_printf("SO %s\n", data->texture_south);
	ft_printf("WE %s\n", data->texture_westh);
	ft_printf("EA %s\n", data->texture_easth);
	ft_printf("Floor %d\n", data->floor);
	ft_printf("Ceiling %d\n", data->ceiling);
	i = -1;
	// ft_printf("map location %p\n", data->map);
	ft_printf("map width %d\n", data->map_width * ZOOM);
	ft_printf("map height %d\n", data->map_height * ZOOM);
	while(data->map && data->map[++i])
		ft_printf("%s", data->map[i]);
	printf("\nPlayer Position %lf, %lf\n", data->ply_x, data->ply_y);
	printf("Player View %lf, %lf\n", data->dir_x, data->dir_y);
}

int32_t	incomplete(t_var *data)
{
	if (!data)
		return 1;
	if (data->path_north == NULL || \
		texture_init(data->path_north, data->texture_north) || \
		data->path_south == NULL || \
		texture_init(data->path_south, data->texture_south) || \
		data->path_westh == NULL || \
		texture_init(data->path_westh, data->texture_westh) || \
		data->path_easth == NULL || \
		texture_init(data->path_easth, data->texture_easth) || \
		data->ply_x == 0 || \
		data->ply_y == 0 || \
		(data->dir_x == 0 && \
		data->dir_y == 0) || \
		data->map_width == -1 || \
		data->map_height == -1 || \
		data->map == NULL || \
		data->ceiling < 0 || \
		data->floor < 0)
	{
		if (DEBUG == 1)
			ft_printf("One or more rendering components are missing or faulty\n");
		return (1);
	}
	return (0);
}

int32_t	parse_input(int argc, char **argv, t_var *data)
{
	t_list	*text;
	int32_t	map_width;
	int32_t	map_start;

	if (argument_count(argc))
		return (1);
	if (file_name(argv))
		return (1);
	map_width = 0;
	map_start = 0;
	text = NULL;
	if (file_read(argv[1], &text, &map_width))
		return (1);
	if (parse_values(text, data, &map_start))
		return (ft_lstclear(&text, free), 1);
	if (construct_map(data, text, map_start))
		return (ft_lstclear(&text, free), 1);
	ft_lstclear(&text, NULL);
	if (check_map(data))
		return(free_data(data));
	if (find_player(data))
		return(free_data(data));
	if (incomplete(data))
		return(free_data(data));
	return (0);
}
