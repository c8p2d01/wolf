#include "../../inc/rendering.h"

void	put_slice(t_var *data, int i)
{
	vec2d_t	start;
	vec2d_t	end;
	vec2d_t temp;

	if (data->rays[i].wall_dst < 0.05)
		return ;
	temp.x = data->rays[i].x;
	temp.y = data->rays[i].y;
	double angle = angle2d(data->direct, temp);
	if (angle == angle)
		data->rays[i].wall_dst = cos(angle) * data->rays[i].wall_dst;
	start.x = (int)((data->config.height / 2) + (data->config.height / data->rays[i].wall_dst));
	start.y = data->config.width - i;
	end.x = (int)((data->config.height / 2) - (data->config.height / data->rays[i].wall_dst));
	end.y = data->config.width - i;
	draw_line(data->main_render_img, start, end, ray_color(data, i, 255));
}

void	render_view(t_var *data)
{
	int	i;

	ft_memset(data->main_render_img->pixels, 0, data->config.width * \
											data->config.height * sizeof(int));
	i = 0;
	while (i < data->config.width)
	{
		put_slice(data, i);
		i++;
	}
}
