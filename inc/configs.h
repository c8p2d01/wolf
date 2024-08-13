#ifndef CONFIGS_H
# define CONFIGS_H

# ifndef DEBUG
#  define DEBUG 1
# endif

// swap meaning and modify makefile before submitting
# ifndef BONUS
#  define CHARSET " 0123"
# else
#  define CHARSET " 01"
# endif

# define PI 3.14159265359

# define FOV 90
# define RENDER 8
# define WIDTH 1366
# define HEIGHT 768
# define ZOOM 7
# define MOVEMENT_SPEED 0.5
# define TURN_SPEED 1 //		in degree per frame
# define MAP_OPACITY 200

# define MAP_WALL 16711680
# define MAP_GRND 65535
# define MAP_DOOR 16777215
# define MAP_OPEN 2763306

# define N_SETTINGS 7

typedef struct s_config
{
	int		setting;
	int		fov;
	double	zoom;
	int		height;
	int		width;
	double	color_offset;
	uint8_t	map_opacity;
	int		ray_style;
}	t_config;

#endif