/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 23:50:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROTATE_STEP (M_PI / 12.0)
#define MOVE_SPEED 0.40

static t_bool	valid_pos(t_state *state)
{
	return (state->pos.x > 0 && state->pos.y > 0
			&& state->pos.x < (double)(state->map_width - 1)
			&& state->pos.y < (double)(state->map_height - 1)
			&& state->map[(int)state->pos.y][(int)state->pos.x] != CELL_WALL
			&& state->map[(int)state->pos.y][(int)state->pos.x] != CELL_ITEM);
}

int				event_keydown(int key, t_state *state)
{
	t_vector	saved_pos;

	saved_pos = state->pos;
	if (key == MLXK_ESC)
		state->running = FALSE;
	else if (key == MLXK_A)
		state->pos = vector_add(state->pos,
				vector_scale(vector_rotate(state->dir, -M_PI_2), MOVE_SPEED));
	else if (key == MLXK_D)
		state->pos = vector_add(state->pos,
				vector_scale(vector_rotate(state->dir, M_PI_2), MOVE_SPEED));
	else if (key == MLXK_W)
		state->pos = vector_add(state->pos,
				vector_scale(state->dir, MOVE_SPEED));
	else if (key == MLXK_S)
		state->pos = vector_add(state->pos,
				vector_scale(state->dir, -MOVE_SPEED));
	else if (key == MLXK_LEFT)
		helper_rotate_player(state, -ROTATE_STEP);
	else if (key == MLXK_RIGHT)
		helper_rotate_player(state, ROTATE_STEP);
	if (!valid_pos(state))
		state->pos = saved_pos;
	return (0);
}

int				event_quit(t_state *state)
{
	state->running = FALSE;
	return (0);
}
