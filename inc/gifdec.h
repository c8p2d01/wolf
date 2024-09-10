/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gifdec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:48:37 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:31:00 by cdahlhof         ###   ########.fr       */
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


void		render_frame_rect(t_gd_gif *gif, uint8_t *buffer);
void		dispose(t_gd_gif *gif);

int			read_image_data(t_gd_gif *gif, int interlace);
int			read_image(t_gd_gif *gif);

void		read_ext(t_gd_gif *gif);
uint16_t	read_num(int fd);
void		discard_sub_blocks(t_gd_gif *gif);
int			interlaced_line_index(int h, int y);

t_table		*new_table(int key_size);
int			add_entry(t_table **tablep, uint16_t length, \
											uint16_t prefix, uint8_t suffix);
uint16_t	get_key(t_gd_gif *gif, t_gif_read_vars *vars);

int			min(int A, int B);
int			max(int A, int B);

#endif
