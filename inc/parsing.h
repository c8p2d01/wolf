#ifndef PARSING_H
# define PARSING_H

# include "cub.h"

// file processing

int32_t	argument_count(int argc);
int32_t	file_name(char **argv);
int32_t	file_read(char *file, t_list **text);

// map variables

int32_t	construct_map(t_var *data, t_list *text, int map_start, int32_t i);
int32_t	parse_values(t_list *text, t_var *data, int *map_start);
int32_t	check_variable(t_var *data, char *line);
int32_t	set_variable(t_var *data, char **elmnts);
int32_t	calculate_color(char *rgb);

// map validation

int32_t	check_map(t_var *data);
int32_t	map_checking_x(char **map);
char	**rotate_table(char **base);
char	*column_to_line(char **table, int index);

// player extraction

int32_t	find_player(t_var *data);
int32_t	extract_player(t_var *data);
int32_t	init_player(t_var *data, char pov);

// utils

void	print_data(t_var *data);
int32_t	incomplete(t_var *data);
int32_t	free_data(t_var *data);
int32_t	texture_init(char *file, mlx_texture_t **dest);
void	update_map_width(t_var *data, t_list *map_text);

#endif