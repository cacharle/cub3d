/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_west_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:42 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:30:40 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_west_texture(t_parsing *parsing, char *line)
{
	parsing->west_texture_path = ft_strdup(line + 1);
	return (TRUE);
}
