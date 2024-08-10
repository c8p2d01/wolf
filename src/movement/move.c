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
		data->direct = rotate2d(&data->direct, TURN_SPEED);
		data->move = rotate2d(&data->move, TURN_SPEED);
	}
	else
	{
		data->direct = rotate2d(&data->direct, -TURN_SPEED);
		data->move = rotate2d(&data->move, -TURN_SPEED);
	}
}

void	apply_movement(t_var *data)
{
	double	max;

	normalise2d(&data->move);
	max = wall_collision(data);
	if (MOVEMENT_SPEED < max)
	{
		data->player.x += data->move.x * MOVEMENT_SPEED;
		data->player.y += data->move.y * MOVEMENT_SPEED;
	}
	else
	{
		data->player.x += data->move.x * max;
		data->player.y += data->move.y * max;
	}
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

