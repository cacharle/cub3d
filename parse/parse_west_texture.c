#include "cub3d.h"

t_bool parse_west_texture(t_parsing *parsing, char *line)
{
	parsing->west_texture_path = ft_strdup(line + 1);
	return (TRUE);
}

