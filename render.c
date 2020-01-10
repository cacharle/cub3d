#include "cub3d.h"

int render_update(void *param)
{
	int x;
	t_state *state;

	state = param;
	if (!state->running)
	{
		state_destroy(state);
		exit(0);
	}
	mlx_clear_window(state->mlx_ptr, state->window_ptr);
	x = -1;
	while (++x < state->window_width)
		render_column(state, x);

	/* for (int i = 0; i < 200000; i++) */
	/* 	state->window_img.data[i] = 127; */
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window_img.id, 0, 0);
	/* mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->north_texture.id, 0, 0); */
	/* for (int i = 0; i < 200; i++) */
	/* 	printf("%d ", state->window_img.data[i]); */
	return (0);
}

void render_column(t_state *state, int x)
{
	/*
	 * -1        0         1
	 *  v        v         v
	 *  ####################
	 *  #        |         #
	 *  #        |         #
	 *  #        |         #
	 *  #        |         #
	 *  #        |         #
	 *  ####################
	 */
	double camera_x = 2 * x / (double)state->window_width - 1;

	/* camera plane length related to current column */
	t_vector ray;
	ray = vector_add(state->dir, vector_scale(state->plane, camera_x));
	/* ray.x = state->dir.x + state->plane.x * camera_x; */
	/* ray.y = state->dir.y + state->plane.y * camera_x; */
	/* printf("[%f %f]\n", ray.x, ray.y); */

	/* map pos*/
	int map_x = (int)state->pos.x;
	int map_y = (int)state->pos.y;

	/* dist to first encountered wall */
	double side_dist_x;
	double side_dist_y;

	/* delta between grid lines from ray percepective */
	double delta_dist_x = sqrt(1 + (SQUARE(ray.y) / SQUARE(ray.x))); //fabs(1.0 / ray.x);
	double delta_dist_y = sqrt(1 + (SQUARE(ray.x) / SQUARE(ray.y))); //hfabs(1.0 / ray.y);

	/* dist to wall (perpendicular to avoid fisheye effect) */
	double perp_wall_dist;

	/* step on size for the `map_. +=` */
	int map_step_x = ray.x < 0 ? -1 : 1;
	int map_step_y = ray.y < 0 ? -1 : 1;

	side_dist_x = ray.x < 0 ? state->pos.x - map_x : map_x + 1.0 - state->pos.x;
	side_dist_x *= delta_dist_x;
	side_dist_y = ray.y < 0 ? state->pos.y - map_y : map_y + 1.0 - state->pos.y;
	side_dist_y *= delta_dist_y;

	t_side side;
	while (TRUE)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x; /* increment real dist */
			map_x += map_step_x;         /* increment map dist */
			side = SIDE_WEST_EAST;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += map_step_y;
			side = SIDE_NORTH_SOUTH;
		}
		if (state->map[map_y][map_x] == CELL_WALL)
			break;
	}
	if (side == SIDE_WEST_EAST)
		perp_wall_dist = ((double)map_x - state->pos.x + (map_step_x == -1 ? 1 : 0)) / ray.x;
	else //if (side == SIDE_NORTH_SOUTH)
		perp_wall_dist = ((double)map_y - state->pos.y + (map_step_y == -1 ? 1 : 0)) / ray.y;
	/* perp_wall_dist = sqrt(SQUARE(state->pos.x - side_dist_x) + SQUARE(state->pos.y - side_dist_y)); */

	int line_height;
	/* if (perp_wall_dist <= 0) */
	/* 	line_height = state->window_height; */
	/* else */
		line_height = (int)(state->window_height / perp_wall_dist);
	/* printf("%f\n", perp_wall_dist); */
	/* printf("%d\n", line_height); */
	int draw_start = state->window_height / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end =  state->window_height / 2 + line_height / 2;
	if (draw_end >= state->window_height)
		draw_end = state->window_height - 1;

	/* int tex_x; */
	/* int wall_x = side == SIDE_WEST_EAST ? pos */
	/* t_vector unit_ray = vector_scale(ray, 1.0 / vector_norm(ray)); */
	/* t_vector dist_v = vector_scale(unit_ray, side == SIDE_WEST_EAST ? side_dist_y : side_dist_x); */
	/* printf("[%f %f]\n", dist_v.x, dist_v.y); */
	/* #<{(| printf("[%f %f]\n", dist_v.x, dist_v.y); |)}># */
    /*  */
	/* double mod = side == SIDE_WEST_EAST ? dist_v.y : dist_v.x; */
	/* mod = fabs(mod); */
	/* mod -= floor(mod); */


	/* tex_x = (int)map_range(side == SIDE_WEST_EAST ? dist_v.y : dist_v.x, 0, 1, 0, state->north_texture.width); */
	/* tex_x = side = SIDE_WEST_EAST ? side_dist_y : side_dist_x) */
	/* printf("%d\n", tex_x); */

	/* double wall_x; */
	/* if (side == SIDE_WEST_EAST) */
	/* 	wall_x = pos_y + prep_wall_dist * ray.y; */
	/* else */
	/* 	wall_x = pos_x + prep_wall_dist * ray.x; */
	/* wall_x -= floor(wall_x); */

	int i;
	i = 0;
	t_color white;
	white.hexcode = 0x00ffffff;
	while (i < draw_start)
		((t_color*)state->window_img.data)[i++ * state->window_img.width + x] = state->ceilling_color;
	while (i < draw_end)
		((t_color*)state->window_img.data)[i++ * state->window_img.width + x] = white;
	while (i < state->window_height)
		((t_color*)state->window_img.data)[i++ * state->window_img.width + x] = state->floor_color;
}

/* double map_range(double x, double src_lo, double src_hi, double dest_lo, double dest_hi) */
/* { */
/* 	double src_len = src_hi - src_lo; */
/* 	double dest_len = dest_hi - dest_lo; */
/* 	return ((x - src_lo) / src_len) * dest_len + dest_lo; */
/* } */
