#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef DEBUG
#  define DEBBUG 0
# endif

# define GONE "\033[8m"
# define CLEAR_TERM "\e[1;1H\e[2J"
# define PI 3.14159265359


# define WIDTH 120
# define HEIGHT 40
# define FOV 90
# define RENDER 30
# define WALL 'O'

# define SKY 8421631
# define FLOOR 2894892
# define WEST 1677696
# define EAST 65280
# define SOUTH 1671168
# define NORTH 255

typedef struct s_var
{
	// hardcode texture reference for i won't be implementing file reading :)
	char **west;
	char **east;
	char **south;
	char **north;

	char **map;
	// canvas
	int canvas[HEIGHT + 1][WIDTH + 1];

	// Player
	double	positionX;
	double	positionY;
	double	orientationX;
	double	orientationY;
	
}	t_var;

double	veclen(int dimension, ...);
void	normalize(int dimension, ...);

void	rayCreation(t_var	*data, double *rayX, double *rayY, int rayNumber);
void	firstStep(t_var *data, double *rayR, double *dst, bool isX);
int		rayMarcher(t_var *data, double *dst, int rayNumber);
void	renderer(t_var *data);

void	printMap(t_var *data);
void	printFrame(t_var *data);
void	putPixel(int color);
int		createRGB(int r, int g, int b);

void	rem(t_var *var);
void	init(t_var *var, char *path);
char	**init_texture(char *first, ...);

#endif