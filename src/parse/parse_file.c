/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 03:50:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 04:28:41 by cacharle         ###   ########.fr       */
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
	return (trim_file_lines(ft_split(file, '\n')));
}
