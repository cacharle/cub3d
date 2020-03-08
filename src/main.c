/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:39:39 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/05 00:14:18 by cacharle         ###   ########.fr       */
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
	mlx_hook(state->window_ptr, 17L, 0, event_quit, (void*)state);
	mlx_key_hook(state->window_ptr, event_keydown, (void*)state);
	mlx_loop_hook(state->mlx_ptr, render_update, (void*)state);
	mlx_loop(state->mlx_ptr);
	return (0);
}
