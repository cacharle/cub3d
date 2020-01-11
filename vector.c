/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 01:28:01 by cacharle          #+#    #+#             */
/*   Updated: 2020/01/12 14:39:34 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define VECTOR_MINUS(v) vector_scale(v, -1.0)
#define VECTOR_SUB(v, w) vector_add(v, VECTOR_MINUS(w))
#define VECTOR_ADD_CONST(v, c) vector_add(v, vector_new(c, c))

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
	return (sqrt(SQUARE(v.x) + SQUARE(v.y)));
}

t_vector	vector_new(double x, double y)
{
	t_vector	v;
	
	v.x = x;
	v.y = y;
	return (v);
}

t_vector	vector_apply(t_vector v, double (*f)(double))
{
	v.x = f(v.x);
	v.y = f(v.y);
	return (v);
}
