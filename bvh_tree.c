/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:39:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 21:29:31 by mman             ###   ########.fr       */
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
void	bvh_tree(t_scene *scene)
{
	ft_pntf("beep boop im a bvh tree %i", scene);
}



//Function courtesy of GEMINI
// t_bvh_node* create_bvh_node(t_aabb aabb, void* data, int isLeaf) {
//     t_bvh_node* node = malloc(sizeof(t_bvh_node));
//     node->aabb = aabb;
//     node->data = data;
//     node->isLeaf = isLeaf;
//     return node;
// }