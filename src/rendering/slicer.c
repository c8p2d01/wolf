#include "./rendering.h"

void	put_slice(t_var *data, int i)
{
	vec2d_t	start;
	vec2d_t	end;

	if (data->rays[i].wall_dst > RENDER)
		return ;
	start.x = (int)((data->config.height / 2) + 1 * (RENDER - data->rays[i].wall_dst) * data->config.zoom);
	start.y = data->config.width - i;
	end.x = (int)((data->config.height / 2) - 1 * (RENDER - data->rays[i].wall_dst) * data->config.zoom);
	end.y = data->config.width - i;
	// printf("ray %i; draw from %d | %d\t to %d | %d\n", i, (int)start.x, (int)start.y, (int)end.x, (int)end.y)
	draw_line(data->main_render_img, start, end, ray_color(data, i));
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
