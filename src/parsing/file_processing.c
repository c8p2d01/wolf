#include "../../inc/parsing.h"

int	check_if_only_space(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\n')
	{
		if (str[i] != ' ')
		{

			return (0);
		}
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

int	check_if_only_newline(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] != '\n')
		{

			return (0);
		}
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

int	first_map_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
int	newline_space_check(char *read_line, int fd, int map_switch)
{
	if (check_if_only_space(read_line))
	{
		free(read_line);
		if (map_switch == 1)
			return (printf("Map should be the last displayed!\n"), 1);
		return (2);
	}
	else if (check_if_only_newline(read_line))
	{
		free(read_line);
		if (map_switch == 1)
			return (printf("Map should be the last displayed!\n"), 1);
		return (3);
	}
	return (0);
}

int	map_validity_upright(char *read_line, int fd, t_list **text)
{
	char	*line;
	int		map_switch = 0;
	int		temp;

	while (read_line)
	{
		temp = newline_space_check(read_line, fd, map_switch);
		if (temp == 1)
			return (1);
		else if (temp == 2)
			break ;
		else if (temp == 3)
		{
			read_line = get_next_line(fd);
			continue ;
		}
		if (first_map_line(read_line) && map_switch == 0)
			map_switch = 1;
		line = ft_strtrim(read_line, "\n");
		free(read_line);
		ft_lstadd_back(text, ft_lstnew(line));
		read_line = get_next_line(fd);
	}
	return (0);
}

/**
 * Read the contents of the file into a list of lines
 */
int32_t	file_read(char *file, t_list **text)
{
	int		fd;
	char	*read_line;

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
	read_line = get_next_line(fd);
	map_validity_upright(read_line, fd, text);
	close(fd);
	// rotated = rotate_table(data->map); // in check_map<map_validation
	return (0);
}

/**
 * Check that the argument count is = 2
 */
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

/**
 * Check that the file, given as the argument, follow the naming convention
 */
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
