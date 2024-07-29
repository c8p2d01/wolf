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

# include "../MLX42/include/MLX42/MLX42.h"

# include "../ft_libft/inc/libft.h"

# include "configs.h"

typedef struct s_ray
{
	int		number;
	double	x;
	double	y;
	double	wall_dst;
	char	*wall;
}	t_ray;

typedef struct s_vctr
{
	double	y;
	double	x;
}	t_vctr;

typedef struct s_var
{
	mlx_t			*_mlx;

	mlx_image_t		*map_layout_img;
	mlx_image_t		*map_render_img;
	mlx_image_t		*main_static_img;
	mlx_image_t		*main_render_img;

	char			*path_north;
	char			*path_south;
	char			*path_westh;
	char			*path_easth;

	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_westh;
	mlx_texture_t	*texture_easth;

	int32_t			floor;
	int32_t			ceiling;

	char			**map;
	int				map_width;
	int				map_height;

	vec2d_t			player;
	vec2d_t			direct;
	vec2d_t			move;

	t_ray			rays[WIDTH];
	bool			map_visibility;
}	t_var;

void		putPixel(int color);
int32_t		create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void		step(t_var *data, int stepsize);
char		map_char(t_var *data, int x, int y);

void		rem(t_var *var);
void		init(t_var *var);
int32_t		parse_input(int argc, char **argv, t_var *data);
void		rayMarcher(t_var *data);

void		filler(t_var *data);
void		mini_filler(t_var *data, int x, int y, char c);
void		draw_player_triangle(t_var *data);
double		deg_2_rad(float degree);

# ifndef PARSING_H
#  include "../src/parsing/parsing.h"
# endif

# ifndef MOVEMENT_H
#  include "../src/movement/movement.h"
# endif

# ifndef RENDERING_H
#  include "../src/rendering/rendering.h"
# endif

#endif