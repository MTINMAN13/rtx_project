/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:10 by mman              #+#    #+#             */
/*   Updated: 2024/07/14 19:52:35 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//casts a SAMPLES_PER_PIXEL rays from each pixel in the viewport -- WIDTH, HEIGHT
//for each ray, check for intersections with objects in the scene
//objects in the scene are stored in a linked list
//scene is a struct that contains the linked list of objects
//scene is divided into BVH tree
void	raycaster(t_engine *scene)
{
	int		i;
	int		j;
	int		temp;

	i = 1;
	temp = 0;
    ft_pntf("💎 ------------- RAYCASTER ------------- 💎");
	while (i <= WIDTH)
	{
		j = 1;
		while (j <= HEIGHT)
		{
			ray(scene, i, j);
            j += 100;
			// j++;
			temp++;
		}
        i += 100;
		// i++;
	}
	printf("focal length %f\n", scene->viewport.focal_length);
	ft_pntf("beep boop im a raycaster %i and I finished running\nRAYS CAST: %i", scene, temp);
    mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0); // Corrected mlxdata access
    ft_pntf("💎 ------------- RAYCASTER ------------- 💎");
}

// checks if the ray intersects with any "object" aabb in the bvh of our scene
// if yes, then we calculate the color data for the pixel
void    ray(t_engine *scene, int x, int y)
{
    t_color	rgb;
	t_ray	ray;

	ray.direction.x = x * scene->viewport.pixel_delta_u.x + scene->viewport.upper_left.x + y * scene->viewport.pixel_delta_u.x;
	ray.direction.y = x * scene->viewport.pixel_delta_v.y + scene->viewport.upper_left.y + y * scene->viewport.pixel_delta_u.y;
	ray.direction.z = x * scene->viewport.pixel_delta_u.z + scene->viewport.upper_left.z + y * scene->viewport.pixel_delta_u.z;
	ray.origin = (*scene).viewport.eye_pos;
    ray.normal_unit = vector_subtract(ray.direction,ray.origin);
    // printf("X        ray from %f %f %f -- : -- ", ray.origin.x, ray.origin.y, ray.origin.z);
    // printf("ray direction %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	rgb = ray_intersections(scene, &ray);
    ft_process_pixel(&scene->mlx, x, y, rgb);
}

t_color ray_intersections(t_engine *scene, t_ray *ray)
{
    t_color color = create_color(255, 255, 255); // Default color (white) - color of the box
    
    //enter the BVH tree - check if there are any objects
    if (scene->bvh_root != NULL)
    {
        ft_pntf("BVH root not null");
        color = traverse_bvh(scene->bvh_root, ray);
    }
    return (color);
}

t_color traverse_bvh(t_bvh_node *node, t_ray *ray)
{
	t_color color = create_color(255, 200, 255); // Default color (white)

    //are there any objects in the node?
    printf("Node Has %d objects\n", node->num_aabbs_inside);
    //traverse left   -- and  -- traverse right

    //does it intersect left
    //does it intersect right

    //if yes, is it the leaf? are there any object in the node?
    if (node->isLeaf)
    {
        // Check intersection with the actual objects in the leaf node
        t_object *object = node->data;
        while (object != NULL)
        {
            t_color temp_color;
            if (object_intersects(ray, object, &temp_color))
            {
                printf("Object hit\n");
                return(object->color);
            }
            object = object->next;
        }
    }
    // else
    // {
    //     // Recursively check left and right children
    //     t_color left_color = traverse_bvh(node->left, ray);
    //     t_color right_color = traverse_bvh(node->right, ray);

    //     // Determine which color to return. For now, just return left if left hits something, otherwise right.
    //     if (!is_color_default(left_color))
    //     {
    //         color = left_color;
    //     }
    //     else if (!is_color_default(right_color))
    //     {
    //         color = right_color;
    //     }
    // }
    return color;
}

int object_intersects(t_ray *ray, t_object *object, t_color *color)
{
	int hit = 0;
	
    // printf("Object type: %d\n", object->type);
	switch (object->type)
	{
		case 2: // Sphere
			hit = sphere_intersection(ray, object, color);
			break;
		case 3: // Plane
			hit = plane_intersection(ray, object, color);
			break;
		case 4: // Square
			hit = square_intersection(ray, object, color);
			break;
		case 5: // Cylinder
			hit = cylinder_intersection(ray, object, color);
			break;
		default:
			break;
	}

	return hit;
}

int sphere_intersection(t_ray *ray, t_object *object, t_color *color)
{
    t_vec oc = vector_subtract(ray->origin, object->coordinates);
    double a = vec_dot(ray->direction, ray->direction);
    double b = 2.0 * vec_dot(oc, ray->direction);
    double c = vec_dot(oc, oc) - (object->diameter * object->diameter / 4.0);
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        double root1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (root1 > 0 || root2 > 0)
        {
            *color = color_from_object(object);
            return 1;
        }
    }
    return 0;
}

int plane_intersection(t_ray *ray, t_object *object, t_color *color)
{
    double denom = vec_dot(object->normal, ray->direction);
    if (denom != 0)
    {
        double t = vec_dot(vector_subtract(object->coordinates, ray->origin), object->normal) / denom;
        if (t >= 0)
        {
            *color = color_from_object(object);
            return 1;
        }
    }
    return 0;
}

int square_intersection(t_ray *ray, t_object *object, t_color *color)
{
    if (plane_intersection(ray, object, color))
    {
        t_vec p = vector_add(ray->origin, vector_divide(ray->direction, object->height));
        t_vec v1 = vector_subtract(object->coordinates, object->normal);
        t_vec v2 = vector_add(object->coordinates, object->normal);
        t_vec v3 = vector_add(v2, vector_subtract(v1, object->coordinates));
        t_vec v4 = vector_add(v1, vector_subtract(v2, object->coordinates));
        if (vec_dot(vec_cross(vector_subtract(p, v1), vector_subtract(v2, v1)), object->normal) >= 0 &&
            vec_dot(vec_cross(vector_subtract(p, v2), vector_subtract(v3, v2)), object->normal) >= 0 &&
            vec_dot(vec_cross(vector_subtract(p, v3), vector_subtract(v4, v3)), object->normal) >= 0 &&
            vec_dot(vec_cross(vector_subtract(p, v4), vector_subtract(v1, v4)), object->normal) >= 0)
        {
            *color = color_from_object(object);
            return 1;
        }
    }
    return 0;
}


int cylinder_intersection(t_ray *ray, t_object *object, t_color *color)
{
    t_vec oc = vector_subtract(ray->origin, object->coordinates);
    double a = vec_dot(ray->direction, ray->direction) - pow(vec_dot(ray->direction, object->normal), 2);
    double b = 2.0 * (vec_dot(oc, ray->direction) - vec_dot(oc, object->normal) * vec_dot(ray->direction, object->normal));
    double c = vec_dot(oc, oc) - pow(vec_dot(oc, object->normal), 2) - pow(object->diameter / 2.0, 2);
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        double root1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if ((root1 >= 0 && root1 <= object->height) || (root2 >= 0 && root2 <= object->height))
        {
            *color = color_from_object(object);
            return 1;
        }
    }
    return 0;
}




int is_color_default(t_color color)
{
    return (color.r == 0 && color.g == 0 && color.b == 0);
}


t_color create_color(float r, float g, float b)
{
    t_color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

void	render(t_engine *scene)
{
	ft_pntf("beep boop im a render %i", scene);
	ft_pntf("------------ VIEWPORT CHECK ------------");
	printf("bottom_left %f %f %f\n", scene->viewport.lower_left.x, scene->viewport.lower_left.y, scene->viewport.lower_left.z);
	printf("upper_right %f %f %f\n", scene->viewport.upper_right.x, scene->viewport.upper_right.y, scene->viewport.upper_right.z);
	ft_pntf("----------------------------------------");
    bvh_bounds(scene);
	// printf("------------ OBJECT CJHECK ------------");
	// printf("\nobject 1 %f %f %f\n", scene->objects->coordinates.x, scene->objects->coordinates.y, scene->objects->coordinates.z);
	bvh_tree(scene);
	raycaster(scene);
    print_bvh_tree(scene);
}

void print_bvh_nodes(t_bvh_node *node)
{
    if (node != NULL)
    {
        printf("BVH Node: %p\n", node);
        printf("Bounding Box: (%f, %f, %f) - (%f, %f, %f)\n", node->aabb.min.x, node->aabb.min.y, node->aabb.min.z, node->aabb.max.x, node->aabb.max.y, node->aabb.max.z);
        printf("Number of AABBS inside: %d\n", node->num_aabbs_inside);
        printf("Is Leaf: %s\n", node->isLeaf ? "Yes ✅" : "No ❌");
        printf("Numbers of Objects inside: %i\n", node->num_actual_objects);
        if (node->isLeaf)
        {
            t_object *object = node->data;
            while (object != NULL)
            {
                printf("Object Type: %d\n", object->type);
                object = object->next;
            }
        }
        printf("\n");

        print_bvh_nodes(node->left);
        print_bvh_nodes(node->right);
    }
}

void print_bvh_tree(t_engine *scene)
{
    printf("BVH Tree:\n");
    print_bvh_nodes(scene->bvh_root);
    printf("object types : 1 - camera, 2 - sphere, 3 - plane, 4 - square, 5 - cylinder\n");
}






































double vec_dot(t_vec v1, t_vec v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

t_vec vec_cross(t_vec v1, t_vec v2)
{
    return (t_vec){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}
