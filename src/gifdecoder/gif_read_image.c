/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_read_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:12 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:13 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

void	inits(t_gd_gif *gif, int interlace, t_gif_read_vars *vars)
{
	vars->start = lseek(gif->fd, 0, SEEK_CUR);
	discard_sub_blocks(gif);
	vars->end = lseek(gif->fd, 0, SEEK_CUR);
	lseek(gif->fd, vars->start, SEEK_SET);
	vars->clear = 1 << vars->key_size;
	vars->stop = vars->clear + 1;
	vars->table = new_table(vars->key_size);
	vars->key_size++;
	vars->init_key_size = vars->key_size;
	vars->sub_len = 0;
	vars->shift = 0;
	vars->key = get_key(gif, vars);
	vars->frm_off = 0;
	vars->ret = 0;
	vars->frm_size = gif->fw * gif->fh;
}

int	key_stuff(t_gd_gif *gif, int interlace, t_gif_read_vars *vars)
{
	if (vars->key == vars->clear)
	{
		vars->key_size = vars->init_key_size;
		vars->table->nentries = (1 << (vars->key_size - 1)) + 2;
		vars->table_is_full = 0;
	}
	else if (!vars->table_is_full)
	{
		vars->ret = add_entry(&vars->table, vars->str_len + 1, vars->key, \
														vars->entry.suffix);
		if (vars->ret == -1)
		{
			free(vars->table);
			return (-1);
		}
		if (vars->table->nentries == 0x1000)
		{
			vars->ret = 0;
			vars->table_is_full = 1;
		}
	}
	vars->key = get_key(gif, vars);
	return (0);
}

void	read_stuff(t_gd_gif *gif, int interlace, t_gif_read_vars *vars)
{
	vars->entry = vars->table->entries[vars->key];
	vars->str_len = vars->entry.length;
	vars->i = 0;
	while (vars->i < vars->str_len)
	{
		vars->p = vars->frm_off + vars->entry.length - 1;
		vars->x = vars->p % gif->fw;
		vars->y = vars->p / gif->fw;
		if (interlace)
			vars->y = interlaced_line_index((int) gif->fh, vars->y);
		gif->frame[(gif->fy + vars->y) * gif->width + gif->fx + vars->x] = \
															vars->entry.suffix;
		if (vars->entry.prefix == 0xFFF)
			break ;
		else
			vars->entry = vars->table->entries[vars->entry.prefix];
		vars->i++;
	}
	vars->frm_off += vars->str_len;
	if (vars->key < vars->table->nentries - 1 && !vars->table_is_full)
		vars->table->entries[vars->table->nentries - 1].suffix = \
															vars->entry.suffix;
}

/* Decompress image pixels.
 * Return 0 on success or -1 on out-of-memory (w.r.t. LZW code table). */
int	read_image_data(t_gd_gif *gif, int interlace)
{
	t_gif_read_vars	vars;

	read(gif->fd, &vars.byte, 1);
	vars.key_size = (int) vars.byte;
	if (vars.key_size < 2 || vars.key_size > 8)
		return (-1);
	inits(gif, interlace, &vars);
	while (vars.frm_off < vars.frm_size)
	{
		if (key_stuff(gif, interlace, &vars) == -1)
			return (-1);
		if (vars.key == vars.clear)
			continue ;
		if (vars.key == vars.stop || vars.key == 0x1000)
			break ;
		if (vars.ret == 1)
			vars.key_size++;
		read_stuff(gif, interlace, &vars);
	}
	free(vars.table);
	if (vars.key == vars.stop)
		read(gif->fd, &vars.sub_len, 1);
	lseek(gif->fd, vars.end, SEEK_SET);
	return (0);
}

/* Read image.
 * Return 0 on success or -1 on out-of-memory (w.r.t. LZW code table). */
int	read_image(t_gd_gif *gif)
{
	uint8_t	fisrz;
	int		interlace;

	gif->fx = read_num(gif->fd);
	gif->fy = read_num(gif->fd);
	if (gif->fx >= gif->width || gif->fy >= gif->height)
		return (-1);
	gif->fw = read_num(gif->fd);
	gif->fh = read_num(gif->fd);
	gif->fw = min(gif->fw, gif->width - gif->fx);
	gif->fh = min(gif->fh, gif->height - gif->fy);
	read(gif->fd, &fisrz, 1);
	interlace = fisrz & 0x40;
	if (fisrz & 0x80)
	{
		gif->lct.size = 1 << ((fisrz & 0x07) + 1);
		read(gif->fd, gif->lct.colors, 3 * gif->lct.size);
		gif->palette = &gif->lct;
	}
	else
		gif->palette = &gif->gct;
	return (read_image_data(gif, interlace));
}
