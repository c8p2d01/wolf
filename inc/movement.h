#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "cub.h"

// orange to purple color variations
# define R1 "\033[38;5;178m"
# define R2 "\033[38;5;173m"
# define R3 "\033[38;5;168m"
# define R4 "\033[38;5;163m"

# define QUIT_COLOR "\033[0m"

typedef enum function_callsign
{
	LEFT	= 1,
	RIGHT	= 0,
}	t_function_callsign;

typedef enum key_state
{
	UP		= 0,
	PRESS	= 1,
	MINUS	= 2,
}	t_key_state;

void	cursor_hook(double xpos, double ypos, void *param);

// move
void	straight(t_var *data, t_key_state action);
void	strafe(t_var *data, t_key_state action);
void	turn(t_var *data, int direction);
void	apply_movement(t_var *data);

// wall_collision
double	wall_collision(t_var *data);
double	max_step(t_var *data, double side);

// mouse
void	enable_file(t_var *data);
void	disable_file(t_var *data);
void	mouse_action(t_var *data);

#endif