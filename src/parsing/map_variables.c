/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:25:22 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int32_t	construct_map(t_var *data, t_list *text, int map_start, int32_t i)
{
	int32_t	l;

	i = 0;
	while (i++ < map_start)
		text = text->next;
	update_map_width(data, text);
	data->map_height = ft_lstsize(text) - map_start;
	if (data->map_height <= 0 || data->map_width <= 0)
		return (1);
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		return (1);
	i = 0;
	while (text)
	{
		l = ft_strlen((char *)text->content);
		if (l != data->map_width)
			text->content = ft_realloc(text->content, l, \
													data->map_width - l + 1);
		if (l != data->map_width)
			ft_memset(text->content + l, ' ', data->map_width - l);
		data->map[i++] = (char *)text->content;
		text = text->next;
	}
	return (0);
}

/**
 * find txture/color varables and set the start of the map
 */
int32_t	parse_values(t_list *text, t_var *data, int *map_start, char *line)
{
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
		{
			free(line);
			break ;
		}
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
