/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_planes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:25:12 by mman              #+#    #+#             */
/*   Updated: 2024/06/30 20:32:57 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



/*
max coordinate is RENDER_DISTANCE/2
min coordinate is -RENDER_DISTANCE/2

The input data are coordinates x,y,z and a vector x,y,z [-1.0,1.0]

If I have a vector normal of a plane, the coordinates of a plane point, and the 
minimum and maximum points of the scene, (each dimension has a min and max),
I can calculate the 4 corners of the plane
and based on this, I can assign the bounds->min and bounds->max of the plane object
where min is left bottom corner and max is right top corner
*/

void cross_product(t_vec v1, t_vec v2, t_vec* result) {
    result->x = v1.y * v2.z - v1.z * v2.y;
    result->y = v1.z * v2.x - v1.x * v2.z;
    result->z = v1.x * v2.y - v1.y * v2.x;
}

void normalize(t_vec* v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    if (length != 0) {
        v->x /= length;
        v->y /= length;
        v->z /= length;
    }
}

void calculate_plane_bounds(t_vec plane_normal, t_vec point, t_object* plane)
{
    // Assume the plane normal is already normalized

    // Generate two orthogonal vectors on the plane
    t_vec up = {0.0f, 1.0f, 0.0f};
    if (fabs(plane_normal.y) > 0.999f) { // if the normal is too close to up vector
        up = (t_vec){1.0f, 0.0f, 0.0f};  // use another vector instead
    }

    t_vec right;
    cross_product(plane_normal, up, &right);
    normalize(&right);

    t_vec forward;
    cross_product(right, plane_normal, &forward);
    normalize(&forward);

    // Define the extent of the plane (arbitrary width and height)
    float width = RENDER_DISTANCE;
    float height = RENDER_DISTANCE;

    // Calculate the corners of the plane
    t_vec half_width_vec = {right.x * width / 2, right.y * width / 2, right.z * width / 2};
    t_vec half_height_vec = {forward.x * height / 2, forward.y * height / 2, forward.z * height / 2};

    plane->bounds.min.x = point.x - half_width_vec.x - half_height_vec.x;
    plane->bounds.min.y = point.y - half_width_vec.y - half_height_vec.y;
    plane->bounds.min.z = point.z - half_width_vec.z - half_height_vec.z;

    plane->bounds.max.x = point.x + half_width_vec.x + half_height_vec.x;
    plane->bounds.max.y = point.y + half_width_vec.y + half_height_vec.y;
    plane->bounds.max.z = point.z + half_width_vec.z + half_height_vec.z;
	// printf("----------- the min bounds are: %lf, %lf, %lf\n", plane->bounds.min.x, plane->bounds.min.y, plane->bounds.min.z);
	// printf("----------- the max bounds are: %lf, %lf, %lf\n", plane->bounds.max.x, plane->bounds.max.y, plane->bounds.max.z);
}