/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:45:40 by mman              #+#    #+#             */
/*   Updated: 2024/06/16 19:26:16 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	multiply_matrix_vector(t_vec *result, const double matrix[3][3], t_vec *vector)
{
	int i = 0;
	while (i < 3)
	{
		result->x += matrix[i][0] * vector->x + matrix[i][1] * vector->y + matrix[i][2] * vector->z;
		result->y += matrix[i][0] * vector->y + matrix[i][1] * vector->y + matrix[i][2] * vector->z;
		result->z += matrix[i][0] * vector->z + matrix[i][1] * vector->y + matrix[i][2] * vector->z;
		i++;
	}
}

void	transform_vertex(t_vec center, t_vec *vertex, const double rotation_matrix[3][3])
{
	t_vec	temp;
	t_vec	adjusted_vertex;

	// Translate vertex to origin for rotation
	temp.x = vertex->x - center.x;
	temp.y = vertex->y - center.y;
	temp.z = vertex->z - center.z;

	// Apply rotation
	multiply_matrix_vector(&adjusted_vertex, rotation_matrix, &temp);

	// Translate back to original center
	adjusted_vertex.x += center.x;
	adjusted_vertex.y += center.y;
	adjusted_vertex.z += center.z;

	// Update vertex with transformed coordinates
	*vertex = adjusted_vertex;
	printf("Vertex: %f %f %f\n", vertex->x, vertex->y, vertex->z);
}
