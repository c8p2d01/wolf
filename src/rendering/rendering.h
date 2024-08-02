#ifndef RENDERING_H
# define RENDERING_H

# ifndef CUB_H
#  include "../../inc/cub.h"
# endif

// floor_ceiling
void	floor_ceiling(t_var *data);
void	put_slice(t_var *data, int i);
void	render_view(t_var *data);
#endif