#include "../../inc/movement.h"

double	wall_collision(t_var *data)
{
// <<<<<<< HEAD
	vec2d_t	step;

	step.x = (int)((data->player.x + data->move.x) / \
															data->config.zoom);
	step.y = (int)((data->player.y + data->move.y) / \
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
	return (max_step(data, 0));
}

double	smallest(t_var *data, double *distances, double side,double wall_dist);

double	max_step(t_var *data, double side)
{
	t_draw_ray	mid;
	t_ray		temp;
	t_ray		player_tmp;
	double		distances[3];

	player_tmp.x = data->player.x;
	player_tmp.y = data->player.y;
	data->player.x += data->move.y * side * data->config.zoom;
	data->player.y += -data->move.x * side * data->config.zoom;
	mid.step.x = 1;
	mid.step.y = 1;
	mid.map.x = (int)((data->player.x / data->config.zoom));
	mid.map.y = (int)((data->player.y / data->config.zoom));
	temp = ray_creator(data, mid.i);
	temp.x = data->move.x;
	temp.y = data->move.y;
	mid.ray = &temp;
	calc_distances(data, &mid);
	mid.spaces = "03NSWE";
	mid.hit = '0';
	hit_wall(data, &mid);
	identify_wall(data, &mid);
	data->player.x = player_tmp.x;
	data->player.y = player_tmp.y;
	return (smallest(data, distances, side, temp.wall_dst));
	// return(MOVEMENT_SPEED);
}

double	smallest(t_var *data, double *distances, double side, double wall_dist)
{
	if (side != 0)
		return (wall_dist);
	distances[0] = wall_dist - WALL_DISTANCE;
	distances[1] = max_step(data, WALL_DISTANCE) - WALL_DISTANCE;
	distances[2] = max_step(data, -WALL_DISTANCE) - WALL_DISTANCE;
	if (distances[0] < distances[1] && distances[0] < distances[2])
		return (distances[0]);
	if (distances[1] < distances[2])
		return (distances[1]);
	return (distances[2]);
}
