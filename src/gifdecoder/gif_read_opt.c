/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_read_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:14 by cdahlhof          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:16 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gif_structs.h"
#include "../../inc/gifdec.h"

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

void	read_ext(t_gd_gif *gif)
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
