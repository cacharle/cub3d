/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:39:57 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/19 17:50:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_state		*create_state(void *mlx_ptr, void *window_ptr, t_parsing *parsing)
{
	t_state *state;

	if ((state = (t_state*)malloc(sizeof(t_state))) == NULL)
		return (NULL);
	state->window_img.id = mlx_new_image(mlx_ptr, parsing->resolution_width, parsing->resolution_height);
	state->window_img.width = parsing->resolution_width;
	state->window_img.height = parsing->resolution_height;
	state->window_img.data = mlx_get_data_addr(state->window_img.id,
			&state->window_img.depth, &state->window_img.size_line, &state->window_img.endian);
	printf("%d\n", state->window_img.width);
	printf("%d\n", state->window_img.height);
	printf("%d\n", state->window_img.depth);
	printf("%d\n", state->window_img.size_line);
	printf("%d\n", state->window_img.endian);

	state->north_texture.id = mlx_xpm_file_to_image(mlx_ptr,
			parsing->north_texture_path, &state->north_texture.width, &state->north_texture.height);
	if (state->north_texture.id == NULL)
		return (NULL);
	state->north_texture.data = mlx_get_data_addr(state->north_texture.id, &state->north_texture.depth,
		   	&state->north_texture.size_line, &state->north_texture.endian);
	/* printf("%d\n", state->north_texture.endian); */
	/* state->south_texture = ; */
	/* state->west_texture = ; */
	/* state->east_texture = ; */

	state->mlx_ptr = mlx_ptr;
	state->window_ptr = window_ptr;
	state->window_width = parsing->resolution_width;
	state->window_height = parsing->resolution_height;
	state->running = TRUE;
	state->pos.x = 1.1;
	state->pos.y = 1.1;
	/* need to be normalized */
	state->dir.x = 1.0;
	state->dir.y = 0.0;
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
	int x;
	t_state *state;
   
	state = param;
	if (!state->running)
	{
		mlx_destroy_window(state->mlx_ptr, state->window_ptr);
		exit(0);
	}
	mlx_clear_window(state->mlx_ptr, state->window_ptr);
	x = -1;
	while (++x < state->window_width)
		draw_column(state, x);
	
	/* for (int i = 0; i < 200000; i++) */
	/* 	state->window_img.data[i] = 127; */
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window_img.id, 0, 0);
	/* mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->north_texture.id, 0, 0); */
	/* for (int i = 0; i < 200; i++) */
	/* 	printf("%d ", state->window_img.data[i]); */
	return (0);
}

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

	int tex_x;

	/* int wall_x = side == SIDE_WEST_EAST ? pos */
	
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
