/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/16 10:06:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WINDOW_MID_HEIGHT(state) (state->window.height / 2)

int		render_update(void *param)
{
	t_state *state;

	state = param;
	if (!state->running)
	{
		state_destroy(state);
		exit(EXIT_SUCCESS);
	}
	render_update_window(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window.id, 0, 0);
	return (0);
}

void	render_update_window(t_state *state)
{
	int x;

	x = -1;
	while (++x < state->window.width)
	{
	/* x = state->window.width / 2 + 1; */
		/* printf("\nx %d\n", x); */
		render_column(state, x);
	}
}

void	render_column(t_state *state, int x)
{
	t_render_state	rstate;

	rstate.x = x;
	/* printf("1\n"); */
	rstate_ray(state, &rstate);
	/* printf("ray [%f %f]\n", rstate.ray.x, rstate.ray.y); */
	rstate.map_pos = vector_new((double)((int)state->pos.x), (double)((int)state->pos.y)); //floor?
	/* printf("map_pos [%f %f]\n", rstate.map_pos.x, rstate.map_pos.y); */
	rstate_delta(&rstate);
	/* printf("delta [%f %f]\n", rstate.delta.x, rstate.delta.y); */
	rstate_init_probe(state, &rstate);
	/* printf("probe [%f %f]\n", rstate.probe.x, rstate.probe.y); */
	rstate.map_step = vector_new(rstate.ray.x < 0.0 ? -1.0 : 1.0, rstate.ray.y < 0.0 ? -1.0 : 1.0);
	/* printf("map_step [%f %f]\n", rstate.map_step.x, rstate.map_step.y); */
	while (TRUE)
	{
		rstate.side = rstate.probe.x < rstate.probe.y ? SIDE_WE : SIDE_WE;
		/* printf("side %s\n", rstate.side == SIDE_WE ? "side we" : "side ns"); */
		rstate_next_probe(&rstate);
		/* printf("2\n"); */
		/* printf("> [%d %d]\n", (int)rstate.map_pos.x, (int)rstate.map_pos.y); */
		if (state->map[(int)rstate.map_pos.y][(int)rstate.map_pos.x] == CELL_WALL)
			break ;
		/* printf("3\n"); */
	}
		/* printf("[%d %d]\n", (int)rstate.map_pos.x, (int)rstate.map_pos.y); */
	rstate_line_height(state, &rstate);
	/* printf("perp dist %f\n", rstate_perp_dist(state, &rstate)); */
	printf("line height %d\n", rstate.line_height);
	rstate.draw_start = WINDOW_MID_HEIGHT(state) - rstate.line_height / 2;
	rstate.draw_end = WINDOW_MID_HEIGHT(state) + rstate.line_height / 2;
	printf("%d -> %d\n", rstate.draw_start, rstate.draw_end);
	render_window_column(state, &rstate);
}

void	render_window_column(t_state *state, t_render_state *rstate)
{
	int		i;
	t_color	white;
	t_color black;

	white.hexcode = 0x00ffffff;
	black.hexcode = 0x00000000;
	i = -1;
	while (++i < rstate->draw_start)
		((t_color*)state->window.data)[i * state->window.width + rstate->x] = black;
	while (++i < rstate->draw_end)
		((t_color*)state->window.data)[i * state->window.width + rstate->x] = white;
	while (++i < state->window_height)
		((t_color*)state->window.data)[i * state->window.width + rstate->x] = black;

	/* printf("%d -> %d\n", rstate->draw_start, rstate->draw_end); */
	/* while (++i < rstate->draw_start) */
	/* 	((t_color*)state->window.data)[i * state->window.width + rstate->x] = */
	/* 		state->ceilling_color; */
	/* i = rstate->draw_end; */
	/* i = render_texture(state, rstate); */
	/* while (++i < state->window_height) */
	/* 	((t_color*)state->window.data)[i * state->window.width + rstate->x] = */
	/* 		state->floor_color; */
}

/* int		render_texture(t_state *state, t_render_state *rstate)) */
/* { */
	/* int i; */
	/* int tex_x; */
	/* double step; */
	/* double tex_pos; */
	/* int tex_y; */
	/* t_image *texture; */
    /*  */
	/* texture = get_tex(state, side); */
	/* tex_x = get_tex_x(); */
    /*  */
	/* step = 1.0 * texture->height / line_height; */
	/* texPos = (start - state->window.height / 2 + line_height / 2) * step; */
    /*  */
	/* i = start - 1; */
	/* while (++i < end) */
	/* { */
	/* 	tex_y = (int)tex_pos & (texture->height - 1); */
	/* 	tex_pos += step; */
	/* 	((t_color*)state->window.data)[i * state->window.width + x] = */
	/* 		texture[texHeight * texY + texX]; */
	/* } */
	/* return (end); */
/* } */
