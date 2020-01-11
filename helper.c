/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 07:32:20 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/11 11:22:15 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	helper_is_player_cell(t_cell cell)
{
	return (cell == CELL_LOOK_NORTH || cell == CELL_LOOK_SOUTH ||
			cell == CELL_LOOK_WEST || cell == CELL_LOOK_EAST);
}

void	helper_free_splited(char **splited)
{
	int	i;

	if (splited == NULL)
		return ;
	i = -1;
	while (splited[++i] != NULL)
		free(splited[i]);
	free(splited);
}
