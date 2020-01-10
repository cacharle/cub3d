/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/10 11:27:56 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROTATE_SIZE (M_PI / 20.0)
#define MOVE_SPEED 0.25

int	handle_keydown(int key, void *param)
{
	t_state	*state;

	state = (t_state*)param;
	if (key == MLXK_ESC)
		state->running = FALSE;
	if (key == MLXK_A)
		state->pos = vector_add(state->pos, vector_scale(vector_rotate(state->dir, M_PI_2), MOVE_SPEED));
	if (key == MLXK_D)
		state->pos = vector_add(state->pos, vector_scale(vector_rotate(state->dir, -M_PI_2), MOVE_SPEED));
	if (key == MLXK_W)
		state->pos = vector_add(state->pos, vector_scale(state->dir, MOVE_SPEED));
	if (key == MLXK_S)
		state->pos = vector_add(state->pos, vector_scale(state->dir, -MOVE_SPEED));
	if (key == MLXK_LEFT)
		state->dir = vector_rotate(state->dir, -ROTATE_SIZE);
	if (key == MLXK_RIGHT)
		state->dir = vector_rotate(state->dir, ROTATE_SIZE);
	return (0);
}
