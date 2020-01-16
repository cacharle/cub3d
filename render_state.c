/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:40:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/16 10:03:01 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	rstate_ray(t_state *state, t_render_state *rstate)
{
	double camera_x;

	camera_x = 2 * rstate->x / (double)state->window.width - 1;
	rstate->ray = vector_add(state->dir, vector_scale(state->plane, camera_x));
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

void	rstate_delta(t_render_state *rstate)
{
	rstate->delta.x = vector_norm(rstate->ray) / rstate->ray.x;
	rstate->delta.y = vector_norm(rstate->ray) / rstate->ray.y;
}

/*
** first delta between player position and first grid unit
**
** current x and y are the perpendicular distance to the nearest wall,
** we multiply them by their corresponding delta.
** 0 <= perpendicular distance <= 1 is a ratio, how much of the full delta we need to take.
**
** if (rstate->ray.x < 0)
**     rstate->probe.x = state->pos.x - rstate->map_pos.x;
** else
**     rstate->probe.x = fabs(state->pos.x - rstate->map_pos.x + 1.0);
** if (rstate->ray.y < 0)
**     rstate->probe.y = state->pos.y - rstate->map_pos.y;
** else
**     rstate->probe.y = fabs(state->pos.y - rstate->map_pos.y + 1.0);
** rstate->probe.x *= rstate->delta.x;
** rstate->probe.y *= rstate->delta.y;
*/

void	rstate_init_probe(t_state *state, t_render_state *rstate)
{
	rstate->probe = VECTOR_SUB(state->pos, rstate->map_pos);
	if (rstate->ray.x > 0)
		rstate->probe.x += 1.0;
	if (rstate->ray.y > 0)
		rstate->probe.y += 1.0;
	rstate->probe.x *= rstate->delta.x;
	rstate->probe.y *= rstate->delta.y;
}

/*
** Move the probe to it's next iteration by advancing to the nearest square unit
** in the x or y direction.
** This advance is represented both with the
** player/ray percpective and the map pecpective.
*/

void	rstate_next_probe(t_render_state *rstate)
{
	if (rstate->probe.x < rstate->probe.y)
	{
		rstate->probe.x += rstate->delta.x;
		rstate->map_pos.x += rstate->map_step.x;
	}
	else
	{
		rstate->probe.y += rstate->delta.y;
		rstate->map_pos.y += rstate->map_step.y;
	}
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
** We use the y component because we hit the wall
** from a south/north percepective,
** if we had hit it form west/east, we would use the x component instead.
*/

double	rstate_perp_dist(t_state *state, t_render_state *rstate)
{
	if (rstate->side == SIDE_NS)
		return ((rstate->map_pos.x - state->pos.x + (1.0 - rstate->map_step.x) / 2.0) / rstate->ray.x); // fait des trucs bizzare
		/* return (rstate->map_pos.y - state->pos.y + state->dir.y); */
	else if (rstate->side == SIDE_WE)
		return ((rstate->map_pos.y - state->pos.y + (1.0 - rstate->map_step.y) / 2.0) / rstate->ray.y);
		/* return (rstate->map_pos.x - state->pos.x + state->dir.x); */
	return (1.0);
}

/*
** 0 <= 1 / perp_dist <= 1
** height * (1 / perp_dist) is how much of the screen height do we take
*/

void	rstate_line_height(t_state *state, t_render_state *rstate)
{
	rstate->line_height =
		(int)((double)state->window.height / rstate_perp_dist(state, rstate));
}

t_image	*get_tex(t_state *state, t_render_state *rstate)
{
	if (rstate->side == SIDE_NS)
	{
		if (rstate->probe.y < state->pos.y)
			return (state->textures + TEX_NORTH);
		else
			return (state->textures + TEX_SOUTH);
	}
	else if (rstate->side == SIDE_WE)
	{
		if (rstate->probe.x < state->pos.x)
			return (state->textures + TEX_WEST);
		else
			return (state->textures + TEX_EAST);
	}
	return (NULL);
}

/*
** Since we're drawing each column, all the texels we want to draw on the window
** are on a single column of the texture.
** First we find the x-coord relative to the wall we hit
*/

/* int			get_tex_x() */
/* { */
/* 	//calculate value of wall_x */
/* 	double wall_x; //where exactly the wall was hit */
/* 	if (side == 0) wall_x = state->pos.y + perp_dist * ray.y; */
/* 	else           wall_x = state->pos.x + perp_dist * ray.x; */
/* 	wall_x -= floor(wall_x); */
/* 	//x coordinate on the texture */
/* 	int tex_x = (int)(wall_x * (double)texWidth); */
/* 	if(side == 0 && ray.x > 0) tex_x = texture_width - tex_x - 1; */
/* 	if(side == 1 && ray.y < 0) tex_x = texture_width - tex_x - 1; */
/* 	return (tex_x); */
/* } */
