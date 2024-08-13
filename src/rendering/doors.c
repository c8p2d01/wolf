#include "../../inc/rendering.h"

void	toggle_doors(mlx_key_data_t key, t_var *data)
{
	char	c;

	c = map_char(data, (int)(data->player.y / data->config.zoom + data->direct.y)\
		, (int)(data->player.x / data->config.zoom + data->direct.x));
	if (c == '2')
		data->map[(int)(data->player.x / data->config.zoom + data->direct.x)][(int)(data->player.y / data->config.zoom + data->direct.y)] = '3';
	if (c == '3')
		data->map[(int)(data->player.x / data->config.zoom + data->direct.x)][(int)(data->player.y / data->config.zoom + data->direct.y)] = '2';
	ft_memset(data->map_layout_img->pixels, 0, \
				data->map_layout_img->width * \
				data->map_layout_img->height * sizeof(int));
	ft_memset(data->map_render_img->pixels, 0, \
				data->map_render_img->width * \
				data->map_render_img->height * sizeof(int));
	filler(data);
	draw_fov_lines(data);
	render_view(data);
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
	char hit;

	hit = '0';
	draw_r->s_dist.x -= 0.5;
	while (ft_strchr("03NSWE", hit))
	{
		trace_step(data, draw_r);
		hit = map_char(data, (int)draw_r->map.y, (int)draw_r->map.x);
		if ((map_char(data, (int)draw_r->map.y - 1, (int)draw_r->map.x) && data->rays[draw_r->i].y < 0) || \
			map_char(data, (int)draw_r->map.y + 1, (int)draw_r->map.x) && data->rays[draw_r->i].y > 0)
			break ;
	}
}

void	trace_x_walls(t_var *data, t_draw_ray *draw_r)
{
	char hit;

	hit = '0';
	draw_r->s_dist.y -= 0.5;
	while (ft_strchr("03NSWE", hit))
	{
		trace_step(data, draw_r);
		hit = map_char(data, (int)draw_r->map.y, (int)draw_r->map.x);
		if ((map_char(data, (int)draw_r->map.y, (int)draw_r->map.x - 1) && data->rays[draw_r->i].y < 0) || \
			map_char(data, (int)draw_r->map.y, (int)draw_r->map.x + 1) && data->rays[draw_r->i].y > 0)
			break ;
	}
}

void	trace_door(t_var *data, t_draw_ray *draw_r)
{
	bool door_axis;

	if (map_char(data, draw_r->map.y + 1, draw_r->map.x) == '1' && \
		map_char(data, draw_r->map.y - 1, draw_r->map.x) == '1')
	{
		door_axis = 1;
		trace_y_walls(data, draw_r);
	}
	else if (map_char(data, draw_r->map.y, draw_r->map.x + 1) == '1' && \
				map_char(data, draw_r->map.y, draw_r->map.x - 1) == '1')
	{
		door_axis = 0;
		trace_x_walls(data, draw_r);
	}
	else
		return ;
	// data->rays[draw_r->i].wall = data->texture_north; // set a door texture somewhere else?
	if (draw_r->side)
		draw_r->s_dist.x -= draw_r->d_dist.x;
	else
		draw_r->s_dist.y -= draw_r->d_dist.y;
	identify_door(data, draw_r, door_axis);
}

void	identify_door(t_var *data, t_draw_ray *draw_r, bool door_axis)
{
	if (draw_r->s_dist.x < draw_r->s_dist.y)
		data->rays[draw_r->i].wall_dst = draw_r->s_dist.x;
	else
		data->rays[draw_r->i].wall_dst = draw_r->s_dist.y;
	if (draw_r->side && !data->rays[draw_r->i].wall)
	{
		if (door_axis)
			data->rays[draw_r->i].wall = data->texture_north; // door texture
		else if (data->rays[draw_r->i].x >= 0)
			data->rays[draw_r->i].wall = data->texture_south; // maybe door side
		else
			data->rays[draw_r->i].wall = data->texture_north;
	}
	else if (!data->rays[draw_r->i].wall)
	{
		if (!door_axis)
			data->rays[draw_r->i].wall = data->texture_north; // door texture
		else if (data->rays[draw_r->i].y >= 0)
			data->rays[draw_r->i].wall = data->texture_easth; // maybe door side textures
		else
			data->rays[draw_r->i].wall = data->texture_westh;
	}
	identify_wall_fraction(data, draw_r);
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
		printf("valid %s door\n", ft_strchr(data->map[i], '2') ? "closed" : "open");
		return (0);
	}
	else
	{
		printf("bad door at %i\t%i\n", i, pos);
		return (42);
	}
}
