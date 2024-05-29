/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:39:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 17:41:58 by mman             ###   ########.fr       */
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



// //Function courtesy of GEMINI
// t_bvh_node	*create_bvh_node(t_aabb aabb, void* data, int isLeaf)
// {
// 	t_bvh_node* node = malloc(sizeof(t_bvh_node));
// 	node->aabb = aabb;
// 	node->data = data;
// 	node->isLeaf = isLeaf;
// 	return node;
// }

// //The root is already calculated in the scene struct scene->bounds
// //Needs to take the viewport and the scene->objects and create a BVH tree, can count with the scene->bounds ass all the objects should be in bounds, the rest is "devoid" of any objects
// void bvh_tree(t_scene *scene)
// {
// 	// Create the root node of the BVH tree using the scene bounds
// 	t_bvh_node *root = create_bvh_node(scene->bounds, NULL, 0);

// 	// Iterate over the objects in the scene and insert them into the BVH tree
// 	for (int i = 0; i < scene->num_objects; i++)
// 	{
// 		t_object *object = scene->objects[i];
// 		// Calculate the object's AABB (axis-aligned bounding box)
// 		t_aabb aabb = calculate_aabb(object);
// 		// Insert the object into the BVH tree
// 		insert_object(root, object, aabb);
// 	}

// 	// Now the BVH tree is constructed, you can perform operations on it
// 	// such as ray-object intersection tests or rendering

// 	// Example: Traverse the BVH tree and print the objects in each leaf node
// 	traverse_bvh_tree(root);

// 	// Free the memory allocated for the BVH tree
// 	free_bvh_tree(root);
// }

void	bvh_tree(t_scene *scene)
{
	ft_pntf("bvh tree %i", scene);
}

void	free_bvh_tree(t_scene *scene)
{
	ft_pntf("bvh fully freed - %i", scene);
}
