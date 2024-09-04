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

# define FPS 30
# define FOV 75
# define RENDER 8
# define WIDTH 1100
# define HEIGHT 600
# define ZOOM 20
# define MOVEMENT_SPEED 1
# define TURN_SPEED 3 //		in degree per frame
# define TURN_MOUSE_SPEED 3
# define MAP_OPACITY 200
# define WALL_DISTANCE 0.08

# define MAP_WALL 16711680
# define MAP_GRND 65535
# define MAP_DOOR 16777215
# define MAP_OPEN 2763306

# define N_SETTINGS 10

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
	float	movement_speed;
	float	turn_speed;
	float	turn_mouse_speed;
	int		framespeed;
}	t_config;

#endif