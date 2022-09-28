#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BLACK "\033[30m"
# define GREY "\033[90m"
# define RED "\033[91m"
# define CYAN "\033[36m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[94m"
# define MAGENTA "\033[35m"

# define NORMAL "\033[0m"
# define FAT "\033[1m"
# define DIM "\033[2m"
# define UNDERLINE "\033[4m"
# define CROSS "\033[9m"
# define BACKGROUND "\033[7m"
# define GONE "\033[8m"
# define CLEAR_TERM "\e[1;1H\e[2J"
# define PI 3.14159265359


# define WIDTH 220
# define HEIGHT 60
# define FOV 90
# define RENDER 10

# define SKY 'o'
# define FLOOR '@'

typedef struct s_var
{
	// hardcode texture reference for i won't be implementing file reading :)
	char **west;
	char **east;
	char **south;
	char **north;

	char **map;
	// canvas
	char cvs[HEIGHT + 1][WIDTH + 1];

	// Player
	double	plx;
	double	ply;
	double	orx;
	double	ory;
	
}	t_var;

#endif