#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "cub.h"

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

// move
void	straight(t_var *data, t_key_state action);
void	strafe(t_var *data, t_key_state action);
void	turn(t_var *data, int direction);
void	apply_movement(t_var *data);
void	display_movement(t_var *data);

// wall_collision
bool	wall_collision(t_var *data, double step_len);
double	trace_movement(t_var *data);

#endif