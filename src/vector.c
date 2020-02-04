/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 01:28:01 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/04 02:13:38 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vector	vector_scale(t_vector v, double scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	return (v);
}

/*
** rotate counter clockwise
*/

t_vector	vector_rotate(t_vector v, double angle)
{
	t_vector rotated;

	rotated.x = cos(angle) * v.x - sin(angle) * v.y;
	rotated.y = sin(angle) * v.x + cos(angle) * v.y;
	return (rotated);
}

double		vector_norm(t_vector v)
{
	return (hypot(v.x, v.y));
}

t_vector	vector_new(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}
