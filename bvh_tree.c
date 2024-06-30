/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:39:58 by mman              #+#    #+#             */
/*   Updated: 2024/06/30 18:22:18 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//Bounding Volume Hierarchy -- the box that surrounds all objects in the scene
//axis-aligned bounding boxes (AABB)
//stuff from scene->objects is to be stored in a BVH tree
//
//cylinder
//sphere
//plane

void bvh_tree(t_scene *scene)
{
    t_object *object_list = scene->objects;
    printf("\n\n\n--------------------------\n");
    // Build the BVH tree and assign it to the scene's root
    printf("So there should be %i objects in the scene. [Longest Axis is %i]\n\n\n\n\n\n\n\n\n", scene->total_objects, ft_longest_axis(*(scene->bounds)));
    sort_object_list(&object_list, ft_longest_axis(*(scene->bounds)));
    printf("Number of objects in list: %d\n", count_objects(object_list));
    build_bvh_tree(scene, &scene->bvh_root, object_list, *(scene->bounds));
    printf("\n\n\n\n\n\n📦 Total of %i AABBs in the BVH tree\n", count_aabbs_in_bvh(scene->bvh_root));
    printf("BVH tree created - %p\n\n\n", scene);
}

void    build_bvh_tree(t_scene *scene, t_bvh_node **current_bvh_node, t_object *object_list, t_aabb bounds)
{
    // Base case: if the object list is empty, set the bvh root to NULL
    if (object_list == NULL)
    {
        *current_bvh_node = malloc(sizeof(t_bvh_node));
        if (*current_bvh_node == NULL)
        {
            perror("Failed to allocate memory for leaf node");
            exit(EXIT_FAILURE);
        }
        (*current_bvh_node)->left = NULL;
        (*current_bvh_node)->right = NULL;
        (*current_bvh_node)->data = NULL;
        (*current_bvh_node)->isLeaf = 1;
        (*current_bvh_node)->num_objects = 0;
        (*current_bvh_node)->aabb = bounds;
        return;
    }
    else if (object_list->next == NULL)
    {
        *current_bvh_node = malloc(sizeof(t_bvh_node));
        if (*current_bvh_node == NULL)
        {
            perror("Failed to allocate memory for leaf node");
            exit(EXIT_FAILURE);
        }
        (*current_bvh_node)->left = NULL;
        (*current_bvh_node)->right = NULL;
        (*current_bvh_node)->data = object_list;
        (*current_bvh_node)->isLeaf = 1;
        (*current_bvh_node)->num_objects = 1;
        (*current_bvh_node)->aabb = object_list->bounds;
        printf("Create one leaf node with the bounds of the object. [OBJECT TYPE: %i]\n", object_list->type);
        return;
    }
    else
    {
        //Here we found a BVH node with more than one object
        //We need to split the object list into two halves
        t_object *left_list = malloc(sizeof(t_object));
        t_object *right_list = malloc(sizeof(t_object));
        printf("🔔 - %p, %p, %p", left_list, right_list, scene);
        // Perform the split and update the object lists
        sort_object_list(&object_list, ft_longest_axis(bounds));
        split_object_list(object_list, &left_list, &right_list);
        // Recursively build the BVH tree for the left and right lists
        build_bvh_tree(scene, &((*current_bvh_node)->left), left_list, calculate_list_bbox(left_list));
        build_bvh_tree(scene, &((*current_bvh_node)->right), right_list, calculate_list_bbox(right_list));
        // Update the AABB of the current BVH node
        (*current_bvh_node)->aabb = encompassing_bbox(calculate_list_bbox(left_list), calculate_list_bbox(right_list));
        // Update the number of objects in the current BVH node
        (*current_bvh_node)->num_objects = count_aabbs_in_bvh(*current_bvh_node);
        // Set the current BVH node as an internal node
        (*current_bvh_node)->isLeaf = 0;
        printf("Create one BVH node, which is not leaf");
    }
}







/**
 * Swaps the positions of two objects in the object list.
 *
 * @param object1 Pointer to the first object.
 * @param object2 Pointer to the second object.
 */
void swap_objects(t_object *a, t_object *b)
{
    t_object temp = *a;
    *a = *b;
    *b = temp;
}

double get_coordinate(t_vec vec, int axis) {
    if (axis == 0) return vec.x;
    if (axis == 1) return vec.y;
    if (axis == 2) return vec.z;
    return 0; // Default case (should not happen if axis is valid)
}

/**
 * Partitions the object list based on a pivot element and an axis.
 * 
 * @param object_list The list of objects to be partitioned.
 * @param pivot The index of the pivot element.
 * @param axis The axis along which the partitioning is performed.
 * @return The updated pivot index.
 */
int partition(t_object *object_list, int pivot, int axis) {
    t_object *pivot_object = object_list;
    for (int i = 0; i < pivot; i++) {
        pivot_object = pivot_object->next;
    }

    // Move the pivot object to the end of the list
    swap_objects(pivot_object, object_list);

    // Partition the list
    t_object *current = object_list;
    t_object *smaller = NULL;
    t_object *larger = NULL;
    while (current != NULL) {
        t_object *next = current->next;
        double current_center = get_coordinate(current->coordinates, axis);
        double pivot_center = get_coordinate(object_list->coordinates, axis); // Pivot object now at the start
        if (current_center <= pivot_center) {
            // Add the object to the smaller list
            current->next = smaller;
            smaller = current;
        } else {
            // Add the object to the larger list
            current->next = larger;
            larger = current;
        }
        current = next;
    }

    // Combine the smaller and larger lists
    if (smaller != NULL) {
        object_list = smaller;
        while (smaller->next != NULL) {
            smaller = smaller->next;
        }
        smaller->next = object_list; // object_list is now the pivot object
    } else {
        object_list = object_list; // Pivot object remains at the start
    }
    object_list->next = larger;

    // Return the updated pivot index
    int pivot_index = 0;
    current = object_list;
    while (current != object_list) {
        pivot_index++;
        current = current->next;
    }
    return pivot_index;
}

void sort_object_list(t_object **object_list, int axis)
{
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxnumber of objects in list: %d\n", count_objects(*object_list));
    // Base case: If the object list is empty or has only one object, no sorting is needed
    if (*object_list == NULL || (*object_list)->next == NULL) {
        return;
    }
    
    // Initialize the sorted list with the first object
    t_object *sorted_list = *object_list;
    *object_list = (*object_list)->next;
    sorted_list->next = NULL;
    
    // Traverse the remaining objects in the object list
    while (*object_list != NULL) {
        // Store the next object in a temporary variable
        t_object *temp = *object_list;
        *object_list = (*object_list)->next;
        
        // Find the correct position to insert the object in the sorted list
        t_object *current = sorted_list;
        t_object *previous = NULL;
        double object_coordinate = get_coordinate(temp->coordinates, axis);
        double current_coordinate = get_coordinate(current->coordinates, axis);
        while (current != NULL && object_coordinate > current_coordinate) {
            previous = current;
            current = current->next;
            if (current != NULL) {
                current_coordinate = get_coordinate(current->coordinates, axis);
            }
        }
        
        // Insert the object into the sorted list
        if (previous == NULL) {
            // Insert at the beginning of the sorted list
            temp->next = sorted_list;
            sorted_list = temp;
        } else {
            // Insert in the middle or at the end of the sorted list
            previous->next = temp;
            temp->next = current;
        }
    }
    
    // Update the object list with the sorted list
    *object_list = sorted_list;

    // Print the number of objects in the list
    int count = count_objects(*object_list);
    printf("Number of objects in the list: %d\n", count);
}

int count_objects(t_object *object_list)
{
    int count = 0;
    t_object *current = object_list;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void split_object_list(t_object *object_list, t_object **left_list, t_object **right_list)
{
    // Initialize the left and right lists
    *left_list = object_list;
    *right_list = object_list->next;
    object_list->next = NULL;

    (*left_list)->next = NULL;
    (*right_list)->prev = NULL;
    // Print the number of objects in each list
    printf("Number of objects in left list: %d\n", count_objects(*left_list));
    printf("Number of objects in right list: %d\n", count_objects(*right_list));
}










// 0 is X-axis, 1 is Y-axis, 2 is Z-axis
int ft_longest_axis(t_aabb bbox)
{
	double x_length = bbox.max.x - bbox.min.x;
	double y_length = bbox.max.y - bbox.min.y;
	double z_length = bbox.max.z - bbox.min.z;
	
    printf("[0 is X-axis, 1 is Y-axis, 2 is Z-axis]\n");
	if (x_length >= y_length && x_length >= z_length) {
		return 0; // X-axis is the longest axis
	} else if (y_length >= x_length && y_length >= z_length) {
		return 1; // Y-axis is the longest axis
	} else {
		return 2; // Z-axis is the longest axis
	}
}



int count_aabbs_in_bvh(t_bvh_node *node)
{
    // Base case: If the node is NULL, there are no AABBs
    if (node == NULL) {
        return 0;
    }
    // Leaf node case: If the node is a leaf, it represents one AABB
    if (node->isLeaf) {
        return 1;
    }
    // Internal node case: Count AABBs in both subtrees and add 1 for the current node's AABB
    int left_count = count_aabbs_in_bvh(node->left);
    int right_count = count_aabbs_in_bvh(node->right);
    return left_count + right_count + 1; // Add 1 for the current node's AABB
}

t_aabb encompassing_bbox(t_aabb bbox1, t_aabb bbox2)
{
    t_aabb encompassing;
    encompassing.min.x = fmin(bbox1.min.x, bbox2.min.x);
    encompassing.min.y = fmin(bbox1.min.y, bbox2.min.y);
    encompassing.min.z = fmin(bbox1.min.z, bbox2.min.z);
    encompassing.max.x = fmax(bbox1.max.x, bbox2.max.x);
    encompassing.max.y = fmax(bbox1.max.y, bbox2.max.y);
    encompassing.max.z = fmax(bbox1.max.z, bbox2.max.z);
    return encompassing;
}


/**
 * Calculates the bounding box of a list of objects.
 *
 * @param object_list The list of objects.
 * @return The bounding box of the object list.
 */
t_aabb calculate_list_bbox(t_object *object_list)
{
    t_aabb bbox;
    bbox.min = (t_vec){INFINITY, INFINITY, INFINITY};
    bbox.max = (t_vec){-INFINITY, -INFINITY, -INFINITY};
    
    t_object *current = object_list;
    while (current != NULL) {
        t_aabb object_bbox = current->bounds;
        bbox.min.x = fmin(bbox.min.x, object_bbox.min.x);
        bbox.min.y = fmin(bbox.min.y, object_bbox.min.y);
        bbox.min.z = fmin(bbox.min.z, object_bbox.min.z);
        
        bbox.max.x = fmax(bbox.max.x, object_bbox.max.x);
        bbox.max.y = fmax(bbox.max.y, object_bbox.max.y);
        bbox.max.z = fmax(bbox.max.z, object_bbox.max.z);
        
        current = current->next;
    }
    printf("The min bounds are: %lf, %lf, %lf\n", bbox.min.x, bbox.min.y, bbox.min.z);
    printf("The max bounds are: %lf, %lf, %lf\n", bbox.max.x, bbox.max.y, bbox.max.z);
    return bbox;
}


void	free_bvh_tree(t_scene *scene)
{
	ft_pntf("bvh fully freed - %i", scene);
}
