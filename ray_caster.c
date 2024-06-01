/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:10 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 20:51:41 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//calculates the ray direction vector
//takes in the camera structure, the x and y coordinates of the pixel
//returns the ray direction vector -- normalized
//
//
//returns ray_direction_normalized_vector
t_vec   ray_direction(t_viewport *camera, int x, int y)
{
    t_vec   ray;
    double  aspect_ratio;
    double  half_fov_rad;
    double  tangent_h;
    double  normalized_x;
    double  normalized_y;
    double  x_offset;
    double  y_offset;

    // Calculate aspect ratio
    aspect_ratio = (double)WIDTH / (double)HEIGHT;

    // Convert FOV to radians and calculate scaling factor
    half_fov_rad = camera->fov * M_PI / 180 / 2.0;
    tangent_h = tan(half_fov_rad);

    // Normalize pixel coordinates
    normalized_x = (2.0 * x / (WIDTH - 1)) - 1.0;
    normalized_y = (2.0 * y / (HEIGHT - 1)) - 1.0;

    // Calculate X and Y offsets with aspect ratio
    x_offset = normalized_x * aspect_ratio * tangent_h;
    y_offset = normalized_y * tangent_h;

    // Optional normalization (uncomment if desired)
    double magnitude = sqrt(x_offset * x_offset + y_offset * y_offset + 1.0);
    x_offset /= magnitude;
    y_offset /= magnitude;

    // Set ray direction (z-component typically set based on focal length)
    ft_vectorize(&ray, x_offset, y_offset, -camera->focal_length); // Assuming negative focal length

    printf("ray direction %f,%f,%f\n", ray.x, ray.y, ray.z);
    return (ray);
}

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
			//cast ray from pixel i,j
			//check for intersections with objects in the scene
			//if intersection, calculate color
			//store color in image buffer
			ray_direction(&scene->viewport, i, j);
			j++;
		}
		i++;
	}
	printf("focal length %f\n", scene->viewport.focal_length);
	ft_pntf("beep boop im a raycaster %i and I finished running", scene);
}

void	render(t_scene *scene)
{
	ft_pntf("beep boop im a render %i", scene);
	printf("I think the viewport will be initialized with the coordinates: %f,%f,%f and  %f,%f,%f\n", scene->viewport.bottom_left.x, scene->viewport.bottom_left.y, scene->viewport.bottom_left.z, scene->viewport.upper_right.x, scene->viewport.upper_right.y, scene->viewport.upper_right.z);
	bvh_bounds(scene);
	bvh_tree(scene);
	raycaster(scene);
}