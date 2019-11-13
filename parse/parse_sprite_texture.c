#include "cub3d.h"

t_bool parse_sprite_texture(t_parsing *parsing, char *line)
{
	parsing->sprite_texture_path = ft_strdup(line + 1);
	return (TRUE);
}

