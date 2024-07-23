#include "parsing.h"

/**
 * Read the contents of the file into a list of lines
 */
int32_t	file_read(char *file, t_list **text)
{
	int		fd;
	char	*read_line;
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
	read_line = get_next_line(fd);
	while (read_line)
	{
		line = ft_strtrim(read_line, "\n");
		free(read_line);
		ft_lstadd_back(text, ft_lstnew(line));
		read_line = get_next_line(fd);
	}
	close(fd);
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
