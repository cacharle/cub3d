#include "cub3d.h"

t_bool parse_south_texture(t_parsing *parsing, char *line)
{
	parsing->south_texture_path = ft_strdup(line + 1);
	return (TRUE);
}

