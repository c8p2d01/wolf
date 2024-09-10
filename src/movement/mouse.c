/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:37:45 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:37:50 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/movement.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_var			*data;
	mouse_mode_t	mouse;

	data = (t_var *)param;
	if (0 < xpos && xpos < WIDTH && 0 < ypos && ypos < HEIGHT && \
															data->mouse == 1)
	{
		mlx_set_cursor_mode(data->_mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(data->_mlx, WIDTH / 2, HEIGHT / 2);
		if (xpos < WIDTH / 2)
		{
			data->direct = rotate2d(&data->direct, \
												data->config.turn_mouse_speed);
			data->move = rotate2d(&data->move, data->config.turn_mouse_speed);
		}
		else if (xpos > WIDTH / 2)
		{
			data->direct = rotate2d(&data->direct, \
												-data->config.turn_mouse_speed);
			data->move = rotate2d(&data->move, -data->config.turn_mouse_speed);
		}
	}
}

void	mouse_action(t_var *data)
{
	if (data->mouse == 0)
	{
		printf("\e[2J\e[3;1H");
		enable_file(data);
		data->mouse = 1;
	}
	else if (data->mouse == 1)
	{
		printf("\e[2J\e[3;1H");
		disable_file(data);
		data->mouse = 0;
	}
}

void	disable_file(t_var *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("src/movement/mouse_printing_files/mouse_disabled", O_RDONLY);
	if (fd == -1)
		printf("failed to load mouse enabling statement\n");
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (fd)
		close(fd);
}

void	print_enabled_character(t_var *data, char *line, int *i)
{
	if (line[*i] == 'R')
	{
		(*i)++;
		if (line[*i] == '1')
			printf(R1);
		else if (line[*i] == '2')
			printf(R2);
		else if (line[*i] == '3')
			printf(R3);
		else if (line[*i] == '4')
			printf(R4);
	}
	else if (line[*i] == 'Q')
	{
		printf(QUIT_COLOR);
		*i += 9;
	}
	else
		printf("%c", line[*i]);
}

void	enable_file(t_var *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("src/movement/mouse_printing_files/mouse_enabled", O_RDONLY);
	if (fd == -1)
		printf("failed to load mouse enabling statement\n");
	line = get_next_line(fd);
	while (line)
	{
		i = -1;
		while (line[++i])
			print_enabled_character(data, line, &i);
		free(line);
		line = get_next_line(fd);
	}
	if (fd)
		close(fd);
}
