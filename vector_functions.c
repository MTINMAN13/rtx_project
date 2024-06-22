/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:33:56 by mman              #+#    #+#             */
/*   Updated: 2024/06/22 21:21:25 by mman             ###   ########.fr       */
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
