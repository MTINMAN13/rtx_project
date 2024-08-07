/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:33:56 by mman              #+#    #+#             */
/*   Updated: 2024/07/14 23:42:25 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//normalizes a vector to a unit vector
void	vector_oneilizer(t_vec *v)
{
	double length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vec	vector_add(t_vec v1, t_vec v2)
{
	t_vec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec	vector_subtract(t_vec v1, t_vec v2)
{
	t_vec result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec	vector_divide(t_vec v, double scalar)
{
	t_vec result;

	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	return (result);
}

t_vec vector_scale(t_vec v, double t)
{
    return (t_vec){v.x * t, v.y * t, v.z * t};
}

double vec_length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}