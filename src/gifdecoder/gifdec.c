#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static uint16_t	read_num(int fd)
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

static void	discard_sub_blocks(t_gd_gif *gif)
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

static void	read_plain_text_ext(t_gd_gif *gif)
{
	t_gif_plaintext_vars	vars;

	if (gif->plain_text)
	{
		lseek(gif->fd, 1, SEEK_CUR);
		vars.tx = read_num(gif->fd);
		vars.ty = read_num(gif->fd);
		vars.tw = read_num(gif->fd);
		vars.th = read_num(gif->fd);
		read(gif->fd, &vars.cw, 1);
		read(gif->fd, &vars.ch, 1);
		read(gif->fd, &vars.fg, 1);
		read(gif->fd, &vars.bg, 1);
		vars.sub_block = lseek(gif->fd, 0, SEEK_CUR);
		gif->plain_text(gif, vars.tx, vars.ty, vars.tw, vars.th, vars.cw, \
													vars.ch, vars.fg, vars.bg);
		lseek(gif->fd, vars.sub_block, SEEK_SET);
	}
	else
		lseek(gif->fd, 13, SEEK_CUR);
	discard_sub_blocks(gif);
}

static void	read_graphic_control_ext(t_gd_gif *gif)
{
	uint8_t	rdit;

	lseek(gif->fd, 1, SEEK_CUR);
	read(gif->fd, &rdit, 1);
	gif->gce.disposal = (rdit >> 2) & 3;
	gif->gce.input = rdit & 2;
	gif->gce.transparency = rdit & 1;
	gif->gce.delay = read_num(gif->fd);
	read(gif->fd, &gif->gce.tindex, 1);
	lseek(gif->fd, 1, SEEK_CUR);
}

static void	read_comment_ext(t_gd_gif *gif)
{
	off_t	sub_block;

	if (gif->comment)
	{
		sub_block = lseek(gif->fd, 0, SEEK_CUR);
		gif->comment(gif);
		lseek(gif->fd, sub_block, SEEK_SET);
	}
	discard_sub_blocks(gif);
}

static void	read_application_ext(t_gd_gif *gif)
{
	char	app_id[8];
	char	app_auth_code[3];
	off_t	sub_block;

	lseek(gif->fd, 1, SEEK_CUR);
	read(gif->fd, app_id, 8);
	read(gif->fd, app_auth_code, 3);
	if (!strncmp(app_id, "NETSCAPE", sizeof(app_id)))
	{
		lseek(gif->fd, 2, SEEK_CUR);
		gif->loop_count = read_num(gif->fd);
		lseek(gif->fd, 1, SEEK_CUR);
	}
	else if (gif->application)
	{
		sub_block = lseek(gif->fd, 0, SEEK_CUR);
		gif->application(gif, app_id, app_auth_code);
		lseek(gif->fd, sub_block, SEEK_SET);
		discard_sub_blocks(gif);
	}
	else
		discard_sub_blocks(gif);
}

static void	read_ext(t_gd_gif *gif)
{
	uint8_t	label;

	read(gif->fd, &label, 1);
	if (label == 0x01)
		read_plain_text_ext(gif);
	else if (label == 0xF9)
		read_graphic_control_ext(gif);
	else if (label == 0xFE)
		read_comment_ext(gif);
	else if (label == 0xFF)
		read_application_ext(gif);
	else
		fprintf(stderr, "unknown extension: %02X\n", label);
}

static t_table	*new_table(int key_size)
{
	int		key;
	int		init_bulk;
	t_table	*table;

	init_bulk = max(1 << (key_size + 1), 0x100);
	table = ft_malloc(sizeof(*table) + sizeof(t_entry) * init_bulk);
	if (table)
	{
		table->bulk = init_bulk;
		table->nentries = (1 << key_size) + 2;
		table->entries = (t_entry *) &table[1];
		key = 0;
		while (key < (1 << key_size))
		{
			table->entries[key] = (t_entry){1, 0xFFF, key};
			key++;
		}
	}
	return (table);
}

/* Add table entry. Return value:
 *  0 on success
 *  +1 if key size must be incremented after this addition
 *  -1 if could not realloc table */
static int	add_entry(t_table **tablep, uint16_t length, \
											uint16_t prefix, uint8_t suffix)
{
	t_table	*table;

	table = *tablep;
	if (table->nentries == table->bulk)
	{
		table->bulk *= 2;
		table = realloc(table, sizeof(*table) + sizeof(t_entry) * table->bulk);
		if (!table)
			return (-1);
		table->entries = (t_entry *) &table[1];
		*tablep = table;
	}
	table->entries[table->nentries] = (t_entry){length, prefix, suffix};
	table->nentries++;
	if ((table->nentries & (table->nentries - 1)) == 0)
		return (1);
	return (0);
}

int	inner_reader(t_gd_gif *gif, t_gif_read_vars *vars)
{
	if (vars->sub_len == 0)
	{
		read(gif->fd, &vars->sub_len, 1);
		if (vars->sub_len == 0)
			return (0x1000);
	}
	read(gif->fd, &vars->byte, 1);
	return (0);
}

static uint16_t	get_key(t_gd_gif *gif, t_gif_read_vars *vars)
{
	int	bits_read;
	int	rpad;
	int	frag_size;
	int	key;

	key = 0;
	bits_read = 0;
	while (bits_read < vars->key_size)
	{
		rpad = (vars->shift + bits_read) % 8;
		if (rpad == 0)
		{
			if (inner_reader(gif, vars) == 0x1000)
				return (0x1000);
			(vars->sub_len)--;
		}
		frag_size = min(vars->key_size - bits_read, 8 - rpad);
		key |= ((uint16_t)((vars->byte) >> rpad)) << bits_read;
		bits_read += frag_size;
	}
	key &= (1 << vars->key_size) - 1;
	vars->shift = (vars->shift + vars->key_size) % 8;
	return (key);
}

/* Compute output index of y-th input line, in frame of height h. */
static int	interlaced_line_index(int h, int y)
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
static int	read_image_data(t_gd_gif *gif, int interlace)
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
static int	read_image(t_gd_gif *gif)
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

static void	render_frame_rect(t_gd_gif *gif, uint8_t *buffer)
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

static void	dispose(t_gd_gif *gif)
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
