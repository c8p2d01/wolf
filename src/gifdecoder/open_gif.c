/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_gif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:19 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:33:15 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

uint16_t	read_num(int fd)
{
	uint8_t	bytes[2];

	read(fd, bytes, 2);
	return (bytes[0] + (((uint16_t) bytes[1]) << 8));
}

static int	open_prefix(t_gd_gif *gif)
{
	uint8_t	sigver[3];

	read(gif->fd, sigver, 3);
	if (memcmp(sigver, "GIF", 3) != 0)
	{
		fprintf(stderr, "invalid signature\n");
		close(gif->fd);
		return (1);
	}
	read(gif->fd, sigver, 3);
	if (memcmp(sigver, "89a", 3) != 0)
	{
		fprintf(stderr, "invalid version\n");
		close(gif->fd);
		return (1);
	}
	gif->width = read_num(gif->fd);
	gif->height = read_num(gif->fd);
	return (0);
}

static int	extract_fdsz(t_gd_gif *gif)
{
	uint8_t	fdsz;
	uint8_t	bgidx;
	uint8_t	aspect;
	int		gct_sz;

	read(gif->fd, &fdsz, 1);
	if (!(fdsz & 0x80))
	{
		fprintf(stderr, "no global color table\n");
		return (1);
	}
	gif->depth = ((fdsz >> 4) & 7) + 1;
	gct_sz = 1 << ((fdsz & 0x07) + 1);
	read(gif->fd, &bgidx, 1);
	read(gif->fd, &aspect, 1);
	gif->gct.size = gct_sz;
	read(gif->fd, gif->gct.colors, 3 * gif->gct.size);
	gif->palette = &gif->gct;
	gif->bgindex = bgidx;
	return (0);
}

static int	init_canvi(t_gd_gif *gif)
{
	uint8_t	*bgcolor;
	int		i;

	gif->frame = ft_malloc(4 * gif->width * gif->height);
	if (!gif->frame)
	{
		free(gif);
		return (0 * close(gif->fd));
	}
	gif->canvas = &gif->frame[gif->width * gif->height];
	if (gif->bgindex)
		memset(gif->frame, gif->bgindex, gif->width * gif->height);
	bgcolor = &gif->palette->colors[gif->bgindex * 3];
	i = 0;
	if (bgcolor[0] || bgcolor[1] || bgcolor [2])
	{
		while (i < gif->width * gif->height)
		{
			memcpy(&gif->canvas[i * 3], bgcolor, 3);
			i++;
		}
	}
	gif->anim_start = lseek(gif->fd, 0, SEEK_CUR);
	return (0);
}

t_gd_gif	*gd_open_gif(const char *fname)
{
	t_gd_gif	*gif;

	gif = ft_malloc(1 * sizeof(*gif));
	if (!gif)
		return (NULL);
	gif->fd = open(fname, O_RDONLY);
	if (gif->fd == -1)
		return (NULL);
	if (open_prefix(gif) || extract_fdsz(gif) || init_canvi(gif))
	{
		close(gif->fd);
		free(gif);
		return (NULL);
	}
	return (gif);
}
