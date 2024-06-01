/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:10:04 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 18:52:52 by mman             ###   ########.fr       */
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
