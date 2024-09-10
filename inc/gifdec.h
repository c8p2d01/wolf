/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gifdec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:48:37 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/09 05:49:19 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIFDEC_H
# define GIFDEC_H

# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>

# include "gif_structs.h"

t_gd_gif	*gd_open_gif(const char *fname);
int			gd_get_frame(t_gd_gif *gif);
void		gd_render_frame(t_gd_gif *gif, uint8_t *buffer);
int			gd_is_bgcolor(t_gd_gif *gif, uint8_t color[3]);
void		gd_rewind(t_gd_gif *gif);
void		gd_close_gif(t_gd_gif *gif);

int			min(int A, int B);
int			max(int A, int B);

#endif
