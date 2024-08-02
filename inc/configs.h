#ifndef CONFIGS_H
# define CONFIGS_H

# ifndef DEBUG
#  define DEBUG 1
# endif

# define PI 3.14159265359

# define FOV 90
# define RENDER 8
# define WIDTH 620
# define HEIGHT 500
# define ZOOM 20
# define MOVEMENT_SPEED 0.5
# define TURN_SPEED 3 //		in degree per frame
# define MAP_OPACITY 200

# define MAP_WALL 16711680
# define MAP_GRND 65535

# define N_SETTINGS 7

typedef struct s_config
{
	int		setting;
	int		fov;
	double	zoom;
	int		height;
	int		width;
	double	color_offset;
	bool	map_visibility;
	int		ray_style;
}	t_config;

#endif