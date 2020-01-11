/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:39 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 10:09:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_state		*state;

	/* if (argc == 3 && ft_strcmp(argv[2], "--save") == 0) */
	/* 	return (save_image()); */
	/*else*/
	if (argc != 2)
		error_put_usage_exit(argv[0]);
	if ((state = state_new(parse(argv[1]))) == NULL)
	{
		ft_putendl_fd("Error: state creation", STDERR_FILENO);
		return (1);
	}
	mlx_hook(state->window_ptr, 2, (1L << 1), event_keydown, (void*)state);
	mlx_loop_hook(state->mlx_ptr, render_update, (void*)state);
	mlx_loop(state->mlx_ptr);
	return (0);
}

/*
int main(int argc, char argv)
{
	t_parsing *p = parse(argv[1]);
	if (p == NULL)
		return (1);
	printf("R %d %d\n", p->resolution_width, p->resolution_height);
	printf("NO %s\n", p->north_texture_path);
	printf("SO %s\n", p->south_texture_path);
	printf("WE %s\n", p->west_texture_path);
	printf("EA %s\n\n", p->east_texture_path);
	printf("S %s\n", p->sprite_texture_path);
	printf("F %d,%d,%d\n", p->floor_color.r, p->floor_color.g, p->floor_color.b);
	printf("C %d,%d,%d\n\n", p->ceilling_color.r, p->ceilling_color.g, p->ceilling_color.b);

	printf("%dx%d\n", p->map_height, p->map_width);
	for (int i = 0; i < p->map_height; i++)
	{
		for (int j = 0; j < p->map_width; j++)
		{
			if (p->map[i][j] == CELL_WALL)
				printf("#");
			else if (p->map[i][j] == CELL_EMPTY)
				printf(" ");
			else
				printf("%d", p->map[i][j]);
			if (j != p->map_width - 1)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}
*/
