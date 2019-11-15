/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:37 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:27:55 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int key, void *param)
{
	t_state	*state;

	state = (t_state*)param;
	if (key == MLXK_ESC)
		state->running = FALSE;
	return (0);
}
