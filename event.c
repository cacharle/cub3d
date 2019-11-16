/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/16 12:44:15 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int key, void *param)
{
	t_state	*state;

	/* printf("%d\n", key); */
	state = (t_state*)param;
	if (key == MLXK_ESC)
		state->running = FALSE;
	if (key == MLXK_A)
		state->pos.x -= 0.5;
	if (key == MLXK_D)
		state->pos.x += 0.5;
	if (key == MLXK_W)
		state->pos.y -= 0.5;
	if (key == MLXK_S)
		state->pos.y += 0.5;
	return (0);
}
