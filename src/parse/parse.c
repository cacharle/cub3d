/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:21 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 01:27:22 by cacharle         ###   ########.fr       */
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
	if ((i = parse_premap(state, lines)) == -1)
	{
		return (error_put_return_lines_state_destroy(
					"parse option", state, lines));
	}
	if (state->pflags != 0xFF || (state = parse_map(state, lines + i)) == NULL)
	{
		return (error_put_return_lines_state_destroy(state == NULL ?
					"parse map" : "parse options", state, lines));
	}
	helper_free_splited(lines);
	return (state);
}

static t_option_parser	g_option_parsers[] =
{
	{"R ", parse_resolution},
	{"NO ", parse_north_texture},
	{"SO ", parse_south_texture},
	{"WE ", parse_west_texture},
	{"EA ", parse_east_texture},
	{"S ", parse_sprite_texture},
	{"F ", parse_floor_color},
	{"C ", parse_ceilling_color}
};

t_bool	parse_line(t_state *state, char *line)
{
	int			i;
	char		*tmp;

	if (!*line)
		return (TRUE);
	i = -1;
	while (++i < (int)(sizeof(g_option_parsers) / sizeof(t_option_parser)))
	{
		if (ft_strncmp(g_option_parsers[i].id, line,
				ft_strlen(g_option_parsers[i].id)) == 0)
		{
			tmp = line + ft_strlen(g_option_parsers[i].id);
			while (*tmp == ' ')
				tmp++;
			return (g_option_parsers[i].func(state, tmp));
		}
	}
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
	if ((state->map = (t_map)ft_calloc(i, sizeof(t_cell*))) == NULL)
		return (NULL);
	state->map_width = ft_strcount(*lines, '1');
	i = -1;
	while (lines[++i] != NULL)
		if ((state->map[i] = create_map_row(state, lines[i])) == NULL)
			return (NULL);
	return (state);
}

t_cell	*create_map_row(t_state *state, char *line)
{
	int		i;
	t_cell	*row;

	if ((row = (t_cell*)malloc(sizeof(t_cell) * state->map_width)) == NULL)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (!create_map_row_char(*line, row, i++))
		{
			free(row);
			return (NULL);
		}
		line++;
		while (*line == ' ')
			line++;
	}
	if (i != state->map_width)
	{
		free(row);
		return (NULL);
	}
	return (row);
}
