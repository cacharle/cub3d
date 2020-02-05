/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:39:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 23:25:21 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 1: While raycasting the walls, store the perpendicular distance
**    of each vertical stripe in a 1D ZBuffer
** 2: Calculate the distance of each sprite to the player
** 3: Use this distance to sort the sprites, from furthest away
**    to closest to the camera
** 4: Project the sprite on the camera plane (in 2D):
**    subtract the player position from the sprite position,
**    then multiply the result with the inverse of the 2x2 camera matrix
** 5: Calculate the size of the sprite on the screen
**    (both in x and y direction) by using the perpendicular distance
** 6: Draw the sprites vertical stripe by vertical stripe,
**    don't draw the vertical stripe if the distance is further away
**    than the 1D ZBuffer of the walls of the current stripe
** 7: Draw the vertical stripe pixel by pixel, make sure there's
**    an invisible color or all sprites would be rectangles
*/

static void		draw_stripe_pixels(t_state *state, t_sprite_state *sstate,
									int stripe, int tex_x)
{
	int		y;
	int		d;
	int		tex_y;
	t_color	color;

	y = sstate->draw_start - 1;
	while (++y < sstate->draw_end_y)
	{
		d = y * 256 - state->window.height * 128 + sstate->sprite_height * 128;
		tex_y = (d * state->textures[TEX_SPRITE].height)
					/ (sstate->sprite_height * 256);
		color = ((t_color*)state->textures[TEX_SPRITE].data)
						[state->textures[TEX_SPRITE].width * tex_y + tex_x];
		if ((color.hexcode & 0x00FFFFFF) != 0)
			((t_color*)state->window.data)[y * state->window.width + stripe] =
				color;
	}
}

static void		draw_stripe(t_state *state, t_sprite_state *sstate, int stripe)
{
	int tex_width;
	int	tex_height;
	int	tex_x;

	tex_width = state->textures[TEX_SPRITE].width;
	tex_height = state->textures[TEX_SPRITE].height;
	tex_x = (int)(256 * (stripe - (-sstate->sprite_width / 2
				+ sstate->sprite_window_x))
				* tex_width / sstate->sprite_width) / 256;
	if (!(sstate->transform.y > 0 && stripe > 0 && stripe < state->window.width
			&& sstate->transform.y < state->z_buffer[stripe]))
		return ;
	draw_stripe_pixels(state, sstate, stripe, tex_x);
}

static void		sprite_boundary(t_state *state, t_sprite_state *sstate)
{
	sstate->sprite_height = ft_abs((int)(state->window.height
							/ (sstate->transform.y)));
	sstate->draw_start = -sstate->sprite_height / 2 + state->window.height / 2;
	if (sstate->draw_start < 0)
		sstate->draw_start = 0;
	sstate->draw_end_y = sstate->sprite_height / 2 + state->window.height / 2;
	if (sstate->draw_end_y >= state->window.height)
		sstate->draw_end_y = state->window.height - 1;
	sstate->sprite_width = ft_abs((int)(state->window.height
				/ (sstate->transform.y)));
	sstate->draw_start_x = -sstate->sprite_width / 2 + sstate->sprite_window_x;
	if (sstate->draw_start_x < 0)
		sstate->draw_start_x = 0;
	sstate->draw_end_x = sstate->sprite_width / 2 + sstate->sprite_window_x;
	if (sstate->draw_end_x >= state->window.width)
		sstate->draw_end_x = state->window.width - 1;
}

static void		render_sprite(t_state *state, int i)
{
	int				stripe;
	t_sprite_state	sstate;
	double			inverse_det;
	t_vector		sprite;

	sprite = vector_add(state->sprites[i].pos, vector_scale(state->pos, -1.0));
	inverse_det = 1.0 / (state->plane.x * state->dir.y
						- state->dir.x * state->plane.y);
	sstate.transform.x = state->dir.y * sprite.x - state->dir.x * sprite.y;
	sstate.transform.y =
			-state->plane.y * sprite.x + state->plane.x * sprite.y;
	sstate.transform = vector_scale(sstate.transform, inverse_det);
	sstate.sprite_window_x = (int)((state->window.width / 2.0)
			* (1.0 + sstate.transform.x / sstate.transform.y));
	sprite_boundary(state, &sstate);
	stripe = sstate.draw_start_x - 1;
	while (++stripe < sstate.draw_end_x)
		draw_stripe(state, &sstate, stripe);
}

void			render_update_sprite(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->sprites_num)
		render_sprite(state, i);
}
