#ifndef RENDERING_H
# define RENDERING_H

# include "cub.h"

// floor_ceiling
void	floor_ceiling(t_var *data);
void	put_slice(t_var *data, int i);
void	render_view(t_var *data);
void	new_put_slice(t_var *data, int i);
void	put_texture(t_var *data, vec2d_t start, vec2d_t end, int height);
void	draw_line_b(t_var *data, vec2d_t zeroth, vec2d_t first, int ray_i);
int		get_txtr_color(t_var *data, int i);
void	print_texture(t_var *data);
void	load_image(t_var *data);

#endif