/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:26:44 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 19:15:51 by mman             ###   ########.fr       */
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
void    calculate_aabb(t_object	*object, t_aabb	*aabb)
{
	if (object->type == 2)
	{
		// Calculate AABB for sphere
		Sphere* sphere = (Sphere*)object->shape;
		aabb->min.x = sphere->center.x - sphere->radius;
		aabb->min.y = sphere->center.y - sphere->radius;
		aabb->min.z = sphere->center.z - sphere->radius;
		aabb->max.x = sphere->center.x + sphere->radius;
		aabb->max.y = sphere->center.y + sphere->radius;
		aabb->max.z = sphere->center.z + sphere->radius;
	} else if (object->type == 5)
	{
		// Calculate AABB for cylinder
		Cylinder* cylinder = (Cylinder*)object->shape;
		aabb->min.x = cylinder->center.x - cylinder->radius;
		aabb->min.y = cylinder->center.y - cylinder->height / 2;
		aabb->min.z = cylinder->center.z - cylinder->radius;
		aabb->max.x = cylinder->center.x + cylinder->radius;
		aabb->max.y = cylinder->center.y + cylinder->height / 2;
		aabb->max.z = cylinder->center.z + cylinder->radius;
	} else if (object->type == 4) {
		// Calculate AABB for plane
		Plane* plane = (Plane*)object->shape;
		aabb->min.x = plane->point.x;
		aabb->min.y = plane->point.y;
		aabb->min.z = plane->point.z;
		aabb->max.x = plane->point.x;
		aabb->max.y = plane->point.y;
		aabb->max.z = plane->point.z;
	}
}