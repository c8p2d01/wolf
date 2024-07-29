#include "./rendering.h"

void	floor_ceiling(t_var *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < HEIGHT / 2)
	{
		w = 0;
		while (w < WIDTH)
		{
			mlx_put_pixel(data->main_static_img, w, h, data->ceiling);
			w++;
		}
		h++;
	}
	while (h < HEIGHT)
	{
		w = 0;
		while (w < WIDTH)
		{
			mlx_put_pixel(data->main_static_img, w, h, data->floor);
			w++;
		}
		h++;
	}
}
