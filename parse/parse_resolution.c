#include "cub3d.h"

t_bool parse_resolution(t_parsing *parsing, char *line)
{
	parsing->resolution_width = ft_atoi(line);
	line = ft_strchr(line, ' ');
	parsing->resolution_height = ft_atoi(line);
	return (TRUE);
}
