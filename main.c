/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:39 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/19 17:09:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Error");
		return (1);
	}
	t_parsing *p = parse(argv[1]);
	if (p == NULL)
		return (1);
	/* printf("R %d %d\n", p->resolution_width, p->resolution_height); */
	/* printf("NO %s\n", p->north_texture_path); */
	/* printf("SO %s\n", p->south_texture_path); */
	/* printf("WE %s\n", p->west_texture_path); */
	/* printf("EA %s\n\n", p->east_texture_path); */
	/* printf("S %s\n", p->sprite_texture_path); */
	/* printf("F %d,%d,%d\n", p->floor_color.r, p->floor_color.g, p->floor_color.b); */
	/* printf("C %d,%d,%d\n\n", p->ceilling_color.r, p->ceilling_color.g, p->ceilling_color.b); */

	/* printf("%dx%d\n", p->map_height, p->map_width); */
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

	void *mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (1);
	void *window_ptr = mlx_new_window(mlx_ptr, p->resolution_width, p->resolution_height, WINDOW_TITLE);
	if (window_ptr == NULL)
		return (1);

	t_state *state = create_state(mlx_ptr, window_ptr, p);
	if (state == NULL)
		return (1);

	/* for (int i = 0; i < 20; i++) */
	/* draw_column(state, i); */

	mlx_key_hook(window_ptr, handle_key, (void*)state);
	mlx_loop_hook(mlx_ptr, graphics_update, (void*)state);
	mlx_loop(mlx_ptr);

	return (0);
}
