/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:39 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/02 19:22:09 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_state		*state;

	if (argc != 2 && !(argc == 3 && ft_strcmp(argv[2], "--save") == 0))
		error_put_usage_exit(argv[0]);
	if ((state = state_new(parse_check(parse(argv[1])))) == NULL)
		return (1);
	if (argc == 3)
		return (capture(state));
	mlx_hook(state->window_ptr, 2, (1L << 1), event_keydown, (void*)state);
	mlx_hook(state->window_ptr, 17L, 0, event_quit, (void*)state);
	mlx_loop_hook(state->mlx_ptr, render_update, (void*)state);
	mlx_loop(state->mlx_ptr);
	return (0);
}


/* int main(int argc, char **argv) */
/* { */
/* 	(void)argc; */
/* 	t_state *s = parse_check(parse(argv[1])); */
/* 	if (s == NULL) */
/* 		return (1); */
/* 	printf("R %d %d\n", s->window.width, s->window.height); */
/* 	printf("NO %s\n", s->textures_path[TEX_NORTH]); */
/* 	printf("SO %s\n", s->textures_path[TEX_SOUTH]); */
/* 	printf("WE %s\n", s->textures_path[TEX_WEST]); */
/* 	printf("EA %s\n\n", s->textures_path[TEX_EAST]); */
/* 	printf("S %s\n", s->textures_path[TEX_SPRITE]); */
/* 	printf("F %d,%d,%d\n", s->floor_color.rgb.r, s->floor_color.rgb.g, s->floor_color.rgb.b); */
/* 	printf("C %d,%d,%d\n\n", s->ceilling_color.rgb.r, s->ceilling_color.rgb.g, s->ceilling_color.rgb.b); */
/* 	printf("%dx%d\n", s->map_height, s->map_width); */
/* 	for (int i = 0; i < s->map_height; i++) */
/* 	{ */
/* 		for (int j = 0; j < s->map_width; j++) */
/* 		{ */
/* 			if (s->map[i][j] == CELL_WALL) */
/* 				printf("#"); */
/* 			else if (s->map[i][j] == CELL_EMPTY) */
/* 				printf(" "); */
/* 			else */
/* 				printf("%d", s->map[i][j]); */
/* 			if (j != s->map_width - 1) */
/* 				printf(" "); */
/* 		} */
/* 		printf("\n"); */
/* 	} */
/* 	printf("post state_new\n"); */
/* 	if ((s = state_new(s)) == NULL) */
/* 	{ */
/* 		printf("Error: state new"); */
/* 		return 1; */
/* 	} */
/* 	printf("state->pos [%f %f]\n", s->pos.x, s->pos.y); */
/* 	state_destroy(s); */
/* 	return 0; */
/* } */
