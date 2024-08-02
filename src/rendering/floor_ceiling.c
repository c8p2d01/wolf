#include "./rendering.h"

void	floor_ceiling(t_var *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < data->config.height / 2)
	{
		w = 0;
		while (w < data->config.width)
		{
			mlx_put_pixel(data->main_static_img, w, h, data->ceiling);
			w++;
		}
		h++;
	}
	while (h < data->config.height)
	{
		w = 0;
		while (w < data->config.width)
		{
			mlx_put_pixel(data->main_static_img, w, h, data->floor);
			w++;
		}
		h++;
	}
}
