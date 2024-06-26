/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:10 by mman              #+#    #+#             */
/*   Updated: 2024/06/29 15:34:03 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//casts a SAMPLES_PER_PIXEL rays from each pixel in the viewport -- WIDTH, HEIGHT
//for each ray, check for intersections with objects in the scene
//objects in the scene are stored in a linked list
//scene is a struct that contains the linked list of objects
//scene is divided into BVH tree
void	raycaster(t_scene *scene)
{
	int		i;
	int		j;
	int		temp;

	i = 1;
	temp = 0;
	while (i < WIDTH)
	{
		j = 1;
		while (j < HEIGHT)
		{
			ray(scene, i, j);
			j++;
			temp++;
		}
		i++;
	}
	printf("focal length %f\n", scene->viewport.focal_length);
	ft_pntf("beep boop im a raycaster %i and I finished running\nRAYS CAST: %i", scene, temp);
}

// checks if the ray intersects with any "object" aabb in the bvh of our scene
// if yes, then we calculate the color data for the pixel
void    ray(t_scene *scene, int x, int y)
{
    t_color	rgb;
	t_ray	ray;

	ray.direction.x = x * scene->viewport.pixel_delta_u.x + scene->viewport.upper_left.x + y * scene->viewport.pixel_delta_u.x;
	ray.direction.y = x * scene->viewport.pixel_delta_v.y + scene->viewport.upper_left.y + y * scene->viewport.pixel_delta_u.y;
	ray.direction.z = x * scene->viewport.pixel_delta_u.z + scene->viewport.upper_left.z + y * scene->viewport.pixel_delta_u.z;
	ray.origin = (*scene).viewport.eye_pos;
	rgb = bvh_intersect(scene, &ray);
    ft_process_pixel(&scene->mlx, x, y, rgb);
}

/**
 * Checks if a ray intersects with an axis-aligned bounding box (AABB).
 *
 * @param aabb The AABB to check for intersection.
 * @param ray The ray to check for intersection.
 * @return 1 if the ray intersects with the AABB, 0 otherwise.
 */
int	aabb_intersect(t_aabb aabb, t_ray *ray)
{
	double	tmin;
	double	tmax;
	double	t1;
	double	t2;
	double	t;

	tmin = (aabb.min.x - ray->origin.x) / ray->direction.x;
	tmax = (aabb.max.x - ray->origin.x) / ray->direction.x;
	if (tmin > tmax)
	{
		t = tmin;
		tmin = tmax;
		tmax = t;
	}
	t1 = (aabb.min.y - ray->origin.y) / ray->direction.y;
	t2 = (aabb.max.y - ray->origin.y) / ray->direction.y;
	if (t1 > t2)
	{
		t = t1;
		t1 = t2;
		t2 = t;
	}
	if ((tmin > t2) || (t1 > tmax))
		return (0);
	if (t1 > tmin)
		tmin = t1;
	if (t2 < tmax)
		tmax = t2;
	t1 = (aabb.min.z - ray->origin.z) / ray->direction.z;
	t2 = (aabb.max.z - ray->origin.z) / ray->direction.z;
	if (t1 > t2)
	{
		t = t1;
		t1 = t2;
		t2 = t;
	}
	if ((tmin > t2) || (t1 > tmax))
		return (0);
	if (t1 > tmin)
		tmin = t1;
	if (t2 < tmax)
		tmax = t2;
	return (1);
}

t_color	bvh_intersect(t_scene *scene, t_ray *ray)
{
	t_bvh_node	*node;
	t_color		rgb;

	node = scene->bvh_root; //the entry node of the BVH tree
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	while (node)
	{
		if (aabb_intersect(node->aabb, ray)) //if the ray intersects with aabb with objects
		{
			if (node->isLeaf)
			{
				rgb = color_from_object(node->data); //get the color of the object
				//TBA - Shadow rays
				break ;
			}
			else
			{
				if (aabb_intersect(node->left->aabb, ray)) 
					node = node->left;
				else
					node = node->right;
			}
		}
		else
			node = NULL;
	}
	return (rgb);
}

void	render(t_scene *scene)
{
	ft_pntf("beep boop im a render %i", scene);
	ft_pntf("------------ VIEWPORT CHECK ------------");
	printf("bottom_left %f %f %f\n", scene->viewport.lower_left.x, scene->viewport.lower_left.y, scene->viewport.lower_left.z);
	printf("upper_right %f %f %f\n", scene->viewport.upper_right.x, scene->viewport.upper_right.y, scene->viewport.upper_right.z);
	ft_pntf("----------------------------------------");
    bvh_bounds(scene);
	bvh_tree(scene);
	raycaster(scene);
}