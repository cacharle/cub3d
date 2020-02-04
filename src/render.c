/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 02:31:57 by cacharle         ###   ########.fr       */
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
	render_update_sprite(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr,
								state->window.id, 0, 0);
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

	rstate_init(state, &rstate, x);
	while (TRUE)
	{
		rstate.side = rstate.probe.x < rstate.probe.y ? SIDE_WE : SIDE_NS;
		rstate_next_probe(&rstate);
		if (state->map[(int)rstate.map_pos.y][(int)rstate.map_pos.x]
				== CELL_WALL)
			break ;
	}
	rstate_post(state, &rstate);
	render_window_column(state, &rstate);
}

void	render_window_column(t_state *state, t_render_state *rstate)
{
	int		i;

	i = 0;
	while (i < rstate->draw_start)
		((t_color*)state->window.data)[i++ * state->window.width + rstate->x] =
			state->ceilling_color;
	i--;
	texture_render(state, rstate, &i);
	while (i < state->window.height)
		((t_color*)state->window.data)[i++ * state->window.width + rstate->x] =
			state->floor_color;
}
