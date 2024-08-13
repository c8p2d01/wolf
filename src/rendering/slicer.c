#include "../../inc/rendering.h"

void	put_slice(t_var *data, int i)
{
	vec2d_t	start;
	vec2d_t	end;
	vec2d_t temp;
	double	actual_dist;

	if (data->rays[i].wall_dst < 0.0005)
		return ;
	temp.x = data->rays[i].x;
	temp.y = data->rays[i].y;
	actual_dist = data->rays[i].wall_dst;
	double angle = angle2d(data->direct, temp);
	if (angle == angle)
		actual_dist = cos(angle) * data->rays[i].wall_dst;
	start.x = (int)((data->config.height / 2) + (data->config.height / actual_dist));
	start.y = data->config.width - i;
	end.x = (int)((data->config.height / 2) - (data->config.height / actual_dist));
	end.y = data->config.width - i;
	// draw_line(data->main_render_img e2, start, end, ray_color(data, i, 255));
	draw_colorful_line(data, (data->config.height / actual_dist), i);
}

void	gif_next_frame(gd_GIF *gif, mlx_texture_t *tex)
{
	int		ret;

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
	
	// usleep(data->gif->gce.delay * 10);
	// gif_next_frame(data);
	// uint8_t	*buffer = data->gif_tex->pixels;
	// for(int x = 0; x < data->gif_tex->width; x++)
	// {
	// 	for(int y = 0; y < data->gif_tex->width; y++)
	// 	{
	// 		prot_put_pixel(data->main_render_img, y, x, \
	// 			create_rgba(buffer[0], buffer[1], buffer[2], 255));
	// 		buffer += 3;
	// 	}
	// }
}
