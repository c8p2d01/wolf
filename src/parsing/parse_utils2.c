/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:28:49 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 18:29:33 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

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
		if (file)
			free(file);
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
