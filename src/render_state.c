/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:40:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 18:30:10 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** ray:
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
**
** delta:
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
**
** init probe:
** first delta between player position and first grid unit
**
** current x and y are the perpendicular distance to the nearest wall,
** we multiply them by their corresponding delta.
** 0 <= perpendicular distance <= 1 is a ratio,
**  how much of the full delta we need to take.
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

void	rstate_init(t_state *state, t_render_state *rstate, int x)
{
	double camera_x;

	rstate->x = x;
	camera_x = 2.0 * (double)rstate->x / (double)state->window.width - 1.0;
	rstate->ray = vector_add(state->dir, vector_scale(state->plane, camera_x));
	rstate->map_pos = vector_new((int)state->pos.x, (int)state->pos.y);
	rstate->delta.x = fabs(1 / rstate->ray.x);
	rstate->delta.y = fabs(1 / rstate->ray.y);
	if (rstate->ray.x < 0)
		rstate->probe.x = (state->pos.x - rstate->map_pos.x) * rstate->delta.x;
	else
		rstate->probe.x = (rstate->map_pos.x + 1.0 - state->pos.x)
							* rstate->delta.x;
	if (rstate->ray.y < 0)
		rstate->probe.y = (state->pos.y - rstate->map_pos.y)
							* rstate->delta.y;
	else
		rstate->probe.y = (rstate->map_pos.y + 1.0 - state->pos.y)
							* rstate->delta.y;
	rstate->map_step = vector_new(rstate->ray.x < 0.0 ? -1.0 : 1.0,
									rstate->ray.y < 0.0 ? -1.0 : 1.0);
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
/*
** 0 <= 1 / perp_dist <= 1
** height * (1 / perp_dist) is how much of the screen height do we take
*/

void	rstate_post(t_state *state, t_render_state *rstate)
{
	if (rstate->side == SIDE_WE)
		rstate->perp_dist = (rstate->map_pos.x - state->pos.x
				+ (1 - rstate->map_step.x) / 2) / rstate->ray.x;
	else
		rstate->perp_dist = (rstate->map_pos.y - state->pos.y
				+ (1 - rstate->map_step.y) / 2) / rstate->ray.y;
	rstate->line_height = (int)((double)state->window.height /
							rstate->perp_dist);
	rstate->draw_start = state->window.height / 2 - rstate->line_height / 2;
	rstate->draw_end = state->window.height / 2 + rstate->line_height / 2;
	if (rstate->draw_start < 0)
		rstate->draw_start = 0;
	if (rstate->draw_end > state->window.height - 1)
		rstate->draw_end = state->window.height - 1;
	state->z_buffer[rstate->x] = rstate->perp_dist;
}
