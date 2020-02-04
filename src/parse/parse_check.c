/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:59:15 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 05:07:22 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	check_player_count(t_state *state)
{
	int	i;
	int	j;
	int player_count;

	player_count = 0;
	i = -1;
	while (++i < state->map_height)
	{
		j = -1;
		while (++j < state->map_width)
			if (helper_is_player_cell(state->map[i][j]))
				player_count++;
	}
	return (player_count == 1);
}

t_state			*parse_check(t_state *state)
{
	int	i;

	if (state == NULL)
		return (NULL);
	i = -1;
	while (++i < state->map_width)
	{
		if (state->map[0][i] != CELL_WALL
				|| state->map[state->map_height - 1][i] != CELL_WALL)
			return (error_put_return_state_destroy(
						"validate map without borders", state));
	}
	i = -1;
	while (++i < state->map_height)
	{
		if (state->map[i][0] != CELL_WALL
				|| state->map[i][state->map_width - 1] != CELL_WALL)
			return (error_put_return_state_destroy(
						"validate map without borders", state));
	}
	if (!check_player_count(state))
	{
		return (error_put_return_state_destroy(
					"validate map with other than one player", state));
	}
	return (state);
}
