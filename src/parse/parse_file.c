/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 03:50:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 01:27:26 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**trim_file_lines(char **lines)
{
	int		i;
	char	*tmp;

	if (lines == NULL)
		return (NULL);
	i = -1;
	while (lines[++i] != NULL)
	{
		if ((tmp = ft_strtrim(lines[i], " ")) == NULL)
			return (NULL);
		lines[i] = tmp;
	}
	return (lines);
}

char		**get_file_lines(char *filename)
{
	int		fd;
	int		ret;
	char	buf[CUB3D_BUFFER_SIZE + 1];
	char	*file;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if ((file = ft_strdup("")) == NULL)
		return (NULL);
	while ((ret = read(fd, buf, CUB3D_BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((file = ft_strjoin(file, buf)) == NULL)
			return (NULL);
	}
	if (ret == -1)
		return (NULL);
	close(fd);
	return (trim_file_lines(ft_split_strict(file, '\n')));
}

int			parse_premap(t_state *state, char **lines)
{
	int	i;

	i = -1;
	while (lines[++i] != NULL)
	{
		if (*lines[i] == '\n')
			continue ;
		if (*lines[i] == '1')
			break ;
		if (!parse_line(state, lines[i]))
			return (-1);
	}
	return (i);
}

t_bool		create_map_row_char(char c, t_cell *row, int i)
{
	if (c == '0' || c == '1' || c == '2')
		row[i] = c - '0';
	else if (c == 'N')
		row[i] = CELL_LOOK_NORTH;
	else if (c == 'S')
		row[i] = CELL_LOOK_SOUTH;
	else if (c == 'W')
		row[i] = CELL_LOOK_WEST;
	else if (c == 'E')
		row[i] = CELL_LOOK_EAST;
	else
		return (FALSE);
	return (TRUE);
}
