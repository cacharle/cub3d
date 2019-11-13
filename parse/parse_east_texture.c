#include "cub3d.h"

t_bool parse_east_texture(t_parsing *parsing, char *line)
{
	parsing->east_texture_path = ft_strdup(line + 1);
	return (TRUE);
}

