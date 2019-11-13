#include "cub3d.h"

t_bool parse_floor_color(t_parsing *parsing, char *line)
{
	line++;
	parsing->floor_color.r = ft_atoi(line);
	line = ft_strchr(line, ',');
	parsing->floor_color.g = ft_atoi(line);
	line = ft_strchr(line, ',');
	parsing->floor_color.b = ft_atoi(line);
	return (TRUE);
}
