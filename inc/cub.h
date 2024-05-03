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
# define RENDER 30
# define WIDTH 200
# define RENDER 30
# define ZOOM 20

typedef struct s_ray
{
	int		number;
	double	x;
	double	y;
	double	wallDst;
	char	*wall;
}	t_ray;

typedef struct s_var
{
	mlx_t	*mlx;

	mlx_image_t	*map_img;

	char	*texture_north;
	char	*texture_south;
	char	*texture_westh;
	char	*texture_easth;

	int32_t	floor;
	int32_t	ceiling;

	char	**map;
	int		map_width;
	int		map_height;

	double	ply_x;
	double	ply_y;
	double	dir_x;
	double	dir_y;

	t_ray	rays[WIDTH];

}	t_var;

// void	rayCreation(t_var	*data, double *rayX, double *rayY, int rayNumber);
// void	firstStep(t_var *data, double *rayR, double *dst, bool isX);
// int		rayMarcher(t_var *data, double *dst, int rayNumber);
// void	renderer(t_var *data);

void	putPixel(int color);
int		create_rgba(int r, int g, int b, int a);

void	rem(t_var *var);
void	init(t_var *var);
int32_t	parse_input(int argc, char **argv, t_var *data);
void	rayMarcher(t_var *data);
void	map_player(t_var *data);


#endif