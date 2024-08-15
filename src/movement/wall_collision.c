#include "../../inc/movement.h"

double	trace_x(t_var *data)
{
	t_draw_ray	move_x;
	t_ray		ray;

	if (data->move.x == 0)
		return (0);
	move_x.step.x = 1;
	move_x.step.y = 1;
	move_x.map.x = (int)(data->player.x / data->config.zoom);
	move_x.map.y = (int)(data->player.y / data->config.zoom);
	ray = ray_creator(data, 0);
	move_x.ray = &ray;
	move_x.ray->x = data->move.x;
	move_x.ray->y = 0;
	normalise_2d(&move_x.ray->x, &move_x.ray->y);
	move_x.color = create_rgba(255,0,0,255);
	calc_distances(data, &move_x);
	hit_wall(data, &move_x);
	identify_wall(data, &move_x);
	draw_ray(data, &move_x);
	return (ray.wall_dst - WALL_DISTANCE);
}

double	trace_y(t_var *data)
{
	t_draw_ray	move_y;
	t_ray		ray;

	if (data->move.x == 0)
		return (0);
	move_y.step.x = 1;
	move_y.step.y = 1;
	move_y.map.x = (int)(data->player.x / data->config.zoom);
	move_y.map.y = (int)(data->player.y / data->config.zoom);
	ray = ray_creator(data, 0);
	move_y.ray = &ray;
	move_y.ray->x = 0;
	move_y.ray->y = data->move.y;
	normalise_2d(&move_y.ray->x, &move_y.ray->y);
	move_y.color = create_rgba(0,255,0,255);
	calc_distances(data, &move_y);
	hit_wall(data, &move_y);
	identify_wall(data, &move_y);
	draw_ray(data, &move_y);
	return (ray.wall_dst - WALL_DISTANCE);
}

double	trace_xy(t_var *data)
{
	t_draw_ray	move_xy;
	t_ray		ray;

	if (data->move.x == 0)
		return (0);
	move_xy.step.x = 1;
	move_xy.step.y = 1;
	move_xy.map.x = (int)(data->player.x / data->config.zoom);
	move_xy.map.y = (int)(data->player.y / data->config.zoom);
	ray = ray_creator(data, 0);
	move_xy.ray = &ray;
	move_xy.ray->x = data->move.x;
	move_xy.ray->y = data->move.y;
	normalise_2d(&move_xy.ray->x, &move_xy.ray->y);
	move_xy.color = create_rgba(0,0,255,255);
	calc_distances(data, &move_xy);
	hit_wall(data, &move_xy);
	identify_wall(data, &move_xy);
	draw_ray(data, &move_xy);
	return (ray.wall_dst - WALL_DISTANCE);
}

double	wall_collision(t_var *data)
{
	if (data->move.x == 0 && data->move.y == 0)
		return (0);

	double	wall_x = trace_x(data);

	double	wall_y = trace_y(data);

	double	wall_xy = trace_xy(data);

	if (wall_x < 0)
	{
		data->move.y = 0;
	}
	if (wall_y < 0)
	{
		data->move.x = 0;
	}
	if (wall_x < wall_y && wall_x < wall_xy)
		return (wall_x);
	if (wall_y < wall_xy)
		return (wall_y);
	if (wall_xy > 0)
		return (wall_xy);
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
