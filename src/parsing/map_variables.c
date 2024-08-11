#include "../../inc/parsing.h"

int32_t	construct_map(t_var *data, t_list *text, int map_start, int32_t i)
{
	int32_t	l;

	i = 0;
	while (i++ < map_start)
		text = text->next;
	update_map_width(data, text);
	data->map_height = ft_lstsize(text) - map_start;
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		return (1);
	i = 0;
	while (text)
	{
		l = ft_strlen((char *)text->content);
		if (l != data->map_width)
		{
			text->content = ft_realloc(text->content, l, \
													data->map_width - l + 1);
			ft_memset(text->content + l, ' ', data->map_width - l);
		}
		data->map[i] = (char *)text->content;
		text = text->next;
		i++;
	}
	return (0);
}

/**
 * find txture/color varables and set the start of the map
 */
int32_t	parse_values(t_list *text, t_var *data, int *map_start)
{
	char	*line;

	while (text)
	{
		line = ft_strtrim((char *)text->content, "\t\v\f\r ");
		if (!line)
			return (1);
		if (ft_strlen(line) == 0)
		{
			text = text->next;
			*map_start = *map_start + 1;
			free(line);
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

/**
 * parse variables and determine their validity
 */
int32_t	check_variable(t_var *data, char *line)
{
	char	**elmnts;

	elmnts = ft_split(line, ' ');
	if (!elmnts)
		return (1);
	if (ft_2d_array_size((void **)elmnts) != 2)
	{
		ft_printf("Error\n");
		if (DEBUG == 1)
			ft_printf("Variable not identifyable\n");
		free_2dstr(elmnts);
		return (1);
	}
	return (set_variable(data, elmnts));
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
		else if (!ft_strncmp(elmnts[0], "F", 2))
			data->floor = calculate_color(elmnts[1]);
		else if (!ft_strncmp(elmnts[0], "C", 2))
			data->ceiling = calculate_color(elmnts[1]);
		else
			return (free_2dstr(elmnts), 1);
	}
	else
		return (free_2dstr(elmnts), 1);
	free_2dstr(elmnts);
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
	else
	{
		color = (ft_atoi(values[0]) % 256) << 24 | \
			(ft_atoi(values[1]) % 256) << 16 | \
			(ft_atoi(values[2]) % 256) << 8 | \
								255;
	}
	free_2dstr(values);
	return (color);
}
