/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 02:35:05 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 23:20:37 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	vector_sub(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

static int		sprite_compar(const void *a, const void *b)
{
	const t_sprite	*sprite_a;
	const t_sprite	*sprite_b;

	sprite_a = a;
	sprite_b = b;
	if (sprite_a->dist > sprite_b->dist)
		return (-1);
	if (sprite_a->dist < sprite_b->dist)
		return (1);
	return (0);
}

static void		sprites_dist(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->sprites_num)
		state->sprites[i].dist =
			vector_norm(vector_sub(state->sprites[i].pos, state->pos));
}

void			sprite_sort(t_state *state)
{
	sprites_dist(state);
	ft_qsort(state->sprites, state->sprites_num,
				sizeof(t_sprite), sprite_compar);
}
