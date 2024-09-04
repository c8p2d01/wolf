#include "../../inc/rendering.h"

void	toggle_doors(mlx_key_data_t key, t_var *data)
{
	char	c;
	int		char_x;
	int		char_y;

	char_x = (int)(data->player.x / data->config.zoom + data->direct.x);
	char_y = (int)(data->player.y / data->config.zoom + data->direct.y);
	c = map_char(data, char_y, char_x);
	if (c == '2')
	{
		data->map[char_x][char_y] = '3';
		redraw_minimap(data);
	}
	if (c == '3')
	{
		data->map[char_x][char_y] = '2';
		redraw_minimap(data);
	}
	ft_memset(data->map_render_img->pixels, 0, \
				data->map_render_img->width * \
				data->map_render_img->height * sizeof(int));
}

void	trace_step(t_var *data, t_draw_ray *draw_r)
{
	if (draw_r->s_dist.x < draw_r->s_dist.y)
	{
		draw_r->s_dist.x += draw_r->d_dist.x;
		draw_r->map.x += draw_r->step.x;
		draw_r->side = 1;
	}
	else
	{
		draw_r->s_dist.y += draw_r->d_dist.y;
		draw_r->map.y += draw_r->step.y;
		draw_r->side = 0;
	}
}

void	trace_y_walls(t_var *data, t_draw_ray *draw_r)
{
	char	hit;

	hit = '0';
	while (ft_strchr("03NSWE", hit))
	{
		trace_step(data, draw_r);
		hit = map_char(data, (int)draw_r->map.y, (int)draw_r->map.x);
		if ((map_char(data, (int)draw_r->map.y - 1, (int)draw_r->map.x) && \
											data->rays[draw_r->i].y < 0) \
			|| \
			map_char(data, (int)draw_r->map.y + 1, (int)draw_r->map.x) && \
											data->rays[draw_r->i].y > 0)
			break ;
	}
}

void	trace_x_walls(t_var *data, t_draw_ray *draw_r)
{
	char	hit;

	hit = '0';
	draw_r->s_dist.y -= 0.5;
	while (ft_strchr("03NSWE", hit))
	{
		trace_step(data, draw_r);
		hit = map_char(data, (int)draw_r->map.y, (int)draw_r->map.x);
		if ((map_char(data, (int)draw_r->map.y, (int)draw_r->map.x - 1) && \
											data->rays[draw_r->i].y < 0) || \
			map_char(data, (int)draw_r->map.y, (int)draw_r->map.x + 1) && \
											data->rays[draw_r->i].y > 0)
			break ;
	}
}

void	trace_door(t_var *data, t_draw_ray *draw_r)
{
	int			tmp;
	t_ray		temp;
	t_ray		p_player;
	double		distances[3];

	p_player.x = data->player.x;
	p_player.y = data->player.y;

	if (map_char(data, draw_r->map.y + 1, draw_r->map.x) == '1' && \
		map_char(data, draw_r->map.y - 1, draw_r->map.x) == '1')
	{
		if (data->direct.x > 0)
			data->player.x = data->p_player.x - 0.5 * data->config.zoom;
		else
			data->player.x = data->p_player.x + 0.5 * data->config.zoom;
	}

	if (map_char(data, draw_r->map.y, draw_r->map.x + 1) == '1' && \
		map_char(data, draw_r->map.y, draw_r->map.x - 1) == '1')
	{
		if (data->direct.y > 0)
			data->player.y = data->p_player.y - 0.5 * data->config.zoom;
		else
			data->player.y = data->p_player.y + 0.5 * data->config.zoom;
	}
	draw_r->map.x = (int)((data->player.x / data->config.zoom));
	draw_r->map.y = (int)((data->player.y / data->config.zoom));
	// data->rays[draw_r->i] = ray_creator(data, draw_r->i);
	// draw_r->ray = &data->rays[draw_r->i];
	calc_distances(data, draw_r);
	draw_r->spaces = "03NSWE";
	draw_r->hit = '0';
	tmp = draw_r->i;
	draw_r->i = -1;
	hit_wall(data, draw_r);
	identify_wall(data, draw_r);
	data->player.x = data->p_player.x;
	data->player.y = data->p_player.y;
	draw_r->i = tmp;
}

void	trace_door_side(t_var *data, t_draw_ray *draw_r)
{
	int			tmp;
	t_ray		temp;
	t_ray		p_player;
	double		distances[3];

	data->player.x = data->p_player.x;
	data->player.y = data->p_player.y;
	draw_r->map.x = (int)((data->player.x / data->config.zoom));
	draw_r->map.y = (int)((data->player.y / data->config.zoom));
	// data->rays[draw_r->i] = ray_creator(data, draw_r->i);
	// draw_r->ray = &data->rays[draw_r->i];
	calc_distances(data, draw_r);
	draw_r->spaces = "023NSWE";
	draw_r->hit = '0';
	tmp = draw_r->i;
	draw_r->i = -42;
	hit_wall(data, draw_r);
	identify_wall(data, draw_r);
	data->player.x = data->p_player.x;
	data->player.y = data->p_player.y;
	draw_r->i = tmp;
}

int	check_door(int i, t_var *data)
{
	int	pos;

	if (ft_strchr(data->map[i], '2'))
	{
		pos = ft_strchr(data->map[i], '2') - data->map[i];
	}
	else
	{
		pos = ft_strchr(data->map[i], '3') - data->map[i];
	}
	if ((data->map[i][pos + 1] == '1' && data->map[i][pos - 1] == '1') || \
		(data->map[i + 1][pos] == '1' && data->map[i - 1][pos] == '1'))
	{
		return (0);
	}
	else
	{
		printf("bad door at %i\t%i\n", i, pos);
		return (42);
	}
}

void	draw_loop(t_var *data, mlx_texture_t *tex, int height, int raynum)
{
	uint8_t			*pixel;
	int				y;
	double			perc_x;
	double			perc_y;
	int				midpoint;

	midpoint = (data->main_render_img->height / 2) - (height / 2);
	y = -1;
	while (++y < height)
	{
		if (!data || !data->rays || midpoint + y < 0 || midpoint + y > \
												data->main_render_img->height)
			continue ;
		perc_y = (double)y / (double)height;
		perc_x = data->rays[raynum].wall_percent;
		lf_limit(&perc_x, 0, 1);
		lf_limit(&perc_y, 0, 1);
		pixel = &tex->pixels[((int)(perc_x * (int)tex->width) + \
				(int)(perc_y * tex->height) * (int)tex->width) \
				* (int)tex->bytes_per_pixel];
		prot_put_pixel(data->main_render_img,
			raynum,
			midpoint + y,
			create_rgba(pixel[0], pixel[1], pixel[2], 255));
	}
}

void	draw_line_b(t_var *data, int height, int raynum)
{
	mlx_texture_t	*tex;

	if (!data || !data->rays || !(&(data->rays[raynum])))
		return ;
	tex = data->rays[raynum].wall;
	if (!tex || !tex->pixels || !tex->width || !tex->height || \
														!tex->bytes_per_pixel)
	{
		return ;
	}
	draw_loop(data, tex, height, raynum);
}
