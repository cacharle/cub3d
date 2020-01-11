/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/12 15:45:03 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WINDOW_MID_HEIGHT(state) (state->window.height / 2)

int		render_update(void *param)
{
	t_state *state;

	state = param;
	if (!state->running)
	{
		state_destroy(state);
		exit(EXIT_SUCCESS);
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
	t_vector	ray;
	t_vector	map_pos;
	t_vector	delta;
	t_side		side;
	int			line_height;

	ray = get_ray(state, x);
	map_pos = vector_new((double)((int)state->pos.x), (double)((int)state->pos.y));
	delta = get_delta(ray);
	current = get_init_delta(state, ray, map_pos, delta);
	map_step = get_map_step(&ray);
	while (TRUE)
	{
		side = current.x < current.y ? SIDE_WE : SIDE_WE;
		helper_ray_next(&current, map_pos, delta, map_step);
		if (state->map[(int)map_pos.y][(int)map_pos.x] == CELL_WALL)
			break;
	}
	line_height = get_line_height(state, get_perp_dist(), side);
	render_window_column(state, x, WINDOW_MID_HEIGHT(state) - line_height / 2,
								WINDOW_MID_HEIGHT(state) + line_height / 2);
}

void	render_window_column(t_state *state, int x, int start, int end)
{
	int		i;
	t_color	white;

	white.hexcode = 0x00ffffff;
	i = -1;
	while (++i < draw_start)
		((t_color*)state->window.data)[i * state->window.width + x] = state->ceilling_color;
	while (++i < draw_end)
		((t_color*)state->window.data)[i * state->window.width + x] = white;
	while (++i < state->window_height)
		((t_color*)state->window.data)[i * state->window.width + x] = state->floor_color;
}
