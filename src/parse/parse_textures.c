/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 09:47:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/02 19:21:39 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_north_texture(t_state *state, char *line)
{
	if ((state->textures_path[TEX_NORTH] = ft_strdup(line)) == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	parse_south_texture(t_state *state, char *line)
{
	if ((state->textures_path[TEX_SOUTH] = ft_strdup(line)) == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	parse_west_texture(t_state *state, char *line)
{
	if ((state->textures_path[TEX_WEST] = ft_strdup(line)) == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	parse_east_texture(t_state *state, char *line)
{
	if ((state->textures_path[TEX_EAST] = ft_strdup(line)) == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	parse_sprite_texture(t_state *state, char *line)
{
	if ((state->textures_path[TEX_SPRITE] = ft_strdup(line)) == NULL)
		return (FALSE);
	return (TRUE);
}
