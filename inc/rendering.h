#ifndef RENDERING_H
# define RENDERING_H

# include "cub.h"

// floor_ceiling
void	floor_ceiling(t_var *data);
// slicer
void	put_slice(t_var *data, int i);
void	render_view(t_var *data);
void	new_put_slice(t_var *data, int i);
void	put_texture(t_var *data, vec2d_t start, vec2d_t end, int height);
void	draw_line_b(t_var *data, int height, int raynum);
int		get_txtr_color(t_var *data, int i);
void	print_texture(t_var *data);
void	load_image(t_var *data);

// doors
void	toggle_doors(mlx_key_data_t key, t_var *data);
void	trace_door(t_var *data, t_draw_ray *draw_r);
void	identify_door(t_var *data, t_draw_ray *draw_r, bool door_axis);
int		check_door(int i, t_var *data);

void	whole_detail(t_var *data);
int		detail_color(t_var *data, int x, int y);
void	draw_colorful_line(t_var *data, int height, int raynum);
#endif