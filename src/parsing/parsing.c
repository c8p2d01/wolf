#include "../../inc/parsing.h"

int32_t	parse_input(int argc, char **argv, t_var *data)
{
	t_list	*text;
	int32_t	map_width;
	int32_t	map_start;

	if (argument_count(argc) || file_name(argv))
		return (1);
	map_width = 0;
	map_start = 0;
	text = NULL;
	if (file_read(argv[1], &text))
		return (1);
	if (parse_values(text, data, &map_start))
		return (ft_lstclear(&text, free), 1);
	if (construct_map(data, text, map_start, 0))
		return (ft_lstclear(&text, free), 1);
	if (check_space_separation(data))
		return (ft_lstclear(&text, free), 1);
	if (check_map(data))
		return (ft_lstclear(&text, free), 1);
	if (find_player(data))
		return (ft_lstclear(&text, free), 1);
	if (incomplete(data))
		return (ft_lstclear(&text, free), 1);
	data->text = text;
	return (0);
}
