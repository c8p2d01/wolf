/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:07 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:08 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

int	gd_is_bgcolor(t_gd_gif *gif, uint8_t color[3])
{
	return (!memcmp(&gif->palette->colors[gif->bgindex * 3], color, 3));
}

void	gd_rewind(t_gd_gif *gif)
{
	lseek(gif->fd, gif->anim_start, SEEK_SET);
}

void	gd_close_gif(t_gd_gif *gif)
{
	close(gif->fd);
	free(gif->frame);
	free(gif);
}
