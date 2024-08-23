#include "../../inc/cub.h"

void	move_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;
	printf("\e[3;1H\n\n");
	temp = data->config.movement_speed + ydelta;
	if (temp > 0 && temp <= 1)
		data->config.movement_speed += ydelta;
}

void	turn_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;

	printf("\e[3;1H\n\n");
	temp = data->config.turn_speed + ydelta;
	if (temp > 0 && temp <= 5)
	{
		printf("turn speed = %f\n", temp);
		data->config.turn_speed += ydelta;
	}
}

void	turn_mouse_setting(double xdelta, double ydelta, t_var *data)
{
	float	temp;

	printf("\e[3;1H\n\n");
	temp = data->config.turn_mouse_speed + ydelta;
	if (temp > 0 && temp <= 5)
	{
		printf("mouse turn speed = %f\n", temp);
		data->config.turn_mouse_speed += ydelta;
	}
}

void	test_setting(double xdelta, double ydelta, t_var *data)
{
	(void)xdelta;
	(void)ydelta;
	(void)data;
}

void	norm_setting(double xdelta, double ydelta, t_var *data)
{
	(void)xdelta;
	(void)ydelta;
	(void)data;
}

void	debug_setting(double xdelta, double ydelta, t_var *data)
{
	(void)xdelta;
	(void)ydelta;
	printf("\e[3;1H\n\n");
	print_data(data);
	debug_fov(data);
	printf("\n");
}

void	fov_setting(double xdelta, double ydelta, t_var *data)
{
	(void)xdelta;
	printf("\e[3;1H\e[9J");
	data->config.fov += (int) ydelta;
	i_limit(&data->config.fov, 1, 179);
	ft_memset(data->map_render_img->pixels, 0, data->map_render_img->width * \
							data->map_render_img->height * sizeof(int));
	debug_fov(data);
}

void	zoom_setting(double xdelta, double ydelta, t_var *data)
{
	double	old_zoom;

	(void)xdelta;
	old_zoom = data->config.zoom;
	data->config.zoom += (int) ydelta;
	lf_limit(&data->config.zoom, 1, data->_mlx->width / data->map_width);
	lf_limit(&data->config.zoom, 1, data->_mlx->height / data->map_height);
	mlx_resize_image(data->map_layout_img, (data->map_width * \
					data->config.zoom), (data->map_height * data->config.zoom));
	mlx_resize_image(data->map_render_img, (data->map_width * \
					data->config.zoom), (data->map_height * data->config.zoom));
	memset(data->map_render_img->pixels, 0, data->map_render_img->width * \
							data->map_render_img->height * sizeof(int));
	memset(data->map_layout_img->pixels, 0, data->map_layout_img->width * \
							data->map_layout_img->height * sizeof(int));
	data->player.x = (int)((data->player.x / old_zoom) * data->config.zoom);
	data->player.y = (int)((data->player.y / old_zoom) * data->config.zoom);
	filler(data);
	draw_fov_lines(data);
	draw_player_triangle(data);
}
