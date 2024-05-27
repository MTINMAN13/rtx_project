/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:53:54 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 00:27:55 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Camera Position, Orientation and Focal_Length are stored in the viewport struct
//this function only initalizes the upper left coordinations
//
void ft_initialize_viewport(t_scene **scene)
{
	t_viewport *viewport;

	viewport = malloc(sizeof(t_viewport));
	*viewport = (*scene)->viewport;
	viewport->viewport_u = (t_vec){WIDTH, 0, 0};
	viewport->viewport_v = (t_vec){0, -HEIGHT, 0};
	viewport->pixel_delta_u = (t_vec){viewport->viewport_u.x / WIDTH, 0, 0};
	viewport->pixel_delta_v = (t_vec){0, viewport->viewport_v.y / HEIGHT, 0};
	viewport->upper_left = (t_vec){viewport->cam_pos.x - (viewport->viewport_u.x / 2),
									viewport->cam_pos.y + (viewport->viewport_v.y / 2),
									viewport->cam_pos.z - viewport->focal_length};
	ft_pntf("viewport rdy");
}
