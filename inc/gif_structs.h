/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:52:08 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/09 05:55:24 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIF_STRUCTS_H
# define GIF_STRUCTS_H

#include "../ft_libft/inc/libft.h"
# include <stdlib.h>
# include <sys/types.h>

typedef struct s_gd_palette {
	int			size;
	uint8_t		colors[0x100 * 3];
}	t_gd_palette;

typedef struct s_gd_gce {
	uint16_t	delay;
	uint8_t		tindex;
	uint8_t		disposal;
	int			input;
	int			transparency;
}	t_gd_gce;

typedef struct s_entry {
	uint16_t	length;
	uint16_t	prefix;
	uint8_t		suffix;
}	t_entry;

typedef struct s_table {
	int		bulk;
	int		nentries;
	t_entry	*entries;
}	t_table;

typedef struct s_reading_vars {
	uint8_t sub_len, shift, byte;
	int init_key_size, key_size, table_is_full;
	int frm_off, frm_size, str_len, i, p, x, y;
	uint16_t key, clear, stop;
	int ret;
	t_table *table;
	t_entry entry;
	off_t start, end;
}	t_reading_vars;

struct t_gd_gif;
typedef struct s_gd_gif {
	uint8_t			sigver[3];
	int				fd;
	off_t			anim_start;
	uint16_t		width;
	uint16_t		height;
	uint16_t		depth;
	uint8_t			bgindex;
	uint16_t		loop_count;
	t_gd_gce		gce;
	t_gd_palette	*palette;
	t_gd_palette	lct;
	t_gd_palette	gct;
	uint16_t		fx;
	uint16_t		fy;
	uint16_t		fw;
	uint16_t		fh;
	uint8_t			*canvas;
	uint8_t			*frame;

	void			(*plain_text)(
			struct s_gd_gif	*gif,
			uint16_t		tx, uint16_t ty,
			uint16_t		tw, uint16_t th,
			uint8_t			cw, uint8_t ch,
			uint8_t			fg, uint8_t bg
			);
	void			(*comment)(
			struct s_gd_gif *gif
			);
	void			(*application)(
			struct s_gd_gif *gif, char id[8], char auth[3]
			);
}	t_gd_gif;

typedef struct	s_gif_plaintext_vars {
	uint16_t	tx;
	uint16_t	ty;
	uint16_t	tw;
	uint16_t	th;
	uint8_t		cw;
	uint8_t		ch;
	uint8_t		fg;
	uint8_t		bg;
	off_t		sub_block;
}	t_gif_plaintext_vars;

typedef struct	s_gif_read_vars {
	uint8_t sub_len;
	uint8_t shift;
	uint8_t byte;
	int init_key_size;
	int key_size;
	int table_is_full;
	int frm_off;
	int frm_size;
	int str_len;
	int i;
	int p;
	int x;
	int y;
	uint16_t key;
	uint16_t clear;
	uint16_t stop;
	int ret;
	t_table *table;
	t_entry entry;
	off_t start;
	off_t end;
	uint8_t	*temp[2];
}	t_gif_read_vars;




#endif
