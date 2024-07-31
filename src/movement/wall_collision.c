#include "./movement.h"

bool	wall_collision(t_var *data)
{
	vec2d_t step;

	step.x = (int)((data->player.x + data->move.x * MOVEMENT_SPEED) / data->config.zoom);
	step.y = (int)((data->player.y + data->move.y * MOVEMENT_SPEED) / data->config.zoom);
	if (ft_strchr("12", map_char(data,\
						(int)step.y, (int)data->player.x / data->config.zoom)))
	{
		data->move.y = 0;
	}
	if (ft_strchr("12", map_char(data,\
						(int)data->player.y / data->config.zoom, (int)step.x)))
	{
		data->move.x = 0;
	}
	return (0);
}
