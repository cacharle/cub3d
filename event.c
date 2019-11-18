/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/18 02:31:23 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROTATE_SIZE (M_PI / 20.0)
#define MOVE_SPEED 0.5

int	handle_key(int key, void *param)
{
	t_state	*state;

	/* printf("%d\n", key); */
	state = (t_state*)param;
	if (key == MLXK_ESC)
		state->running = FALSE;
	if (key == MLXK_A)
		state->pos = vector_add(state->pos, vector_rotate(vector_scale(state->dir, MOVE_SPEED), M_PI_2));
	if (key == MLXK_D)
		state->pos = vector_add(state->pos, vector_rotate(vector_scale(state->dir, MOVE_SPEED), -M_PI_2));
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
