#include "cub3d.h"

t_bool parse_ceilling_color(t_parsing *parsing, char *line)
{
	line++;
	parsing->ceilling_color.r = ft_atoi(line);
	line = ft_strchr(line, ',');
	parsing->ceilling_color.g = ft_atoi(line);
	line = ft_strchr(line, ',');
	parsing->ceilling_color.b = ft_atoi(line);
	return (TRUE);
}
