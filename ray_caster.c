/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:46:10 by mman              #+#    #+#             */
/*   Updated: 2024/07/17 18:29:42 by mman             ###   ########.fr       */
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
            j += QUALITY;
			// j++;
			temp++;
		}
        i += QUALITY;
		// i++;
	}
	printf("focal length %f\n", scene->viewport.focal_length);
	ft_pntf("beep boop im a raycaster %i and I finished running\nRAYS CAST: %i", scene, temp);
    mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0); // Corrected mlxdata access
    ft_pntf("💎 ------------- RAYCASTER ------------- 💎");
}

t_vec vector_normalize(t_vec vec)
{
    double length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    t_vec normalized_vec;
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;
    normalized_vec.z = vec.z / length;
    return normalized_vec;
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
    ray.normal_unit = vector_normalize(vector_subtract(ray.direction, ray.origin));
    ray.hit_point = vector_add(ray.origin, vector_scale(ray.normal_unit, 20000.0));
    // printf("X        ray from %f %f %f -- : -- ", ray.origin.x, ray.origin.y, ray.origin.z);
    // printf("ray direction %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
    rgb = ray_intersections(scene, &ray);
    printf("closest point is %f %f %f\n", ray.hit_point.x, ray.hit_point.y, ray.hit_point.z);
    ft_process_pixel(&scene->mlx, x, y, rgb);
}

t_color ray_intersections(t_engine *scene, t_ray *ray)
{
    t_color color = create_color(255, 255, 255); // Default color (white) - color of the box
    
    //enter the BVH tree - check if there are any objects
    if (scene->bvh_root != NULL)
    {
        traverse_bvh(scene->bvh_root, ray, &color);
    }
    return (color);
}

static inline double max(double a, double b) {
    return a > b ? a : b;
}

static inline double min(double a, double b) {
    return a < b ? a : b;
}

int ray_intersects_aabb(t_ray *ray, t_aabb *aabb)
{
    double tmin = 0.0;
    double tmax = DBL_MAX;

    for (int d = 0; d < 3; ++d) {
        double invD = 1.0 / ((d == 0) ? ray->normal_unit.x : (d == 1) ? ray->normal_unit.y : ray->normal_unit.z);
        double t0 = (((d == 0) ? aabb->min.x : (d == 1) ? aabb->min.y : aabb->min.z) - 
                     ((d == 0) ? ray->origin.x : (d == 1) ? ray->origin.y : ray->origin.z)) * invD;
        double t1 = (((d == 0) ? aabb->max.x : (d == 1) ? aabb->max.y : aabb->max.z) - 
                     ((d == 0) ? ray->origin.x : (d == 1) ? ray->origin.y : ray->origin.z)) * invD;

        if (invD < 0.0) {
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        tmin = max(t0, tmin);
        tmax = min(t1, tmax);

        if (tmax <= tmin) {
            return 0;
        }
    }
	// printf("found intersection\n");
    return 1;
}

void traverse_bvh(t_bvh_node *node, t_ray *ray, t_color *color)
{
    if (node == NULL)
    {
        // printf("Reached a NULL node, returning.\n");
        return;
    }

    // printf("Traversing node with %d objects, isLeaf: %d\n", node->num_actual_objects, node->isLeaf);
    
    if (node->num_actual_objects > 0)
    {
        if (node->num_actual_objects == 1)
            object_intersects(ray, node->data, color);
        else
        {
			traverse_bvh(node->left, ray, color);
            if (node->right != NULL && ray_intersects_aabb(ray, &node->right->aabb))
                traverse_bvh(node->right, ray, color);
        }
    }
    else
        printf("Node has no objects, skipping.\n");
}


int object_intersects(t_ray *ray, t_object *object, t_color *color)
{
	int hit = 0;
	
	// printf("checking for object type: %d", object->type);
	// printf("| object aaab min %f %f %f", object->aabb.min.x, object->aabb.min.y, object->aabb.min.z);
	// printf("| object aaab max %f %f %f\n", object->aabb.max.x, object->aabb.max.y, object->aabb.max.z);
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

// Updated sphere_intersection function
int sphere_intersection(t_ray *ray, t_object *object, t_color *color)
{
    if (discriminant > 0)
    {
        t_vec hit_point = vector_add(ray->origin, vector_scale(ray->direction, t));

        // Update hit point and color only if this is the closest intersection
        if (vec_length(vector_subtract(hit_point, ray->origin)) < vec_length(vector_subtract(ray->hit_point, ray->origin)))
        {
            ray->hit_point = hit_point;
            *color = object->color;
            printf("Hit point updated to: %f %f %f\n", hit_point.x, hit_point.y, hit_point.z);
            printf("Color updated to: %d %d %d\n", color->r, color->g, color->b);
            return 1;
        }
    }
    return 0;
}

t_vec Intersect(t_vec planeCenter, t_vec planeNormal, t_vec rayP, t_vec rayD) {
    float denominator = vec_dot(rayD, planeNormal);
    // Check if ray is parallel to the plane
    if (fabs(denominator) < 1e-6) {
        return (t_vec){INT_MAX, INT_MAX, INT_MAX}; // Return some form of error or indication that the ray is parallel to the plane
    }
    float d = vec_dot(planeCenter, planeNormal);
    float t = -(d + vec_dot(rayP, planeNormal)) / denominator;
    // Optionally, check if t is negative
    if (t < 0) {
        return (t_vec){INT_MAX, INT_MAX, INT_MAX}; // Return some form of error or indication that the intersection is behind the ray origin
    }
    t_vec t_vec = vector_scale(rayD, t);
    return (vector_add(rayP, t_vec));
}

int plane_intersection(t_ray *ray, t_object *object, t_color *color)
{
    // Extract plane data
    t_vec plane_normal = object->normal;
    t_vec plane_point = object->coordinates; // A point on the plane
    t_vec intersection = Intersect(plane_point, plane_normal, ray->origin, ray->direction);
    if (intersection.x == INT_MAX && intersection.y == INT_MAX && intersection.z == INT_MAX) {
        return 0;
    }
    else {
        double distance = vec_length(vector_subtract(intersection, ray->origin));
        double current_distance = vec_length(vector_subtract(ray->hit_point, ray->origin));
        if (distance < current_distance) {
            ray->hit_point = intersection;
            *color = color_from_object(object);
            // printf("hit a plane at %f %f %f and returning the color %d %d %d\n", intersection.x, intersection.y, intersection.z, color->r, color->g, color->b);
        }
        return 1;
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






































/**
 * Calculates the dot product of two vectors.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The dot product of v1 and v2.
 */
double vec_dot(t_vec v1, t_vec v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

t_vec vec_cross(t_vec v1, t_vec v2)
{
    return (t_vec){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}
