#include "cub3d.h"

t_bool parse_north_texture(t_parsing *parsing, char *line)
{
	parsing->north_texture_path = ft_strdup(line + 1);
	return (TRUE);
}

