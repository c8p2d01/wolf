#include "../../inc/rendering.h"

void	put_slice(t_var *data, int i)
{
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
	// draw_line(data->main_render_img e2, start, end, ray_color(data, i, 255));
	draw_line_b(data->main_render_img, (data->config.height / actual_dist), i);
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
		// new_put_slice(data, i);
		i++;
	}
}

// void	new_put_slice(t_var *data, int i)
// {
// 	vec2d_t	start;
// 	vec2d_t	end;
// 	vec2d_t temp;

// 	if (data->rays[i].wall_dst < 0.0005) //data->rays[i].wall_dst > RENDER || 
// 		return ;
// 	temp.x = data->rays[i].x;
// 	temp.y = data->rays[i].y;
// 	double angle = angle2d(data->direct, temp);
// 	if (angle == angle)
// 		data->rays[i].wall_dst = cos(angle) * data->rays[i].wall_dst;
// printf("data->rays[i].wall_dst = %f\n", data->rays[i].wall_dst);
// 	start.x = (int)((data->config.height / 2) + (data->config.height / data->rays[i].wall_dst * 4));
// 	start.y = data->config.width - i;
// 	end.x = (int)((data->config.height / 2) - (data->config.height / data->rays[i].wall_dst * 4));
// 	end.y = data->config.width - i;

// 	int height = fabs(end.x - start.x);
// 	// printf("Height = %i\n", height);
// 	printf("start.x = %f\n", start.x);
// 	// printf("start.y = %f\n", start.y);
// 	printf("end.x = %f\n", end.x);
// 	// printf("end.y = %f\n", end.y);


// 	put_texture(data, start, end, height);
// 	// draw_line(data->main_render_img, start, end, ray_color(data, i));
// }

// void	put_texture(t_var *data, vec2d_t start, vec2d_t end, int height)
// {
// 	int	y;
// 	int j;
// 	double	step;
// 	int	n;

// 	y = 0;
// 	n = start.x;
// 	step = data->wall->height / height;
// 	// step = height / data->wall->height;

// 	j = ((int)y * data->wall->width);
// 	while (n > end.x && n > HEIGHT)
// 	{
// 		mlx_put_pixel(data->main_render_img, start.y, n, data->wall_pixels[(int)j]);
// 		y += step;
// 		j = (int)y * data->wall->width;
// 		n--;
// 	}
// }

// void	new_put_slice(t_var *data, int i)
// {
// 	vec2d_t	start;
// 	vec2d_t	end;
// 	vec2d_t temp;

// 	if (data->rays[i].wall_dst < 0.0020)
// 		return ;
// 	temp.x = data->rays[i].x;
// 	temp.y = data->rays[i].y;
// 	double angle = angle2d(data->direct, temp);
// 	if (angle == angle)
// 		data->rays[i].wall_dst = cos(angle) * data->rays[i].wall_dst;
// 	end.x = (int)((data->config.height / 2) + (data->config.height / data->rays[i].wall_dst));
// 	end.y = data->config.width - i;
// 	start.x = (int)((data->config.height / 2) - (data->config.height / data->rays[i].wall_dst));
// 	start.y = data->config.width - i;
// 	// printf("start.x = %f\n", start.x);
// 	// printf("start.y = %f\n", start.y);
// 	// printf("end.x = %f\n", end.x);
// 	// printf("end.y = %f\n", end.y);
// 	// draw_line_b(data, start, end, create_rgba(255, 255, 255, 255));
// 	draw_line_b(data, start, end, i);
// 	// put_texture(data, start, end, height);

// }

// void	print_texture(t_var *data)
// {
// 	int i = 0;
// 	double j = 0;
// 	int c = 0;
// 	int	txtr_color;
// 	double step;
// 	// int	height;
// 	// if (zeroth.x >= 0)
// 	// 	height = (first.x - zeroth.x);
// 	// else
// 	// 	height = (first.x + zeroth.x);
// 	step = (double)data->wall->height / (HEIGHT - 100);
// 	printf("step = %f\n", step);
// 	while(i < WIDTH / 2)
// 	{
// 		j = 0;
// 		while (j < HEIGHT/ 2)
// 		{
// 			// printf("i = %i, data->wall->height = %i\n", i, data->wall->height);
// 		// while(j_percent < 1)
// 			// j_percent = j / data->wall->width;
// 			c = (j * data->wall->width * 4) + (i * 4);
// 			// c = (j_percent * data->wall->width * 4) + (i * data->wall->width * 4);
// 			// txtr_color = get_txtr_color(data, c);
// 			// prot_put_pixel(data->main_render_img, i, (int)j, txtr_color);
// 			prot_put_pixel(data->main_render_img, i, (int)j, data->wall_pixels[c]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	switch_shift(int *n)
// {
// 	if (*n == 0)
// 		*n = 1;
// 	else
// 		*n = 0;
// }

// void	print_texture(t_var *data)
// {
// 	int i = 0;
// 	int j = 0;
// 	int c = 0;
// 	int	txtr_color;
// 	double j_color;
// 	double i_color;
// 	int		switch_i;
// 	int		switch_j;

// switch_j = 0;
// switch_i = 0;
// i_color = 0;
// 	while (i < data->wall->height)
// 	{
// 		printf("i = %i, data->wall->height = %i\n", i, data->wall->height);
// 		j = 0;
// j_color = 0;
// 		while(j < data->wall->width)
// 		{
// 			c = (j_color * 4) + (i_color * data->wall->width * 4);
// 			txtr_color = get_txtr_color(data, c);
// 			prot_put_pixel(data->main_render_img, j, i, txtr_color);
// 			// j++;
// 			// j++;
// 			switch_shift(&switch_j);
// 			if (switch_j)
// 				j++;
// 			j_color++;
// 			// c += 4;
// 		}
// 		// i++;
// 		switch_shift(&switch_i);
// 		if (switch_i)
// 			i++;
// 		i_color++;
// 	}
// }
