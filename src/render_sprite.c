/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:39:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 03:38:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_stripe(t_state *state, t_sprite_state *sstate, int stripe)
{
	int tex_width;
	int	tex_height;
	int	tex_x;
	int	y;

	tex_width = state->textures[TEX_SPRITE].width;
	tex_height = state->textures[TEX_SPRITE].height;
	tex_x = (int)(256 * (stripe - (-sstate->sprite_width / 2 + sstate->sprite_window_x))
					* tex_width / sstate->sprite_width) / 256;
	if (!(sstate->transform.y > 0 && stripe > 0 && stripe < state->window.width && sstate->transform.y < state->z_buffer[stripe]))
		return ;
	y = sstate->draw_start - 1;
	while (++y < sstate->draw_end_y)
	{
		int d = y * 256 - state->window.height * 128 + sstate->sprite_height * 128; 
		int tex_y = ((d * tex_height) / sstate->sprite_height) / 256;
		t_color color = ((t_color*)state->textures[TEX_SPRITE].data)[tex_width * tex_y + tex_x];
		if ((color.hexcode & 0x00FFFFFF) != 0)
			((t_color*)state->window.data)[y * state->window.width + stripe] = color;
	}
}

static void			sprite_boundary(t_state *state, t_sprite_state *sstate)
{
	sstate->sprite_height = ft_abs((int)(state->window.height
							/ (sstate->transform.y)));
	sstate->draw_start = -sstate->sprite_height / 2 + state->window.height / 2;
	if(sstate->draw_start < 0)
		sstate->draw_start = 0;
	sstate->draw_end_y = sstate->sprite_height / 2 + state->window.height / 2;
	if(sstate->draw_end_y >= state->window.height)
		sstate->draw_end_y = state->window.height - 1;
	sstate->sprite_width = ft_abs( (int) (state->window.height
				/ (sstate->transform.y)));
	sstate->draw_start_x = -sstate->sprite_width / 2 + sstate->sprite_window_x;
	if (sstate->draw_start_x < 0)
		sstate->draw_start_x = 0;
	sstate->draw_end_x = sstate->sprite_width / 2 + sstate->sprite_window_x;
	if (sstate->draw_end_x >= state->window.width)
		sstate->draw_end_x = state->window.width - 1;
}

static void			render_sprite(t_state *state, int i)
{
	int				stripe;
	t_sprite_state	sstate;

	sstate.sprite.x = state->sprites[i].pos.x - state->pos.x;
	sstate.sprite.y = state->sprites[i].pos.y - state->pos.y;
	sstate.inverse_det = 1.0 / (state->plane.x
							* state->dir.y - state->dir.x * state->plane.y);
	sstate.transform.x = sstate.inverse_det
		* (state->dir.y * sstate.sprite.x - state->dir.x * sstate.sprite.y);
	sstate.transform.y = sstate.inverse_det * (-state->plane.y
			* sstate.sprite.x + state->plane.x * sstate.sprite.y);
	sstate.sprite_window_x = (int)((state->window.width / 2)
			* (1 + sstate.transform.x / sstate.transform.y));
	sprite_boundary(state, &sstate);
	stripe = sstate.draw_start_x - 1;
	while (++stripe < sstate.draw_end_x)
		draw_stripe(state, &sstate, stripe);
}

void				render_update_sprite(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->sprites_num)
		render_sprite(state, i);
}
