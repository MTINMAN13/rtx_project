/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:26:44 by mman              #+#    #+#             */
/*   Updated: 2024/06/30 19:25:26 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Sets the minimum and maximum bounds of the scene to infinity and -infinity respectively
static void	initialize_bounds(t_scene **scene)
{
	(*scene)->bounds->min.y = INFINITY;
	(*scene)->bounds->min.y = INFINITY;
	(*scene)->bounds->min.z = INFINITY;
	(*scene)->bounds->max.x = -INFINITY;
	(*scene)->bounds->max.y = -INFINITY;
	(*scene)->bounds->max.z = -INFINITY;
}

double	ft_fmin(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	ft_fmax(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}

//Bounding Volume Hierarchy -- the box that surrounds all objects in the scene
//axis-aligned bounding box (AABB)
//Takes in the Camera Viewport
//Takes in the Object Data
//Creates the Root Node of the BVH Tree -- the AABB which surrounds all objects in the scene
void bvh_bounds(t_scene *scene)
{
    int i = 0;
    t_object *current_object;

    ft_pntf("beep boop im a bvh_bounds %i", scene);
    scene->bounds = malloc(sizeof(t_aabb));
    if (!scene->bounds)
        return; // Handle allocation failure

    initialize_bounds(&scene);

    // Ensure we start from the head of the list
    current_object = scene->objects;
    while (current_object && current_object->prev)
        current_object = current_object->prev;

    while (i < scene->total_objects && current_object)
    {
        scene->bounds->min.x = ft_fmin(scene->bounds->min.x, current_object->bounds.min.x);
        scene->bounds->min.y = ft_fmin(scene->bounds->min.y, current_object->bounds.min.y);
        scene->bounds->min.z = ft_fmin(scene->bounds->min.z, current_object->bounds.min.z);
        scene->bounds->max.x = ft_fmax(scene->bounds->max.x, current_object->bounds.max.x);
        scene->bounds->max.y = ft_fmax(scene->bounds->max.y, current_object->bounds.max.y);
        scene->bounds->max.z = ft_fmax(scene->bounds->max.z, current_object->bounds.max.z);
        printf("this is the bounds.min %f\n", current_object->bounds.min.x);
        i++;
        current_object = current_object->next;
    }

    // Reset to the head of the list
    current_object = scene->objects;
    while (current_object && current_object->prev)
        current_object = current_object->prev;

    printf("\nthis should be the first object %s\n", current_object ? current_object->raw_data : "NULL");

    // PART TWO -- CREATE THE ROOT NODE OF THE BVH TREE by ALIGNING THE BOUNDS TO THE SCENE (viewport)(camera)
    // Multiply the bounds' corner points by the view matrix.
    // This will align the bounds to the scene.
    // Calculate the corners of the root BVH node

    printf("----------- the min bounds are: %lf, %lf, %lf\n", scene->bounds->min.x, scene->bounds->min.y, scene->bounds->min.z);
    printf("----------- the max bounds are: %lf, %lf, %lf\n", scene->bounds->max.x, scene->bounds->max.y, scene->bounds->max.z);
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