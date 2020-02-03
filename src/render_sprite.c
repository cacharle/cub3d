/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:39:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/02 23:52:29 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		sprite_compar(const void *a, const void *b)
{
	const t_sprite	*sprite_a;
	const t_sprite	*sprite_b;

	sprite_a = a;
	sprite_b = b;
	if (sprite_a->dist > sprite_b->dist)
		return -1;
	if (sprite_a->dist < sprite_b->dist)
		return 1;
	return 0;
}

void	sprites_dist(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->sprites_num)
		state->sprites[i].dist = vector_norm(vector_sub(state->sprites[i].pos, state->pos));
}

void	render_update_sprite(t_state *state)
{
	sprites_dist(state);
	ft_qsort(state->sprites, state->sprites_num, sizeof(t_sprite), sprite_compar);
	for(int i = 0; i < state->sprites_num; i++)
	{
		double sprite_x = state->sprites[i].pos.x - state->pos.x;
		double sprite_y = state->sprites[i].pos.y - state->pos.y;

		double inverse_det = 1.0 / (state->plane.x * state->dir.y - state->dir.x * state->plane.y);
		double transform_x = inverse_det * (state->dir.y * sprite_x - state->dir.x * sprite_y);
		double transform_y = inverse_det * (-state->plane.y * sprite_x + state->plane.x * sprite_y);
		int sprite_window_x = (int)((state->window.width / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(state->window.height / (transform_y)));
		int draw_start = -sprite_height / 2 + state->window.height / 2;
		if(draw_start < 0)
		   	draw_start = 0;
		int draw_end_y = sprite_height / 2 + state->window.height / 2;
		if(draw_end_y >= state->window.height)
		   	draw_end_y = state->window.height - 1;

		int sprite_width = abs( (int) (state->window.height / (transform_y)));
		int draw_start_x = -sprite_width / 2 + sprite_window_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_window_x;
		if (draw_end_x >= state->window.width)
			draw_end_x = state->window.width - 1;

		for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_width = state->textures[TEX_SPRITE].width;
			int tex_height = state->textures[TEX_SPRITE].height;
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_window_x)) * tex_width / sprite_width) / 256;
			if(transform_y > 0 && stripe > 0 && stripe < state->window.width && transform_y < state->z_buffer[stripe])
				for(int y = draw_start; y < draw_end_y; y++)
				{
					int d = y * 256 - state->window.height * 128 + sprite_height * 128; 
					int tex_y = ((d * tex_height) / sprite_height) / 256;
					t_color color = ((t_color*)state->textures[TEX_SPRITE].data)[tex_width * tex_y + tex_x];
					if ((color.hexcode & 0x00FFFFFF) != 0) // if not empty pixel
						((t_color*)state->window.data)[y * state->window.width + stripe] = color;
				}
		}
	}
}
