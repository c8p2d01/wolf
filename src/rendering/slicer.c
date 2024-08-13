#include "../../inc/rendering.h"

void	put_slice(t_var *data, int i)
{
	vec2d_t	temp;
	double	actual_dist;
	double	angle;

	if (data->rays[i].wall_dst < 0.0005)
		return ;
	temp.x = data->rays[i].x;
	temp.y = data->rays[i].y;
	actual_dist = data->rays[i].wall_dst;
	angle = angle2d(data->direct, temp);
	if (angle == angle)
		actual_dist = cos(angle) * data->rays[i].wall_dst;
	draw_line_b(data, (data->config.height / actual_dist), i);
}

void	gif_next_frame(gd_GIF *gif, mlx_texture_t *tex)
{
	int	ret;

	if (!gif || !tex)
		return ;
	ret = gd_get_frame(gif);
	if (ret == -1)
		return ;
	if (ret == 0)
		gd_rewind(gif);
	gd_render_frame(gif, tex->pixels);
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
