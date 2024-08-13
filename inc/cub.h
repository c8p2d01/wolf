#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
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
t_var		**proto_global();

void		init(t_var *var);
int32_t		parse_input(int argc, char **argv, t_var *data);


t_ray		ray_creator(t_var *data, int num);
void		draw_fov_lines(t_var *data);
int			ray_color(t_var *data, int raynum, uint8_t opacity);
void		debug_fov(t_var *data);
void		print_map(t_var *data);
void		hit_wall(t_var *data, t_draw_ray *draw_r);
void		identify_wall(t_var *data, t_draw_ray *draw_r);
void		identify_wall_fraction(t_var *data, t_draw_ray *draw_r);
void		draw_ray(t_var *data, t_draw_ray *draw_r);
void		draw_line(mlx_image_t *img, vec2d_t a, vec2d_t b, int color);
void		prot_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color);

void		print_setting(t_var *data);
void		test_setting(double xdelta, double ydelta, t_var *data);
void		norm_setting(double xdelta, double ydelta, t_var *data);
void		debug_setting(double xdelta, double ydelta, t_var *data);
void		fov_setting(double xdelta, double ydelta, t_var *data);
void		zoom_setting(double xdelta, double ydelta, t_var *data);
void		style_setting(double xdelta, double ydelta, t_var *data);
void		offset_setting(double xdelta, double ydelta, t_var *data);
void		height_setting(double xdelta, double ydelta, t_var *data);
void		width_setting(double xdelta, double ydelta, t_var *data);

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