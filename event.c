/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/17 13:59:48 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROTATE_STEP (M_PI / 20.0)
#define MOVE_SPEED 0.25

int	event_keydown(int key, t_state *state)
{
	if (key == MLXK_ESC)
		state->running = FALSE;
	else if (key == MLXK_A)
		state->pos = vector_add(state->pos,
				vector_scale(vector_rotate(state->dir, M_PI_2), MOVE_SPEED));
	else if (key == MLXK_D)
		state->pos = vector_add(state->pos,
				vector_scale(vector_rotate(state->dir, -M_PI_2), MOVE_SPEED));
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
	return (0);
}

int event_quit(t_state *state)
{
	state->running = FALSE;
}
