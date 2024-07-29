#include "./movement.h"

bool	wall_collision(t_var *data)
{
	vec2d_t step;

	step.x = (int)((data->player.x + data->move.x * MOVEMENT_SPEED) / ZOOM);
	step.y = (int)((data->player.y + data->move.y * MOVEMENT_SPEED) / ZOOM);
	if (ft_strchr("12", map_char(data,\
						(int)step.y, (int)data->player.x / ZOOM)))
	{
		data->move.y = 0;
	}
	if (ft_strchr("12", map_char(data,\
						(int)data->player.y / ZOOM, (int)step.x)))
	{
		data->move.x = 0;
	}
	return (0);
}
