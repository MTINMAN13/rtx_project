/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_viewport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:53:54 by mman              #+#    #+#             */
/*   Updated: 2024/06/15 17:26:37 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Camera Position, Orientation and Focal_Length are stored in the viewport struct
//this function only initalizes the upper left coordinations
//
void ft_initialize_viewport(t_scene **scene)
{
	(*scene)->viewport.viewport_u = (t_vec){WIDTH, 0, 0};
	(*scene)->viewport.viewport_v = (t_vec){0, -HEIGHT, 0};
	(*scene)->viewport.pixel_delta_u = (t_vec){(*scene)->viewport.viewport_u.x / WIDTH, 0, 0};
	(*scene)->viewport.pixel_delta_v = (t_vec){0, (*scene)->viewport.viewport_v.y / HEIGHT, 0};
	(*scene)->viewport.bottom_left = (t_vec){(*scene)->viewport.cam_pos.x - ((*scene)->viewport.viewport_u.x / 2),
											 (*scene)->viewport.cam_pos.y + ((*scene)->viewport.viewport_v.y / 2),
											 (*scene)->viewport.cam_pos.z - (*scene)->viewport.focal_length};
	(*scene)->viewport.upper_right = (t_vec){(*scene)->viewport.cam_pos.x + ((*scene)->viewport.viewport_u.x / 2),
											 (*scene)->viewport.cam_pos.y - ((*scene)->viewport.viewport_v.y / 2),
											 (*scene)->viewport.cam_pos.z - (*scene)->viewport.focal_length};
	ft_pntf("viewport rdy");
	printf("fov %f\n", (*scene)->viewport.fov);
	printf("focal length %f\n", (*scene)->viewport.focal_length);
	printf("bottom_left %f %f %f\n", (*scene)->viewport.bottom_left.x, (*scene)->viewport.bottom_left.y, (*scene)->viewport.bottom_left.z);
	printf("upper_right %f %f %f\n", (*scene)->viewport.upper_right.x, (*scene)->viewport.upper_right.y, (*scene)->viewport.upper_right.z);
	ft_pntf("------------------");
}

void	parse_camera_data(char *line, t_scene **scene)
{
	char	**split;
	// t_vec	*coords;
	// t_vec	*orientation;
	// coords = NULL;
	// orientation = NULL;
	if (ft_strncmp(line, "C", 1) == 0)
	{
		split = ft_split(line, ' ');
		(*scene)->viewport.raw_data = ft_strdup(line);
		ft_assign_values_to_t_vec(&(*scene)->viewport.cam_pos, split[1]);
		ft_assign_values_to_t_vec(&(*scene)->viewport.orientation, split[2]);
		(*scene)->viewport.fov = ft_atoidouble(split[3]);
		(*scene)->viewport.focal_length = focal_length((*scene)->viewport.fov);
		(*scene)->viewport.render_distance_cutoff = tan((*scene)->viewport.fov / 2);
		ft_initialize_viewport(scene);
		get_eye_coords(scene);
		printf("render cutoff distance : %f\n", (*scene)->viewport.render_distance_cutoff);
	}
	else
		split = NULL;
}

void	get_eye_coords(t_scene **scene)
{
	(*scene)->viewport.eye_pos.x = (*scene)->viewport.cam_pos.x;
	(*scene)->viewport.eye_pos.y = (*scene)->viewport.cam_pos.y;
	(*scene)->viewport.eye_pos.z = (*scene)->viewport.cam_pos.z - (*scene)->viewport.focal_length;
}