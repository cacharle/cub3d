/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:37:17 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/15 15:09:32 by cacharle         ###   ########.fr       */
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
		render_column(state, x);
}

void	render_column(t_state *state, int x)
{
	t_render_state	rstate;

	rstate.x = x;
	rstate_ray(state, &rstate);
	vector_new((double)((int)state->pos.x), (double)((int)state->pos.y));
	rstate_delta(&rstate);
	rstate_init_probe(state, &rstate);
	vector_new(rstate.ray.x < 0.0 ? -1.0 : 1.0, rstate.ray.y < 0.0 ? -1.0 : 1.0);
	while (TRUE)
	{
		rstate.side = rstate.probe.x < rstate.probe.y ? SIDE_WE : SIDE_WE;
		rstate_next_probe(&rstate);
		if (state->map[(int)rstate.map_pos.y][(int)rstate.map_pos.x] == CELL_WALL)
			break ;
	}
	rstate_line_height(state, &rstate);
	render_window_column(state, &rstate);
	// WINDOW_MID_HEIGHT(state) - line_height / 2
	// WINDOW_MID_HEIGHT(state) + line_height / 2
}

void	render_window_column(t_state *state, t_render_state *rstate)
{
	int		i;
	t_color	white;

	white.hexcode = 0x00ffffff;
	i = -1;
	/* while (++i < draw_start) */
	/* 	((t_color*)state->window.data)[i * state->window.width + rstate->x] = */
	/* 		state->ceilling_color; */
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
