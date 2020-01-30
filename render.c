/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/30 15:17:49 by cacharle         ###   ########.fr       */
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
	render_update_window(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window.id, 0, 0);
	return (0);
}

void	render_update_window(t_state *state)
{
	int x;

	x = -1;
	while (++x < state->window.width)
		render_column(state, x);
}

void	render_column(t_state *state, int x)
{
	t_render_state	rstate;

	rstate.x = x;
	rstate_ray(state, &rstate);
	rstate.map_pos = vector_new((double)((int)state->pos.x), (double)((int)state->pos.y)); //floor?
	rstate_delta(&rstate);
	rstate_init_probe(state, &rstate);
	rstate.map_step = vector_new(rstate.ray.x < 0.0 ? -1.0 : 1.0, rstate.ray.y < 0.0 ? -1.0 : 1.0);
	while (TRUE)
	{
		rstate.side = rstate.probe.x < rstate.probe.y ? SIDE_WE : SIDE_NS;
		rstate_next_probe(&rstate);
		if (state->map[(int)rstate.map_pos.y][(int)rstate.map_pos.x] == CELL_WALL)
			break ;
	}
	rstate_perp_dist(state, &rstate);
	rstate_line_height(state, &rstate);
	rstate.draw_start = state->window.height / 2 - rstate.line_height / 2;
	rstate.draw_end = state->window.height / 2 + rstate.line_height / 2;
	if (rstate.draw_start < 0)
		rstate.draw_start = 0;
	if (rstate.draw_end > state->window.height - 1)
		rstate.draw_end = state->window.height - 1;
	render_window_column(state, &rstate);
}

void	render_window_column(t_state *state, t_render_state *rstate)
{
	int		i;
	t_color	white;

	white.hexcode = 0x00ffffff;
	i = 0;
	while (i < rstate->draw_start)
		((t_color*)state->window.data)[i++ * state->window.width + rstate->x] = state->ceilling_color;
	while (i < rstate->draw_end)
		((t_color*)state->window.data)[i++ * state->window.width + rstate->x] = white;
	render_texture(state, rstate);
	i = rstate->draw_end;
	while (i < state->window.height)
		((t_color*)state->window.data)[i++ * state->window.width + rstate->x] = state->floor_color;

}

void	render_texture(t_state *state, t_render_state *rstate)
{
	int 	i;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		tex_x;
	t_image	*texture;

	texture = get_tex(state, rstate);
	tex_x = get_tex_x(state, rstate, texture);
	step = 1.0 * texture->height / rstate->line_height;
	tex_pos = (rstate->draw_start - state->window.height / 2 + rstate->line_height / 2) * step;
	i = rstate->draw_start - 1;
	while (++i < rstate->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		((t_color*)state->window.data)[i * state->window.width + rstate->x] =
			((t_color*)texture->data)[texture->height * tex_y + tex_x];
	}
}
