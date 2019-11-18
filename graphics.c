#include "cub3d.h"

t_state		*create_state(void *mlx_ptr, void *window_ptr, t_parsing *parsing)
{
	t_state *state;

	if ((state = (t_state*)malloc(sizeof(t_state))) == NULL)
		return (NULL);
	state->mlx_ptr = mlx_ptr;
	state->window_ptr = window_ptr;
	state->window_width = parsing->resolution_width;
	state->window_height = parsing->resolution_height;
	state->running = TRUE;
	state->pos.x = 1.0;
	state->pos.y = 1.0;
	state->dir.x = 1.0;
	state->dir.y = 1.0;
	state->plane.x = 0.0;
	state->plane.y = 0.66;
	state->map = parsing->map;
	state->map_width = parsing->map_width;
	state->map_height = parsing->map_height;
	state->ceilling_color = parsing->ceilling_color;
	state->floor_color = parsing->floor_color;
	return (state);
}

int graphics_update(void *param)
{
	t_state *state = param;
	if (!state->running)
	{
		mlx_destroy_window(state->mlx_ptr, state->window_ptr);
		exit(0);
	}
	/* int color = 0x00FFFFFF; */
	/* int x = state->pos.x; */
	/* int y = state->pos.y; */
	/* for (int i = 0; i < 4; i++) */
	/* for (int j = 0; j < 4; j++) */
	/* mlx_pixel_put(state->mlx_ptr, state->window_ptr, x + i - 2,y + j - 2, 0x00ffffff); */

	/* int x2 = state->dir.x; */
	/* int y2 = state->dir.y; */
	/* for (int i = 0; i < 4; i++) */
	/* for (int j = 0; j < 4; j++) */
	/* mlx_pixel_put(state->mlx_ptr, state->window_ptr, x + x2 + i - 2,y + y2 + j - 2, 0x00ffff00); */

	mlx_clear_window(state->mlx_ptr, state->window_ptr);
	int x;

	x = -1;
	while (++x < state->window_width)
		draw_column(state, x);
	
	return (0);
}

typedef enum
{
	SIDE_NORTH_SOUTH,
	SIDE_WEST_EAST
}	t_side;

void draw_column(t_state *state, int x)
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
		perp_wall_dist = (map_x - state->pos.x + (1 - map_step_x) / 2) / ray.x;
	else //if (side == SIDE_NORTH_SOUTH)
		perp_wall_dist = (map_y - state->pos.y + (1 - map_step_y) / 2) / ray.y;

	int line_height = (int)(state->window_height / perp_wall_dist);
	int draw_start = state->window_height / 2 - line_height / 2;
	/* if (draw_start < 0) */
	/* 	draw_start = 0; */
	int draw_end =  state->window_height / 2 + line_height / 2;
	/* if (draw_end >= state->window_height) */
	/* 	draw_end = state->window_height - 1; */

	/* for (int i = 0; i < draw_start; i++) */
	/* 	mlx_pixel_put(state->mlx_ptr, state->window_ptr, x, i, state->ceilling_color.hexcode); */
	for (int i = draw_start; i < draw_end; i++)
		mlx_pixel_put(state->mlx_ptr, state->window_ptr, x, i, 0x00ffffff);
	/* for (int i = draw_end; i < state->window_height; i++) */
	/* 	mlx_pixel_put(state->mlx_ptr, state->window_ptr, x, i, state->floor_color.hexcode); */
}
