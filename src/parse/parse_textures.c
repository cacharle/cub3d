/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 09:47:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 00:06:18 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	parse_north_texture(t_state *state, char *line)
{
	if (state->pflags & PFLAGS_NO)
		return (FALSE);
	if ((state->textures_path[TEX_NORTH] = ft_strdup(line)) == NULL)
		return (FALSE);
	state->pflags |= PFLAGS_NO;
	return (TRUE);
}

t_bool	parse_south_texture(t_state *state, char *line)
{
	if (state->pflags & PFLAGS_SO)
		return (FALSE);
	if ((state->textures_path[TEX_SOUTH] = ft_strdup(line)) == NULL)
		return (FALSE);
	state->pflags |= PFLAGS_SO;
	return (TRUE);
}

t_bool	parse_west_texture(t_state *state, char *line)
{
	if (state->pflags & PFLAGS_WE)
		return (FALSE);
	if ((state->textures_path[TEX_WEST] = ft_strdup(line)) == NULL)
		return (FALSE);
	state->pflags |= PFLAGS_WE;
	return (TRUE);
}

t_bool	parse_east_texture(t_state *state, char *line)
{
	if (state->pflags & PFLAGS_EA)
		return (FALSE);
	if ((state->textures_path[TEX_EAST] = ft_strdup(line)) == NULL)
		return (FALSE);
	state->pflags |= PFLAGS_EA;
	return (TRUE);
}

t_bool	parse_sprite_texture(t_state *state, char *line)
{
	if (state->pflags & PFLAGS_S)
		return (FALSE);
	if ((state->textures_path[TEX_SPRITE] = ft_strdup(line)) == NULL)
		return (FALSE);
	state->pflags |= PFLAGS_S;
	return (TRUE);
}
