/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:10:04 by mman              #+#    #+#             */
/*   Updated: 2024/06/23 21:46:17 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//takes in the vector structure, assigns values from string
//string is converted into a double and assigned to the vector
//string is in the format "x,y,z"
void	ft_assign_values_to_t_vec(t_vec *vec, char *str)
{
	char	**token;
	char	*copy = ft_strdup(str); // Make a copy of the string to avoid modifying the original

	// Parse the string using strtok
	token = ft_split(copy, ',');
	vec->x = ft_atoidouble(token[0]);
	vec->y = ft_atoidouble(token[1]);
	vec->z = ft_atoidouble(token[2]);
	// Free the memory allocated by ft_split
	free(copy);
	free(token);
}

//Takes in the vector structure and assigns three doubles to it
void	ft_vectorize(t_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

//takes in the color structure, assigns values from string
void	ft_assign_values_to_t_color(t_color *color, char *str)
{
	char	**token;
	char	*copy = ft_strdup(str); // Make a copy of the string to avoid modifying the original

	// Parse the string using strtok
	token = ft_split(copy, ',');
	color->r = ft_atoi(token[0]);
	color->g = ft_atoi(token[1]);
	color->b = ft_atoi(token[2]);
	// Free the memory allocated by ft_split
	free(copy);
	free(token);
}

// Function to calculate change in coordinates per unit distance
t_vec	change_per_unit_distance(t_vec p1, t_vec p2)
{
	t_vec delta;

	// Calculate differences in coordinates
	double deltaX = p2.x - p1.x;
	double deltaY = p2.y - p1.y;
	double deltaZ = p2.z - p1.z;

	// Calculate Euclidean distance
	double distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
	printf("distance: %f\n", distance);

	// Ensure distance is not zero to avoid division by zero
	if (distance == 0)
	{
		delta.x = 0;
		delta.y = 0;
		delta.z = 0;
	}
	else
	{
		// Calculate change per unit distance
		delta.x = deltaX / distance * -1;
		delta.y = deltaY / distance * -1;
		delta.z = deltaZ / distance * -1;
	}
	printf("length of delta: %f\n", sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z));
	return delta;
}