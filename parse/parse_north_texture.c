/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_north_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:47 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:30:52 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_north_texture(t_parsing *parsing, char *line)
{
	parsing->north_texture_path = ft_strdup(line + 1);
	return (TRUE);
}
