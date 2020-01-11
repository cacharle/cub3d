/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:59:15 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 11:15:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state		*parse_check(t_state *state)
{
	int	i;
	int	j;
	int player_count;

	i = -1;
	while (++i < state->map_width)
		if (state->map[0][i] != CELL_WALL
				|| state->map[state->map_height - 1][i] != CELL_WALL)
			return (state_destroy(state));
	i = -1;
	while (++i < state->map_height)
		if (state->map[i][0] != CELL_WALL
				|| state->map[i][state->map_width - 1] != CELL_WALL)
			return (state_destroy(state));
	// maybe not necessary
	/* player_count = 0; */
	/* i = -1; */
	/* while (++i < state->map_height) */
	/* { */
	/* 	j = -1; */
	/* 	while (++j < state->map_width) */
	/* 		if (helper_is_player_cell(state->map[i][j])) */
	/* 			player_count++; */
	/* } */
	/* if (player_count != 1) */
	/* 	return (state_destroy(state)); */
	return (state);
}
