#include "cub3d.h"

t_parsing *parse(char *filename)
{
	int fd;
	int ret;
	char *line;
	t_parsing *parsing;

	if ((parsing = (t_parsing*)malloc(sizeof(t_parsing))) == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
		if (!parse_line(parsing, line))
			return (NULL);
	if (ret == -1)
		return (NULL);
	return (parsing);
}

static t_option_parser option_parsers[] = {
	{"R", parse_resolution},
	{"NO", parse_north_texture},
	{"SO", parse_south_texture},
	{"WE", parse_west_texture},
	{"EA", parse_east_texture},
	{"S", parse_sprite_texture},
	{"F", parse_floor_color},
	{"C", parse_ceilling_color},
};

#define OPTIONS_PARSER_SIZE (sizeof(line_parsers) / sizeof(t_line_parser))

t_bool parse_option(t_parsing *parsing, char *line)
{
	int i;

	if (!*line)
		return (TRUE);
	i = -1;
	while (++i < LINE_PARSER_SIZE)
		if (ft_strchr("012", *line) != NULL)
			return (parse_map(parsing, line));
		else if (ft_strncmp(option_parsers[i].id, line,
							ft_strlen(option_parsers[i].id)) == 0)
			return (option_parsers[i]
					.func(parsing, line + ft_strlen(option_parsers[i].id));
	return (FALSE);
}

t_bool parse_map(t_parsing *parsing, char *line)
{
	return (FALSE);
}
