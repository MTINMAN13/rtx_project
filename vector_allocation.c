/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:10:04 by mman              #+#    #+#             */
/*   Updated: 2024/05/26 14:14:18 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//takes in the vector structure, assigns values from string
//string is converted into a double and assigned to the vector
//string is in the format "x,y,z"
void ft_assign_values_to_t_vec(t_vec *vec, char *str)
{
    char    **token;
    char    *copy = ft_strdup(str); // Make a copy of the string to avoid modifying the original

    // Parse the string using strtok
    token = ft_split(copy, ',');
    vec->x = ft_atoidouble(token[0]);
    vec->y = ft_atoidouble(token[1]);
    vec->z = ft_atoidouble(token[2]);
    // Free the memory allocated by ft_split
    free(copy);
    free(token);
}