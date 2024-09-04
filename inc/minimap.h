#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub.h"

// draw_mini_rays

void	calc_distances(t_var *data, t_draw_ray *draw_r);
void	hit_wall(t_var *data, t_draw_ray *draw_r);
void	identify_wall(t_var *data, t_draw_ray *draw_r);
void	identify_wall_fraction(t_var *data, t_draw_ray *draw_r);
void	draw_ray(t_var *data, t_draw_ray *draw_r);
void	draw_fov_lines(t_var *data);

// draw_triangle

int		set_ds_vectors(vec2d_t *d, vec2d_t *s, vec2d_t *zeroth, vec2d_t *first);
void	update_e2_y(double *err, vec2d_t *d, vec2d_t *s, vec2d_t *zeroth);
void	update_e2_x(double *err, vec2d_t *d, vec2d_t *s, vec2d_t *zeroth);
void	draw_line(mlx_image_t *img, vec2d_t zeroth, vec2d_t first, int color);
void	draw_player_triangle(t_var *data);

// map_plane

void	filler(t_var *data);
void	layout_color(t_var *data, int zoom_x, int zoom_y, char c);
void	mini_filler(t_var *data, int x, int y, char c);
void	redraw_minimap(t_var *data);
void	prot_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color);

#endif