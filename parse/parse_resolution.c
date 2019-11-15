/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:27 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:31:47 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_resolution(t_parsing *parsing, char *line)
{
	parsing->resolution_width = ft_atoi(line);
	line = ft_strrchr(line, ' ') + 1;
	parsing->resolution_height = ft_atoi(line);
	return (TRUE);
}
