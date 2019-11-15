/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:30:05 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:31:56 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_sprite_texture(t_parsing *parsing, char *line)
{
	parsing->sprite_texture_path = ft_strdup(line + 1);
	return (TRUE);
}
