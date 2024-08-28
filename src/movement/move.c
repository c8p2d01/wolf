#include "../../inc/movement.h"

void	straight(t_var *data, t_key_state action)
{
	if (action == PRESS)
	{
		data->move.x += data->direct.x;
		data->move.y += data->direct.y;
	}
	else if (action == MINUS)
	{
		data->move.x -= data->direct.x;
		data->move.y -= data->direct.y;
	}
}

void	strafe(t_var *data, t_key_state action)
{
	if (action == PRESS)
	{
		data->move.x += data->direct.y;
		data->move.y -= data->direct.x;
	}
	else if (action == MINUS)
	{
		data->move.x -= data->direct.y;
		data->move.y += data->direct.x;
	}
}

void	turn(t_var *data, int direction)
{
	if (direction == LEFT)
	{
		data->direct = rotate2d(&data->direct, data->config.turn_speed);
		data->move = rotate2d(&data->move, data->config.turn_speed);
	}
	else
	{
		data->direct = rotate2d(&data->direct, -data->config.turn_speed);
		data->move = rotate2d(&data->move, -data->config.turn_speed);
	}
}

void	apply_movement(t_var *data)
{
	double	max;
	vec2d_t	step;

	normalise2d(&data->move);
	max = wall_collision(data);
	normalise2d(&data->move);
	step.x = data->move.x * data->config.movement_speed;
	step.y = data->move.y * data->config.movement_speed;
	if (data->move.x)
		lf_limit(&step.x, -max, max);
	if (data->move.y)
		lf_limit(&step.y, -max, max);
	data->player.x += step.x;
	data->player.y += step.y;
}

// void	apply_movement(t_var *data)
// {
// 	double	step_len;
// 	double	tmp;

// 	normalise2d(&data->move);
// 	tmp = trace_movement(data);
// 	step_len = MOVEMENT_SPEED;
// 	if (tmp < MOVEMENT_SPEED)
// 		step_len = tmp;
// 		printf("%lf\n", step_len);
// 	wall_collision(data, step_len);
// 	data->player.x += data->move.x * step_len;
// 	data->player.y += data->move.y * step_len;
// }

