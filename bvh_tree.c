/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:39:58 by mman              #+#    #+#             */
/*   Updated: 2024/06/29 18:13:30 by mman             ###   ########.fr       */
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

// Assuming these functions are defined elsewhere

/**
 * Swaps the positions of two objects in the object list.
 *
 * @param object1 Pointer to the first object.
 * @param object2 Pointer to the second object.
 */
void swap_objects(t_object *a, t_object *b) {
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



t_object *sort_object_list(t_object *object_list, int axis) {
    // Base case: if the object list is empty or contains only one object, return the list
    if (object_list == NULL || object_list->next == NULL)
	{
		printf("object_list is NULL\n");
	    return object_list;
	}

    // Choose a pivot element
    int pivot = 0;
    t_object *current = object_list;
    while (current->next != NULL) {
        current = current->next;
        pivot++;
    }

    // Partition the list based on the pivot element
    int pivot_index = partition(object_list, pivot, axis);

    // Recursively sort the left and right halves of the list
    t_object *left_list = object_list;
    t_object *right_list = object_list;
	int i = 0;
	t_object *temp = right_list;
	while (temp != NULL) {
		i++;
		temp = temp->next;
	}
	printf("📙📙 Number of objects found: %d\n", i);
    left_list = sort_object_list(left_list, axis);
    right_list = sort_object_list(right_list->next, axis);

    // Combine the sorted left and right halves
    object_list = left_list;
    while (left_list->next != NULL) {
        left_list = left_list->next;
    }
    left_list->next = right_list;

    return object_list;
}


void split_object_list(t_object *object_list, int axis, t_object **left_list, t_object **right_list) {
    // Initialize the left and right lists
    *left_list = NULL;
    *right_list = NULL;

    // Calculate the midpoint along the given axis
    double midpoint = 0.0;
    int num_objects = 0;
    t_object *current = object_list;
    while (current != NULL) {
        midpoint += get_coordinate(current->coordinates, axis);
        num_objects++;
        current = current->next;
    }
    midpoint /= num_objects;

    // Split the object list based on the midpoint
    current = object_list;
    while (current != NULL)
	{
        printf("current type is %i\n", current->type);
		t_object *next = current->next;
        double current_center = get_coordinate(current->coordinates, axis);
        if (current_center <= midpoint) {
            // Add the object to the left list
            current->next = *left_list;
            *left_list = current;
        } else {
            // Add the object to the right list
            current->next = *right_list;
            *right_list = current;
        }
        current = next;
    }
}












// 0 is X-axis, 1 is Y-axis, 2 is Z-axis
int ft_longest_axis(t_aabb bbox) {
	double x_length = bbox.max.x - bbox.min.x;
	double y_length = bbox.max.y - bbox.min.y;
	double z_length = bbox.max.z - bbox.min.z;
	
	if (x_length >= y_length && x_length >= z_length) {
		return 0; // X-axis is the longest axis
	} else if (y_length >= x_length && y_length >= z_length) {
		return 1; // Y-axis is the longest axis
	} else {
		return 2; // Z-axis is the longest axis
	}
}






t_bvh_node *build_bvh_tree(t_object *object_list, t_aabb bounds) {
    // Base case: if the object list is empty, return NULL
    if (object_list == NULL) {
		printf("object_list is NULL 📙\n");
        return NULL;
    }

    // Base case: if the object list contains only one object, create a leaf node
    if (object_list->next == NULL) {
        t_bvh_node *leaf = malloc(sizeof(t_bvh_node));
        if (leaf == NULL) {
            perror("Failed to allocate memory for leaf node");
            exit(EXIT_FAILURE);
        }
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->data = object_list;
        leaf->isLeaf = 1;
        leaf->num_objects = 1;
        leaf->aabb = object_list->bounds;
        return leaf;
    }

    // Calculate the bounding box of the object list
    t_aabb bbox = calculate_list_bbox(object_list);

    // Calculate the longest axis of the bounding box
    int longest_axis = ft_longest_axis(bbox);

    // Sort the object list along the longest axis
    object_list = sort_object_list(object_list, longest_axis);

    // Split the object list into two halves
    t_object *left_list = NULL;
    t_object *right_list = NULL;
    split_object_list(object_list, longest_axis, &left_list, &right_list);

    // Recursively build the left and right subtrees
    t_bvh_node *left_subtree = build_bvh_tree(left_list, bbox);
    t_bvh_node *right_subtree = build_bvh_tree(right_list, bbox);

    // Create a new internal node
    t_bvh_node *internal_node = malloc(sizeof(t_bvh_node));
    if (internal_node == NULL) {
        perror("Failed to allocate memory for internal node");
        exit(EXIT_FAILURE);
    }
    internal_node->left = left_subtree;
    internal_node->right = right_subtree;
    internal_node->data = NULL;
    internal_node->isLeaf = 0;
    internal_node->num_objects = 0;
    internal_node->aabb = bbox;
	printf("Done building BVH tree\n");
    return internal_node;
}





int count_aabbs_in_bvh(t_bvh_node *node) {
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



void bvh_tree(t_scene *scene) {
    // Build the BVH tree and assign it to the scene's root
	printf("So there should be %i objects in the scene\n", scene->total_objects);
    scene->bvh_root = build_bvh_tree(scene->objects, *(scene->bounds));
	printf("\n\n\n\n\n\n📦 Total of %i AABBs in the BVH tree\n", count_aabbs_in_bvh(scene->bvh_root));
    printf("BVH tree created - %p\n\n\n", scene);
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
t_aabb calculate_list_bbox(t_object *object_list) {
    t_aabb bbox;
    bbox.min = (t_vec){INFINITY, INFINITY, INFINITY};
    bbox.max = (t_vec){-INFINITY, -INFINITY, -INFINITY};
    
    while (object_list) {
        t_aabb object_bbox = object_list->bounds;
        bbox.min.x = fmin(bbox.min.x, object_bbox.min.x);;
        bbox.min.y = fmin(bbox.min.y, object_bbox.min.y);
        bbox.min.z = fmin(bbox.min.z, object_bbox.min.z);
        
        bbox.max.x = fmax(bbox.max.x, object_bbox.max.x);
        bbox.max.y = fmax(bbox.max.y, object_bbox.max.y);
        bbox.max.z = fmax(bbox.max.z, object_bbox.max.z);
        
        object_list = object_list->next;
    }
    
    return bbox;
}


void	free_bvh_tree(t_scene *scene)
{
	ft_pntf("bvh fully freed - %i", scene);
}
