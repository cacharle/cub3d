/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 07:32:20 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/12 15:43:29 by cacharle         ###   ########.fr       */
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

/*
** -1      0       1 <-- camera_x
**  v      v       v
**  ################
**  #      |       # <-- screen
**  #      |       #
**  ################
**  
** camera_x is the x column from the camera percpective
** scaling the plane vector and adding it to the direction vector
** to create a vector in the *direction* of the column x.
*/

t_vector	get_ray(t_state *state, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)state->window.width - 1;
	return (vector_add(state->dir, vector_scale(state->plane, camera_x)));
}

/*
** delta between each grid unit form the vector percpective
**
** This can be simplified like (for some obscure reason):
** delta.x = fabs(1.0 / ray.x);
** delta.y = fabs(1.0 / ray.y);
*/

t_vector	get_delta(t_vector ray)
{
	t_vector delta;

	delta.x = sqrt(1.0 + (SQUARE(ray.y) / SQUARE(ray.x)));
	delta.y = sqrt(1.0 + (SQUARE(ray.x) / SQUARE(ray.y)));
	return (delta);
}

/*
** first delta between player position and first grid unit
**
** if (ray.x < 0)
**     current.x = state->pos.x - map_pos.x;
** else
**     current.x = fabs(state->pos.x - map_pos.x + 1.0);
** if (ray.y < 0)
**     current.y = state->pos.y - map_pos.y;
** else
**     current.y = fabs(state->pos.y - map_pos.y + 1.0);
**
** current x and y are the perpendicular distance to the nearest wall,
** we multiply them by their corresponding delta.
** 0 <= perpendicular distance <= 1 is a ratio, how much of the full delta we need to take.
**
** current.x *= delta.x;
** current.y *= delta.y;
*/

t_vector	get_init_delta(t_state *state, t_vector *ray, t_vector *map_pos, t_vector *delta)
{
	t_vector current;

	current = vector_apply(&fabs, VECTOR_SUB(state->pos, *map_pos));
	if (ray.x > 0)
		current.x += 1.0;
	if (ray.y > 0)
		current.y += 1.0;
	current.x *= delta.x;
	current.y *= delta.y;
	return (current);
}

t_vector	get_map_step(t_vector *ray)
{
	return (vector_new(ray.x < 0 ? -1 : 1,
						ray.y < 0 ? -1 : 1));
}

t_vector	get_perp_dist(t_state *state, t_vector *ray, t_vector *map_pos)
{

}

int			get_line_height(t_state *state, int prep_dist, t_side side)
{
	int	line_height;

	if (perp_wall_dist <= 0)
		line_height = state->window_height;
	else
		line_height = (int)(state->window.height / perp_wall_dist);
	return (line_height);
}

int			get_perp_wall_dist(t_state *state, t_vector *map_pos,
					t_vector *ray, int map_step_x, int map_step_y)
{
	if (side == SIDE_WEST_EAST)
		perp_wall_dist = ((double)map_x - state->pos.x + (map_step_x == -1 ? 1 : 0)) / ray.x;
	else if (side == SIDE_NORTH_SOUTH)
		perp_wall_dist = ((double)map_y - state->pos.y + (map_step_y == -1 ? 1 : 0)) / ray.y;
}

void		helper_ray_next(t_vector *current, t_vector *map_pos,
					t_vector delta, t_vector map_step)
{
	if (current->x < current->y)
	{
		current->x += delta.x;
		map_pos->x += map_step.x;
	}
	else
	{
		current->y += delta.y;
		map_pos->y += map_step.y;
	}
}
