#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

#include "../MLX42/include/MLX42/MLX42.h"

# include "../ft_libft/inc/libft.h"

# ifndef DEBUG
#  define DEBUG 1
# endif

# define PI 3.14159265359

# define FOV 90
// # define FOV_DIV 4
# define RENDER 3000
# define WIDTH 200
# define ZOOM 20

typedef struct s_ray
{
	int		number;
	double	x;
	double	y;
	double	wallDst;
	// char	*wall;
}	t_ray;

typedef struct	s_vctr
{
	double	y;
	double	x;
}	t_vctr;

typedef struct	s_intvctr
{
	int	y;
	int	x;
}	t_intvctr;

typedef struct s_draw_ray
{
	int			i;
	// t_ray		*ray;
	t_vctr		s_dist;
	t_vctr		d_dist;
	t_intvctr	step;
	t_intvctr	map;
}	t_draw_ray;

typedef struct s_var
{
	mlx_t		*mlx;
	mlx_t		*main_mlx;

	mlx_image_t	*map_img;
	mlx_image_t	*main_img;

	char			*path_north;
	char			*path_south;
	char			*path_westh;
	char			*path_easth;

	mlx_texture_t*	texture_north;
	mlx_texture_t*	texture_south;
	mlx_texture_t*	texture_westh;
	mlx_texture_t*	texture_easth;

	int32_t	floor;
	int32_t	ceiling;

	char	**map;
	int		map_width;
	int		map_height;
	// int		map_size;

	double	ply_x; //pixel location
	double	ply_y; //pixel location
	double	dir_x; //where am I looking at?
	double	dir_y; //where am I looking at?
	t_vctr			direct;
	t_ray	rays[WIDTH];

}	t_var;

void	putPixel(int color);
int		create_rgba(uint8_t r,uint8_t g,uint8_t b,uint8_t a);
void	step(t_var *data, int stepsize);
void	turn(t_var *data, float degree);

void	rem(t_var *var);
void	init(t_var *var);
int32_t	parse_input(int argc, char **argv, t_var *data);
void	rayMarcher(t_var *data);

# ifndef PARSING_H
#  include "../src/parsing/parsing.h"
# endif

void	filler(t_var *data);
void	mini_filler(t_var *data, int x, int y, char c);
void	draw_player_triangle(t_var *data);
double	deg_2_rad(float degree);
t_ray	rayCreator(t_var *data, int num);
void	draw_fov_lines(t_var *data);
void	calc_distances(t_var *data, t_draw_ray *draw_r);
void	print_map(t_var *data);
void	hit_wall(t_var *data, t_draw_ray *draw_r);
void	draw_ray(t_var *data, t_draw_ray *draw_r);
// void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
void	draw_line(t_var *data, t_vctr zeroth, t_vctr first, int color);

#endif