/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_south_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:55 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:30:46 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_south_texture(t_parsing *parsing, char *line)
{
	parsing->south_texture_path = ft_strdup(line + 1);
	return (TRUE);
}
