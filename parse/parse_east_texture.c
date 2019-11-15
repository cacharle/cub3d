/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_east_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:29:37 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:31:02 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_east_texture(t_parsing *parsing, char *line)
{
	parsing->east_texture_path = ft_strdup(line + 1);
	return (TRUE);
}
