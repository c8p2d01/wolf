/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:22 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:24 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gifdec.h"
#include "../../inc/gif_structs.h"

int	min(int A, int B)
{
	if ((A) < (B))
		return (A);
	return (B);
}

int	max(int A, int B)
{
	if ((A) > (B))
		return (A);
	return (B);
}

void	discard_sub_blocks(t_gd_gif *gif)
{
	uint8_t	size;

	read(gif->fd, &size, 1);
	lseek(gif->fd, size, SEEK_CUR);
	while (size)
	{
		read(gif->fd, &size, 1);
		lseek(gif->fd, size, SEEK_CUR);
	}
}

/* Compute output index of y-th input line, in frame of height h. */
int	interlaced_line_index(int h, int y)
{
	int	p;

	p = (h - 1) / 8 + 1;
	if (y < p)
		return (y * 8);
	y -= p;
	p = (h - 5) / 8 + 1;
	if (y < p)
		return (y * 8 + 4);
	y -= p;
	p = (h - 3) / 4 + 1;
	if (y < p)
		return (y * 4 + 2);
	y -= p;
	return (y * 2 + 1);
}
