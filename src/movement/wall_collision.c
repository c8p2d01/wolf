#include "../../inc/movement.h"

bool	wall_collision(t_var *data, double step_len)
{
	vec2d_t	step;

	step.x = (int)((data->player.x + data->move.x * step_len) / \
															data->config.zoom);
	step.y = (int)((data->player.y + data->move.y * step_len) / \
															data->config.zoom);
	if (ft_strchr("12", map_char(data, \
						(int)step.y, (int)data->player.x / data->config.zoom)))
	{
		data->move.y = 0;
	}
	if (ft_strchr("12", map_char(data, \
						(int)data->player.y / data->config.zoom, (int)step.x)))
	{
		data->move.x = 0;
	}
	return (0);
}

// void	approach_wall(t_var *data, t_draw_ray *draw_r, double o_x, double o_y);
// double	trace_cardinal_movement(t_var *data, short axis);
// double	trace_movement(t_var *data)
// {
// 	double	x_approach;
// 	double	y_approach;
// 	double	shortest;

// 	x_approach = trace_cardinal_movement(data, 0);
// 	y_approach = trace_cardinal_movement(data, 1);
// 	shortest = x_approach;
// 	if (y_approach < x_approach)
// 		shortest = y_approach;
// 	// if (shortest < WALL_DISTANCE)
// 		return (shortest);
// 	return (0);
// }

// double	trace_cardinal_movement(t_var *data, short axis)
// {
// 	t_draw_ray	draw_r;
// 	t_ray		temp;

// 	draw_r.i = 0;
// 	draw_r.step.x = 1;
// 	draw_r.step.y = 1;
// 	if (!axis)
// 	{
// 		draw_r.map.x = (int)((data->player.x / data->config.zoom) + WALL_DISTANCE);
// 		if (data->move.x > 0)
// 			draw_r.map.x = (int)((data->player.x / data->config.zoom) - WALL_DISTANCE);
// 	}
// 	else
// 	{
// 		draw_r.map.y = (int)((data->player.y / data->config.zoom) + WALL_DISTANCE);
// 		if (data->move.y > 0)
// 			draw_r.map.y = (int)((data->player.y / data->config.zoom) - WALL_DISTANCE);
// 	}
// 	draw_r.map.x = (int)((data->player.x / data->config.zoom));
// 	draw_r.map.y = (int)(data->player.y / data->config.zoom);
// 	temp = ray_creator(data, draw_r.i);
// 	temp.x = data->move.x;
// 	temp.y = data->move.y;
// 	draw_r.ray = &temp;
// 	calc_distances(data, &draw_r);
// 	if (axis)
// 		hit_wall(data, &draw_r);
// 	else
// 		hit_wall(data, &draw_r);
// 	if (draw_r.s_dist.x < draw_r.s_dist.y)
// 		draw_r.ray->wall_dst = draw_r.s_dist.x;
// 	else
// 		draw_r.ray->wall_dst = draw_r.s_dist.y;
// 	// printf("%d\n", temp.wall_dst);
// 	return (temp.wall_dst);
// }
