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
** if we have a vector v = [2 3]:
** dx = |v| / v_1
**    = sqrt(v_1^2 + v_2^2) / v_1
**    = (v_1^2 + v_2^2) / v_1^2
**    = 1 + v_2^2 / v_1^2
** Same thing for dy
** dy = |v| / v_2
**    = sqrt(v_1^2 + v_2^2) / v_1
**    = (v_1^2 + v_2^2) / v_2^2
**    = v_1^2 / v_2^2 + 1
**
** This can be simplified (for some obscure reason):
** dx = |1 / v_1|
** dy = |1 / v_2|
*/

t_vector	get_delta(t_vector ray)
{
	t_vector delta;

	delta.x = vector_norm(ray) / ray.x;
	delta.y = vector_norm(ray) / ray.y;
	return (delta);
}

/*
** first delta between player position and first grid unit
**
** current x and y are the perpendicular distance to the nearest wall,
** we multiply them by their corresponding delta.
** 0 <= perpendicular distance <= 1 is a ratio, how much of the full delta we need to take.
**
** if (ray.x < 0)
**     current.x = state->pos.x - map_pos.x;
** else
**     current.x = fabs(state->pos.x - map_pos.x + 1.0);
** if (ray.y < 0)
**     current.y = state->pos.y - map_pos.y;
** else
**     current.y = fabs(state->pos.y - map_pos.y + 1.0);
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

/*
** perpendicular distance between the wall hit and the camera plane.
** We don't use euclidean distance because it would cause a fisheye effect.
**
** ====================X========== wall
**         |          /|
**         | <------ / | -----+
**         |        /  |      |
**   plane |       /   | <- perpendicular distance
**    |    |      /    |
**    v    |     /     |
** <-------^----/----------------- camera plane
**         |   /
**  dir -> |  /
**         | / <- euclidean distance
**         |/
**         x <- pos
**
** In this case the perpendicular distance (p) is the difference
** of the y-coord of the hit point and the y-coord of the pos + dir vector.
** We use the y component because we hit the wall from a south/north percepective,
** if we had hit it form west/east, we would use the x component instead.
*/

double		get_perp_dist(t_state *state, t_vector *hit_point, t_side side)
{
	if (side == SIDE_NS)
		return hit_point->y - state->pos.y + state->dir.y);
	else if (side == SIDE_NS)
		return hit_point->x - state->pos.x + state->dir.x);
}

/*
** 0 <= 1 / perp_dist <= 1
** height * (1 / perp_dist) is how much of the screen height do we take
*/

int			get_line_height(t_state *state, double prep_dist, t_side side)
{
	return ((int)((double)state->window.height / perp_wall_dist));
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

t_image		*get_tex(t_state *state, t_side side)
{
	if (side == SIDE_NS)
	{
		if (hit_point->y < state->pos.y)
			return (state->textures[TEX_NORTH]);
		else
			return (state->textures[TEX_SOUTH]);
	}
	else if (side == SIDE_WE)
	{
		if (hit_point->x < state->pos.x)
			return (state->textures[TEX_WEST]);
		else
			return (state->textures[TEX_EAST]);
	}
	return (NULL);
}

/*
** Since we're drawing each column, all the texels we want to draw on the window
** are on a single column of the texture.
** First we find the x-coord relative to the wall we hit
*/

int			get_tex_x()
{
	//calculate value of wall_x
	double wall_x; //where exactly the wall was hit
	if (side == 0) wall_x = state->pos.y + perp_dist * ray.y;
	else           wall_x = state->pos.x + perp_dist * ray.x;
	wall_x -= floor(wall_x);
	//x coordinate on the texture
	int tex_x = (int)(wall_x * (double)texWidth);
	if(side == 0 && ray.x > 0) tex_x = texture_width - tex_x - 1;
	if(side == 1 && ray.y < 0) tex_x = texture_width - tex_x - 1;
	return (tex_x);
}
