#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include "../ft_libft/inc/libft.h"

# ifndef DEBUG
#  define DEBBUG 0
# endif

# define GONE "\033[8m"
# define CLEAR_TERM "\e[1;1H\e[2J"
# define PI 3.14159265359


# define WIDTH 121
# define HEIGHT 10
# define FOV 90
# define RENDER 30
# define WALL 'O'

# define SKY 8421631
# define FLOOR 2894892

typedef struct s_ray
{
	int		number;
	double	x;
	double	y;
	double	wallDst;
	short	wallKind;
}	t_ray;

typedef struct s_var
{
	char **map;
	// canvas replace with mlx image
	int canvas[HEIGHT + 1][WIDTH + 1];

	// Player
	double	positionX;
	double	positionY;
	double	orientationX;
	double	orientationY;
	
}	t_var;

// void	rayCreation(t_var	*data, double *rayX, double *rayY, int rayNumber);
// void	firstStep(t_var *data, double *rayR, double *dst, bool isX);
// int		rayMarcher(t_var *data, double *dst, int rayNumber);
// void	renderer(t_var *data);

void	putPixel(int color);
int		createRGB(unsigned int r, unsigned int g, unsigned int b);

void	rem(t_var *var);
void	init(t_var *var);

#endif