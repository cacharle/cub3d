/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:21 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:32:54 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parsing	*parse(char *filename)
{
	int			i;
	char		**lines;
	t_parsing	*parsing;

	if ((lines = get_file_lines(filename)) == NULL)
		return (NULL);
	if ((parsing = (t_parsing*)malloc(sizeof(t_parsing))) == NULL)
		return (NULL);
	parsing->map = NULL;
	i = -1;
	while (lines[++i] != NULL)
	{
		if (*lines[i] == '1')
			break ;
		if (!parse_line(parsing, lines[i]))
			return (NULL);
	}
	if ((parsing = parse_map(parsing, lines + i)) == NULL)
		return (NULL);
	free(lines);
	return (parsing);
}

char		**get_file_lines(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	char	*file;

	fd = open(filename, O_RDONLY);
	if ((file = ft_strdup("")) == NULL)
		return (NULL);
	while ((ret = get_next_line(fd, &line)) == 1)
		if ((file = ft_strjoin_free(file, ft_strjoin_free(line, ft_strdup("\n"), 2), 2)) == NULL)
			return (NULL);
	if (ret == -1)
		return (NULL);
	free(line);
	close(fd);
	return (ft_split(file, '\n'));
}

static t_option_parser	option_parsers[] =
{
	{"R", parse_resolution},
	{"NO", parse_north_texture},
	{"SO", parse_south_texture},
	{"WE", parse_west_texture},
	{"EA", parse_east_texture},
	{"S", parse_sprite_texture},
	{"F", parse_floor_color},
	{"C", parse_ceilling_color}
};

#define OPTIONS_PARSERS_SIZE (sizeof(option_parsers) / sizeof(t_option_parser))

t_bool		parse_line(t_parsing *parsing, char *line)
{
	int i;

	if (!*line)
		return (TRUE);
	i = -1;
	while (++i < (int)OPTIONS_PARSERS_SIZE)
		if (ft_strncmp(option_parsers[i].id, line, ft_strlen(option_parsers[i].id)) == 0)
			return (option_parsers[i].func(parsing, line + ft_strlen(option_parsers[i].id)));
	return (FALSE);
}

t_parsing	*parse_map(t_parsing *parsing, char **lines)
{
	int		i;

	i = -1;
	while (lines[++i] != NULL)
		if (*lines[i] != '1')
			return (NULL);
	parsing->map_height = i;
	if ((parsing->map = (t_map)malloc(sizeof(t_cell*) * i)) == NULL)
		return (NULL);
	parsing->map_width = ft_strcount(*lines, '1');
	i = -1;
	while (lines[++i] != NULL)
		if ((parsing->map[i] = create_map_row(lines[i])) == NULL)
			return (NULL);
	return (parsing);
}

t_cell		*create_map_row(char *line)
{
	int		i;
	t_cell	*row;

	if ((row = (t_cell*)malloc(sizeof(t_cell) * ft_strlen(line))) == NULL)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (*line == '0')
			row[i++] = CELL_EMPTY;
		else if (*line == '1')
			row[i++] = CELL_WALL;
		else if (*line == '2')
			row[i++] = CELL_ITEM;
		else if (*line == 'N')
			row[i++] = CELL_LOOK_NORTH;
		else if (*line == 'S')
			row[i++] = CELL_LOOK_SOUTH;
		else if (*line == 'W')
			row[i++] = CELL_LOOK_WEST;
		else if (*line == 'E')
			row[i++] = CELL_LOOK_EAST;
		else
		{
			free(row);
			return (NULL);
		}
		line++;
		while (*line == ' ')
			line++;
	}
	return (row);
}
