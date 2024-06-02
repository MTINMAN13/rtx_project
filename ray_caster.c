/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:10 by mman              #+#    #+#             */
/*   Updated: 2024/06/02 23:44:02 by mman             ###   ########.fr       */
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

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ray(scene, i, j);
			j++;
		}
		i++;
	}
	printf("focal length %f\n", scene->viewport.focal_length);
	ft_pntf("beep boop im a raycaster %i and I finished running", scene);
}

// checks if the ray intersects with any "object" aabb in the bvh of our scene
// if yes, then we calculate the color data for the pixel
void    ray(t_scene *scene, int x, int y)
{
    t_color	rgb;
	t_ray	ray;

	ray.direction.x = x;
	ray.direction.y = y;
	ray.direction.z = 0;
	ray.origin = (*scene).viewport.eye_pos;
    ft_process_pixel(&scene->mlx, x, y, rgb);
}

void	render(t_scene *scene)
{
	ft_pntf("beep boop im a render %i", scene);
	printf("I think the viewport will be initialized with the coordinates: %f,%f,%f and  %f,%f,%f\n", scene->viewport.bottom_left.x, scene->viewport.bottom_left.y, scene->viewport.bottom_left.z, scene->viewport.upper_right.x, scene->viewport.upper_right.y, scene->viewport.upper_right.z);
	printf("the eye is located at TBD\n");
    bvh_bounds(scene);
	bvh_tree(scene);
	raycaster(scene);
}