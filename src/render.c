/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/01 14:15:44 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_update(void *param)
{
	t_state *state;

	state = param;
	if (!state->running)
	{
		state_destroy(state);
		exit(EXIT_SUCCESS);
		return (0);
	}
	state->surface = &state->window;
	render_update_window(state, CELL_WALL);
	/* state->surface = &state->sprite_window; */
	/* render_update_window(state, CELL_ITEM); */
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr,
			state->window.id, 0, 0);
	return (0);
}

void	render_update_window(t_state *state, t_cell target)
{
	int x;

	x = -1;
	while (++x < state->window.width)
		render_column(state, x, target);
}

void	render_column(t_state *state, int x, t_cell target)
{
	t_render_state	rstate;

	rstate.x = x;
	rstate_ray(state, &rstate);
	rstate.map_pos = vector_new((double)((int)state->pos.x), (double)((int)state->pos.y));
	rstate_delta(&rstate);
	rstate_init_probe(state, &rstate);
	rstate.map_step = vector_new(rstate.ray.x < 0.0 ? -1.0 : 1.0, rstate.ray.y < 0.0 ? -1.0 : 1.0);
	while (TRUE)
	{
		if (rstate.probe.x < 0 || rstate.probe.y < 0
				|| rstate.probe.x > state->map_width
				|| rstate.probe.y > state->map_height)
			return ;
		rstate.side = rstate.probe.x < rstate.probe.y ? SIDE_WE : SIDE_NS;
		rstate_next_probe(&rstate);
		if (state->map[(int)rstate.map_pos.y][(int)rstate.map_pos.x] == CELL_WALL)
			break ;
	}
	rstate_perp_dist(state, &rstate);
	rstate_line_height(state, &rstate);
	rstate.draw_start = state->surface->height / 2 - rstate.line_height / 2;
	rstate.draw_end = state->surface->height / 2 + rstate.line_height / 2;
	if (rstate.draw_start < 0)
		rstate.draw_start = 0;
	if (rstate.draw_end > state->surface->height - 1)
		rstate.draw_end = state->surface->height - 1;
	render_window_column(state, &rstate);
}

void	render_window_column(t_state *state, t_render_state *rstate)
{
	int		i;
	t_color	white;

	white.hexcode = 0x00ffffff;
	i = 0;
	while (i < rstate->draw_start)
		((t_color*)state->surface->data)[i++ * state->surface->width + rstate->x] =
			state->ceilling_color;
	i--;
	render_texture(state, rstate, &i);
	while (i < state->surface->height)
		((t_color*)state->surface->data)[i++ * state->surface->width + rstate->x] =
			state->floor_color;
}

void	render_texture(t_state *state, t_render_state *rstate, int *i)
{
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
	t_image	*texture;

	texture = texture_select(state, rstate);
	tex_x = texture_x(state, rstate, texture);
	tex_step = (double)texture->height / (double)rstate->line_height;
	tex_pos = (rstate->draw_start - state->surface->height / 2 + rstate->line_height / 2) * tex_step;
	while ((*i)++ < rstate->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += tex_step;
		/* ((t_color*)state->surface->data)[*i * state->surface->width + rstate->x] = */
		/* 	((t_color*)texture->data)[texture->height * tex_y + tex_x]; */
	}
}
