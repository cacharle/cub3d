/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 11:38:43 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/01 14:11:07 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*texture_select(t_state *state, t_render_state *rstate)
{
	if (rstate->side == SIDE_NS)
	{
		if (rstate->map_pos.y < state->pos.y)
			return (state->textures + TEX_NORTH);
		else
			return (state->textures + TEX_SOUTH);
	}
	else if (rstate->side == SIDE_WE)
	{
		if (rstate->map_pos.x > state->pos.x)
			return (state->textures + TEX_WEST);
		else
			return (state->textures + TEX_EAST);
	}
	return (NULL);
}

/*
** Since we're drawing each column, all the texels we want to draw on the window
** are on a single column of the texture.
** First we find the x-coord relative to the wall we hit
*/

int		texture_x(t_state *state, t_render_state *rstate, t_image *texture)
{
	int		tex_x;
	double	wall_x;

	if (rstate->side == SIDE_WE)
		wall_x = state->pos.y + rstate->perp_dist * rstate->ray.y;
	else
		wall_x = state->pos.x + rstate->perp_dist * rstate->ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((rstate->side == SIDE_NS && rstate->ray.x > 0) ||
			(rstate->side == SIDE_WE && rstate->ray.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
