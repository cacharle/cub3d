/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:39:57 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/10 11:44:24 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state		*state_new(void *mlx_ptr, void *window_ptr, t_parsing *parsing)
{
	t_state *state;

	if ((state = (t_state*)malloc(sizeof(t_state))) == NULL)
		return (NULL);
	if ((state->north_texture = load_texture(parsing->north_texture_path)) == NULL)
		return (NULL);
	if ((state->south_texture = load_texture(parsing->south_texture_path)) == NULL)
		return (NULL);
	if ((state->west_texture = load_texture(parsing->west_texture_path)) == NULL)
		return (NULL);
	if ((state->east_texture = load_texture(parsing->east_texture_path)) == NULL)
		return (NULL);

	state->window_img.id = mlx_new_image(mlx_ptr, parsing->resolution_width, parsing->resolution_height);
	state->window_img.width = parsing->resolution_width;
	state->window_img.height = parsing->resolution_height;
	state->window_img.data = mlx_get_data_addr(state->window_img.id,
			&state->window_img.depth, &state->window_img.size_line, &state->window_img.endian);

	state->running = TRUE;
	state->mlx_ptr = mlx_ptr;
	state->window_ptr = window_ptr;
	state->window_width = parsing->resolution_width;
	state->window_height = parsing->resolution_height;
	state->map = parsing->map;
	state->map_width = parsing->map_width;
	state->map_height = parsing->map_height;
	state->ceilling_color = parsing->ceilling_color;
	state->floor_color = parsing->floor_color;

	state_new_player(state, parsing);

	return (state);
}

void	state_new_player(t_state *state, t_parsing *parsing)
{
	int	i;
	int j;

	i = -1;
	while (++i < parsing->map_height)
	{
		j = -1;
		while (++j < parsing->map_width)
			if (parsing->map[i][j] & (CELL_LOOK_NORTH | CELL_LOOK_SOUTH
									| CELL_LOOK_WEST | CELL_LOOK_EAST)
			{
				state->pos.x = (double)j + 0.5;
				state->pos.y = (double)i + 0.5;
				// break 2nd loop?
				break;
			}
	}
	/* need to be normalized */
	state->dir.x = 0.0;
	state->dir.y = 0.0;
	if (parsing->map[(int)state.y][(int)state.x] & CELL_LOOK_NORTH)
		state->dir.y = 1.0;
	else if (parsing->map[(int)state.y][(int)state.x] & CELL_LOOK_SOUTH)
		state->dir.y = -1.0;
	else if (parsing->map[(int)state.y][(int)state.x] & CELL_LOOK_WEST)
		state->dir.x = -1.0;
	else if (parsing->map[(int)state.y][(int)state.x] & CELL_LOOK_EAST)
		state->dir.x = 1.0;

	state->plane.x = 0.0;
	state->plane.y = 0.66;
}

void	state_destroy(t_state *state)
{
	mlx_destroy_window(state->mlx_ptr, state->window_ptr);
	free(state->north_texture);
	free(state->south_texture);
	free(state->west_texture);
	free(state->east_texture);
	free(state);
}
