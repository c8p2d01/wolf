#ifndef MOVEMENT_H
# define MOVEMENT_H

# ifndef CUB_H
#  include "../../inc/cub.h"
# endif

typedef enum function_callsign
{
	LEFT	= 1,
	RIGHT	= 0,
}	function_callsign_t;

typedef enum key_state
{
	UP		= 0,
	PRESS	= 1,
	MINUS	= 2,
}	key_state_t;

// move
void	straight(t_var *data, key_state_t action);
void	strafe(t_var *data, key_state_t action);
void	turn(t_var *data, int direction);
void	apply_movement(t_var *data);
void	display_movement(t_var *data);

// wall_collision
bool	wall_collision(t_var *data);

#endif