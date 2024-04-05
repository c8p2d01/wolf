/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:09:01 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/04/04 22:52:04 by cdahlhof         ###   ########.fr       */
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
		if (*map_width < ft_strlen(line))
			*map_width = ft_strlen(line);
		ft_lstadd_back(text, ft_lstnew(line));
		line = get_next_line(fd);
	}
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
		{
			ft_printf("Color Format Error\n");
		}
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
			data->texture_north = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "SO", 3))
			data->texture_south = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "EA", 3))
			data->texture_easth = ft_strdup(elmnts[1]);
		if (ft_strncmp(elmnts[0], "WE", 3))
			data->texture_westh = ft_strdup(elmnts[1]);
	}
	else if (ft_strlen(elmnts[0]) == 1)
	{
		if (elmnts[0][0] == 'F')
			data->floor = calculate_color(elmnts[1]);
		if (elmnts[0][0] == 'C')
			data->floor = calculate_color(elmnts[1]);
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
	if (ft_2d_array_size((void **)elmnts) != 2 || \
		ft_strlen(elmnts[0]) > 2 || \
		!(ft_strlen(elmnts[0]) == 2 && ft_strchr("OOEA", elmnts[0][1]) || \
			ft_strlen(elmnts[0]) == 1 && ft_strchr("NSWEFC", elmnts[0][0])))
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
		{
			ft_printf("Variable not identifyable\n");
			i = 0;
			while (elmnts[i])
				ft_printf("Variable component NR %d: %s\n", i + 1, elmnts[i++]);
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

	printf("LAL\n");
	while (text)
	{
		line = ft_strtrim((char *)text->content, "\t\n\v\f\r ");
		if (!line)
			return (1);
		printf(">%s\n<", line);
		if (ft_strlen(line) == 0)
		{
			text = text->next;
			continue ;
		}
		if (ft_strchr("01", line[0]))
			break ;
		if (check_variable(data, line))
		{
			free(line);
			return (1);
		}
		text = text->next;
		*map_start = *map_start + 1;
		free(line);
	}
	return (0);
}

int32_t	construct_map(t_var *data, t_list *text, int map_width, int map_start)
{
	int32_t	i;
	int32_t	map_height;
	char	*line;

	i = 0;
	while (i++ < map_start)
		text = text->next;
	map_height = ft_lstsize(text);
	data->map = ft_calloc(map_height + 1, sizeof(char *));
	if (!data->map)
		return (1);
	while (i < map_height && text)
	{
		line = (char *)text->content;
		printf("%d\t%s", i, line);
		data->map[i] = malloc((map_width + 1) * sizeof(char));
		if (!data->map[i])
		{
			free_2dstr(data->map);
			return (1);
		}
		ft_strlcpy(data->map[i], line, ft_strlen(line));
		text = text->next;
	}
	return (0);
}

int32_t	init_player(t_var *data, int x, int y, char pov)
{
	data->ply_x = x;
	data->ply_y = y;
	if (pov == 'N')
		data->dir_y = 1;
	if (pov == 'S')
		data->dir_y = -1;
	if (pov == 'W')
		data->dir_x = -1;
	if (pov == 'E')
		data->dir_x = 1;
	return (0);
}

int32_t	extract_player(t_var *data, int *x, int y)
{
	char	*line;
	char	c;

	line = data->map[y];
	if (ft_strchr(line, 'N'))
		c = 'N';
	if (ft_strchr(line, 'S'))
		c = 'S';
	if (ft_strchr(line, 'W'))
		c = 'W';
	if (ft_strchr(line, 'E'))
		c = 'E';
	*x = ft_strchr(line, c) - line;
	return (init_player(data, *x, y, c));
}

int32_t	find_player(t_var *data, int *x, int *y)
{
	int		height;
	char	*line;

	if (!data || !data->map)
		return (1);
	height = ft_2d_array_size((void **)data->map);
	*y = 0;
	while (*y < height)
	{
		line = ft_strtrim(data->map[*y], "10 \n");
		if (ft_strlen(line))
			break ;
		free(line);
		*y = *y + 1;
	}
	if (!ft_strchr("WSNE", line[0]))
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
			ft_printf("Erroneus char in map\n");
	}
	if (line)
		free(line);
	return (extract_player(data, x, *y));
}

char	*column_to_line(char **table, int index)
{
	int		l;
	char	*res;

	res = ft_calloc(ft_2d_array_size(table) + 1, sizeof(char));
	l = 0;
	while (table[l])
	{
		if (ft_strlen(table[l]) < index)
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

	i = 0;
	while (base[i])
	{
		if (l < ft_strlen(base[i]))
			l = ft_strlen(base[i]);
		i++;
	}
	res = ft_calloc(l + 1, sizeof(char *));
	i = 0;
	while (i < l)
	{
		res[i] = column_to_line(base, i);
		i++;
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
	if (i[0] > 0)
		i[0] = 0;
	return (i[0]);
}

int	check_map(t_var *data)
{
	char	**rotated;
	int		res;

	rotated = rotate_table(date->map);
	res = map_checking_x(data->map) + map_checking_x(rotated);
	free_2dstr(rotated);
	return (res);
}

int32_t	free_data(t_var *data)
{
	free_2dstr(data->map);
	free(data->texture_north);
	free(data->texture_south);
	free(data->texture_easth);
	free(data->texture_westh);
	return (1);
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
	if (construct_map(data, text, map_width, map_start))
		return (ft_lstclear(&text, free), 1);
	ft_lstclear(&text, free);
	if (check_map(data))
		return(free_data(data));
	return (0);
}
