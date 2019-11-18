/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:32 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/18 02:43:36 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_floor_color(t_parsing *parsing, char *line)
{
	line++;
	parsing->floor_color.rgb.r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	parsing->floor_color.rgb.g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	parsing->floor_color.rgb.b = ft_atoi(line);
	return (TRUE);
}
