#include "./movement.h"

void	straight(t_var *data, int sign)
{
	if (sign < 0)
	{
		data->move.x -= data->direct.x;
		data->move.y -= data->direct.y;
	}
	else
	{
		data->move.x += data->direct.x;
		data->move.y += data->direct.y;
	}
}

void	strafe(t_var *data, int sign)
{
	if (sign < 0)
	{
		data->move.x += data->direct.y;
		data->move.y -= data->direct.x;
	}
	else
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
	else //if (direction == RIGHT)
	{
		data->direct = rotate2d(&data->direct, -TURN_SPEED);
		data->move = rotate2d(&data->move, -TURN_SPEED);
	}
}

void	apply_movement(t_var *data)
{
	vec2d_t actual_move;

	// if (wall_collision(data))
	// 	slde(data);
	// else
	{
		actual_move.x = data->move.x;
		actual_move.y = data->move.y;
		normalise2d(&actual_move);
		data->player.x += actual_move.x;
		data->player.y += actual_move.y;
	}
}

void	display_movement(t_var *data)
{
	// Center
	mlx_put_pixel(data->map_img, 25, 25, create_rgba(255, 42, 0, 255));
	// dir
	mlx_put_pixel(data->map_img, 25 + data->move.y * 10, 25 + data->move.x * 10, create_rgba(42, 255, 0, 255));
	mlx_put_pixel(data->map_img, 25 + data->direct.y * 15, 25 + data->direct.x * 15, create_rgba(42, 0, 255, 255));
}

// void	apply_movement(t_var *data)
// {
// 	data
// }