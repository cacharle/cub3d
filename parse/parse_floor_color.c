/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:32 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:31:16 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_floor_color(t_parsing *parsing, char *line)
{
	line++;
	parsing->floor_color.r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	parsing->floor_color.g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	parsing->floor_color.b = ft_atoi(line);
	return (TRUE);
}
