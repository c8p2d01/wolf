#include "parsing.h"

int32_t	check_map(t_var *data)
{
	char	**rotated;
	int		res;

	rotated = rotate_table(data->map);
	data->map_width = ft_2d_array_size((void **)rotated) - 1;
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

/**
 * check if a line is rule compliant
 * -> all of its segments (divided by ' ') begin and end with '1'
 */
int32_t	map_checking_x(char **map)
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
			trimm = ft_strNOTtrim(subs[i[1]], "1");
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

char	*column_to_line(char **table, int index)
{
	int		l;
	char	*res;

	res = ft_calloc(ft_2d_array_size((void **)table) + 1, sizeof(char));
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
