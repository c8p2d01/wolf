#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub.h"

typedef struct s_ray
{
	int				number;
	double			x;
	double			y;
	double			wall_dst;
<<<<<<< HEAD
=======
	double			wall_percent;
>>>>>>> c10d8f68bb5fcb564590d99308fa37f1277b01fd
	mlx_texture_t	*wall;
}	t_ray;

typedef struct s_intvctr
{
	int	y;
	int	x;
}	t_intvctr;

typedef struct s_draw_ray
{
	int			i;
	vec2d_t		s_dist;
	vec2d_t		d_dist;
	vec2d_t		step;
	vec2d_t		map;
	int			side;
	int			color;
	t_ray		*ray;
	char		hit;
}	t_draw_ray;

typedef struct s_var
{
	mlx_t			*_mlx;

	t_config		config;

	mlx_image_t		*map_layout_img;
	mlx_image_t		*map_render_img;
	mlx_image_t		*main_static_img;
	mlx_image_t		*main_render_img;

	char			*path_north;
	char			*path_south;
	char			*path_westh;
	char			*path_easth;
	char			*path_door;

	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_westh;
	mlx_texture_t	*texture_easth;
	mlx_texture_t	*texture_door;

	int32_t			floor;
	int32_t			ceiling;

	char			**map;
	int				map_width;
	int				map_height;

	vec2d_t			player;
	vec2d_t			direct;
	vec2d_t			move;

	t_ray			*rays;

	int				settings;

	struct timeval	time;

	gd_GIF			*gif[5];
	mlx_texture_t	*gif_tex;
}	t_var;

#endif