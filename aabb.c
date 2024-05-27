/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:26:44 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 19:31:24 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Bounding Volume Hierarchy -- the box that surrounds all objects in the scene
//axis-aligned bounding box (AABB)
//scans objects in the scene
//calculates the bounds of the scene
void    bvh_bounds(t_scene *scene)
{
	// int i = 0;
	// // Scan through the objects in the scene
	// while (i < scene->objects_count)
	// {
	//     // Calculate the bounds of each object
	//     // ...
		
	//     i++;
	// }

	// Calculate the bounds of the lights in the scene
	// ...

	ft_pntf("beep boop im a bvh bounds %i", scene);
}

// 0 = camera, 1 = light, 2 = sphere, 3 = plane, 4 = square, 5 = cylinder, 6 = triangle
void	calculate_aabb(t_object	*object, t_aabb	*aabb)
{
	if (object->type == 2)
	{
		// Calculate AABB for sphere or cylinder
		aabb->min.x = object->coordinates.x - object->diameter;
		aabb->min.y = object->coordinates.y - object->diameter;
		aabb->min.z = object->coordinates.z - object->diameter;
		aabb->max.x = object->coordinates.x + object->diameter;
		aabb->max.y = object->coordinates.y + object->diameter;
		aabb->max.z = object->coordinates.z + object->diameter;
	} 
	else if (object->type == 5)
	{
		// Calculate AABB for cylinder
		aabb->min.x = object->coordinates.x - object->diameter;
		aabb->min.y = object->coordinates.y - object->diameter / 2;
		aabb->min.z = object->coordinates.z - object->diameter;
		aabb->max.x = object->coordinates.x + object->diameter;
		aabb->max.y = object->coordinates.y + object->diameter / 2;
		aabb->max.z = object->coordinates.z + object->diameter;
	} 
	else if (object->type == 4)
	{
		// Calculate AABB for plane
		aabb->min.x = object->coordinates.x;
		aabb->min.y = object->coordinates.y;
		aabb->min.z = object->coordinates.z;
		aabb->max.x = object->coordinates.x;
		aabb->max.y = object->coordinates.y;
		aabb->max.z = object->coordinates.z;
	}
	ft_pntf("beep boop object calculated %i (object type)", object->type);
}