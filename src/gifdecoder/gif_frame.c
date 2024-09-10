/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:10 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:11 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

void	render_frame_rect(t_gd_gif *gif, uint8_t *buffer)
{
	int		i;
	int		j;
	int		k;
	uint8_t	index;
	uint8_t	*color;

	i = gif->fy * gif->width + gif->fx;
	j = 0;
	while (j < gif->fh)
	{
		k = 0;
		while (k < gif->fw)
		{
			index = gif->frame[(gif->fy + j) * gif->width + gif->fx + k];
			color = &gif->palette->colors[index * 3];
			if (!gif->gce.transparency || index != gif->gce.tindex)
				memcpy(&buffer[(i + k) * 3], color, 3);
			k++;
		}
		i += gif->width;
		j++;
	}
}

void	dispose(t_gd_gif *gif)
{
	int		i;
	int		j;
	int		k;
	uint8_t	*bgcolor;

	if (gif->gce.disposal == 2)
	{
		bgcolor = &gif->palette->colors[gif->bgindex * 3];
		i = gif->fy * gif->width + gif->fx;
		j = 0;
		while (j < gif->fh)
		{
			k = 0;
			while (k < gif->fw)
			{
				memcpy(&gif->canvas[(i + k) * 3], bgcolor, 3);
				k++;
			}
			i += gif->width;
			j++;
		}
	}
	else
		render_frame_rect(gif, gif->canvas);
}

int	gd_get_frame(t_gd_gif *gif)
{
	char	sep;

	dispose(gif);
	read(gif->fd, &sep, 1);
	while (sep != ',')
	{
		if (sep == ';')
			return (0);
		if (sep == '!')
			read_ext(gif);
		else
			return (-1);
		read(gif->fd, &sep, 1);
	}
	if (read_image(gif) == -1)
		return (-1);
	return (1);
}

void	gd_render_frame(t_gd_gif *gif, uint8_t *buffer)
{
	memcpy(buffer, gif->canvas, gif->width * gif->height * 3);
	render_frame_rect(gif, buffer);
}
