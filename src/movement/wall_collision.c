#include "../../inc/movement.h"

bool	wall_collision(t_var *data, double step_len)
{
// <<<<<<< HEAD
	vec2d_t	step;

	step.x = (int)((data->player.x + data->move.x * MOVEMENT_SPEED) / \
															data->config.zoom);
	step.y = (int)((data->player.y + data->move.y * MOVEMENT_SPEED) / \
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
	return (MOVEMENT_SPEED);
	// =======
	// t_draw_ray	move_x;
	// t_ray		ray;
// 	move_x.step.x = 1;
// 	move_x.step.y = 1;
// 	move_x.map.x = (int)(data->player.x / data->config.zoom);
// 	move_x.map.y = (int)(data->player.y / data->config.zoom);
// 	ray = ray_creator(data, 0);
// 	move_x.ray = &ray;
// 	move_x.ray->x = data->move.x;
// 	move_x.ray->y = 0;
// 	normalise_2d(&move_x.ray->x, &move_x.ray->y);
// 	move_x.color = create_rgba(255,0,0,255);
// 	calc_distances(data, &move_x);
// 	hit_wall(data, &move_x);
// 	identify_wall(data, &move_x);
// 	draw_ray(data, &move_x);

// 	double	wall_x = move_x.ray->wall_dst - WALL_DISTANCE;
	
// 	t_draw_ray	move_y;
// 	t_ray		ray2;
	
// 	move_y.step.x = 1;
// 	move_y.step.y = 1;
// 	move_y.map.x = (int)(data->player.x / data->config.zoom);
// 	move_y.map.y = (int)(data->player.y / data->config.zoom);
// 	ray2 = ray_creator(data, 42);
// 	move_y.ray = &ray2;
// 	move_y.ray->x = 0;
// 	move_y.ray->y = data->move.y;
// 	normalise_2d(&move_y.ray->x, &move_y.ray->y);
// 	move_y.color = create_rgba(0,255,0,255);
// 	calc_distances(data, &move_y);
// 	hit_wall(data, &move_y);
// 	identify_wall(data, &move_y);
// 	draw_ray(data, &move_y);

// 	double	wall_y = move_y.ray->wall_dst - WALL_DISTANCE;

// 	t_draw_ray	move_xy;
// 	t_ray		ray3;
	
// 	move_xy.step.x = 1;
// 	move_xy.step.y = 1;
// 	move_xy.map.x = (int)(data->player.x / data->config.zoom);
// 	move_xy.map.y = (int)(data->player.y / data->config.zoom);
// 	ray3 = ray_creator(data, 42);
// 	move_xy.ray = &ray3;
// 	move_xy.ray->x = data->move.x;
// 	move_xy.ray->y = data->move.y;
// 	normalise_2d(&move_xy.ray->x, &move_xy.ray->y);
// 	move_xy.color = create_rgba(0,0,255,255);
// 	calc_distances(data, &move_xy);
// 	hit_wall(data, &move_xy);
// 	identify_wall(data, &move_xy);
// 	draw_ray(data, &move_xy);

// 	double	wall_xy = move_xy.ray->wall_dst - WALL_DISTANCE;

// 	if (wall_x < 0)
// >>>>>>> keeping distance, raycasting x,y & both of movVec and keep from walls, some things are still possible tho
	// {
	// 	data->move.y = wall_y;
	// }
	// if (wall_y < 0)
	// {
	// 	data->move.x = wall_x;
	// }
	// if (wall_x < wall_y && wall_x < wall_xy)
	// 	return (wall_x);
	// if (wall_y < wall_xy)
	// 	return (wall_y);
	// if (wall_xy > 0)
	// 	return (wall_xy);
	// return (0);
}
