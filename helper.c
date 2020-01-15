/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 07:32:20 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/15 14:40:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	helper_is_player_cell(t_cell cell)
{
	return (cell == CELL_LOOK_NORTH || cell == CELL_LOOK_SOUTH ||
			cell == CELL_LOOK_WEST || cell == CELL_LOOK_EAST);
}

void	helper_free_splited(char **splited)
{
	int	i;

	if (splited == NULL)
		return ;
	i = -1;
	while (splited[++i] != NULL)
		free(splited[i]);
	free(splited);
}

void	helper_rotate_player(t_state *state, double rotation)
{
	state->dir = vector_rotate(state->dir, rotation);
	state->plane = vector_rotate(state->plane, rotation);
}

void	helper_init_dir_plane(t_state *state, int y, int x)
{
	if (state->map[y][x] == CELL_LOOK_NORTH)
		state->dir.y = 1.0;
	else if (state->map[y][x] == CELL_LOOK_SOUTH)
		state->dir.y = -1.0;
	else if (state->map[y][x] == CELL_LOOK_WEST)
		state->dir.x = -1.0;
	else if (state->map[y][x] == CELL_LOOK_EAST)
		state->dir.x = 1.0;
	state->plane = vector_rotate(state->dir, M_PI_2);
	state->plane = vector_scale(state->plane, 1.0 / vector_norm(state->plane));
	state->plane = vector_scale(state->plane, 0.66);
	state->plane = vector_apply(state->plane, &fabs);
}
