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
# include <memory.h>

# include "../MLX42/include/MLX42/MLX42.h"

# include "../ft_libft/inc/libft.h"

# include "configs.h"
# include "structs.h"
# include "minimap.h"
# include "settings.h"
# include "parsing.h"
# include "movement.h"
# include "rendering.h"

# ifndef DEBUG
#  define DEBUG 1
# endif

int32_t		create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
char		map_char(t_var *data, int x, int y);
double		deg_2_rad(float degree);

void		init(t_var *var);
int32_t		parse_input(int argc, char **argv, t_var *data);


t_ray		ray_creator(t_var *data, int num);
int			ray_color(t_var *data, int raynum, uint8_t opacity);
void		debug_fov(t_var *data);
void		print_map(t_var *data);

#endif