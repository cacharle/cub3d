/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:21 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 12:59:58 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state	*parse(char *filename)
{
	int		i;
	char	**lines;
	t_state	*state;

	if ((state = state_new_empty()) == NULL)
		return (error_put_return("create empty state"));
	if ((lines = get_file_lines(filename)) == NULL)
		return (error_put_return_state_destroy("read .cub file", state));
	i = -1;
	while (lines[++i] != NULL)
	{
		if (*lines[i] == '1')
			break ;
		if (!parse_line(state, lines[i]))
			return (error_put_return_lines_state_destroy(
						"parse configuration", state, lines));
	}
	if ((state = parse_map(state, lines + i)) == NULL)
		return (error_put_return_lines_state_destroy(
					"parse map", state, lines));
	helper_free_splited(lines);
	return (state);
}

char	**get_file_lines(char *filename)
{
	int		fd;
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*file;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if ((file = ft_strdup("")) == NULL)
		return (NULL);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((file = ft_strjoin(file, buf)) == NULL)
			return (NULL);
	}
	if (ret == -1)
		return (NULL);
	close(fd);
	return (ft_split(file, '\n'));
}

static t_option_parser	g_option_parsers[] =
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

#define OPTIONS_PARSERS_SIZE (sizeof(g_option_parsers) / sizeof(t_option_parser))

t_bool	parse_line(t_state *state, char *line)
{
	int i;

	if (!*line)
		return (TRUE);
	i = -1;
	while (++i < (int)OPTIONS_PARSERS_SIZE)
		if (ft_strncmp(g_option_parsers[i].id, line,
				ft_strlen(g_option_parsers[i].id)) == 0)
			return (g_option_parsers[i].func(
					state, line + ft_strlen(g_option_parsers[i].id) + 1));
	return (FALSE);
}

t_state	*parse_map(t_state *state, char **lines)
{
	int		i;

	i = -1;
	while (lines[++i] != NULL)
		if (*lines[i] != '1')
			return (NULL);
	state->map_height = i;
	if ((state->map = (t_map)malloc(sizeof(t_cell*) * i)) == NULL)
		return (NULL);
	state->map_width = ft_strcount(*lines, '1');
	i = -1;
	while (lines[++i] != NULL)
		if ((state->map[i] = create_map_row(lines[i])) == NULL)
			return (NULL);
	return (state);
}

t_cell	*create_map_row(char *line)
{
	int		i;
	t_cell	*row;

	if ((row = (t_cell*)malloc(sizeof(t_cell) * ft_strlen(line))) == NULL)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == '2')
			row[i++] = *line - '0';
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
