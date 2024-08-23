#ifndef SETTINGS_H
# define SETTINGS_H

# include "cub.h"
# include "configs.h"

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
void		move_setting(double xdelta, double ydelta, t_var *data);
void		turn_setting(double xdelta, double ydelta, t_var *data);
void		turn_mouse_setting(double xdelta, double ydelta, t_var *data);

#endif