/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:39 by cacharle          #+#    #+#             */
/*   Updated: 2019/11/15 09:26:16 by cacharle         ###   ########.fr       */
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
	printf("R %d %d\n", p->resolution_width, p->resolution_height);
	printf("NO %s\n", p->north_texture_path);
	printf("SO %s\n", p->south_texture_path);
	printf("WE %s\n", p->west_texture_path);
	printf("EA %s\n\n", p->east_texture_path);
	printf("S %s\n", p->sprite_texture_path);
	printf("F %d,%d,%d\n", p->floor_color.r, p->floor_color.g, p->floor_color.b);
	printf("C %d,%d,%d\n\n", p->ceilling_color.r, p->ceilling_color.g, p->ceilling_color.b);

	/* printf("%dx%d\n", p->map_height, p->map_width); */
	for (int i = 0; i < p->map_height; i++)
	{
		for (int j = 0; j < p->map_width; j++)
		{
			printf("%d", p->map[i][j]);
			if (j != p->map_width - 1)
				printf(" ");
		}
		printf("\n");
	}
	/* void *mlx_ptr = mlx_init(); */
	/* void *mlx_window = mlx_new_window(mlx_ptr, 640, 480, "bonjour"); */
	/* mlx_key_hook(mlx_window, handle_key, NULL); */
	/* mlx_loop(mlx_ptr); */
	/* mlx_destroy_window(mlx_ptr, mlx_window); */


	return (0);
}
