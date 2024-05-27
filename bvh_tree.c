/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:39:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 03:15:39 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Bounding Volume Hierarchy -- the box that surrounds all objects in the scene
//axis-aligned bounding box (AABB)
void	bvh_bounds(t_scene *scene)
{
	ft_pntf("beep boop im a bvh bounds %i", scene);
}


//stuff from scene->objects is to be stored in a BVH tree
//
//cylinder           
//sphere
//plane
void	bvh_tree(t_scene *scene)
{
	ft_pntf("beep boop im a bvh tree %i", scene);
}