/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_viewport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:53:54 by mman              #+#    #+#             */
/*   Updated: 2024/06/15 19:16:38 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Camera Position, Orientation and Focal_Length are stored in the viewport struct
//this function only initalizes the upper left coordinations

static void	get_viewport_direction(t_scene *scene)
{
	double x = scene->viewport.orientation.x;
	double y = scene->viewport.orientation.y;

	printf("\n\n\nLooking ");

	if (x > 0.0 && x <= 0.5)
	{
		printf("slightly to the right ");
	}
	else if (x > 0.5 && x <= 1.0)
	{
		printf("to the right ");
	}
	else if (x >= -0.5 && x < 0.0)
	{
		printf("slightly to the left ");
	}
	else if (x >= -1.0 && x < -0.5)
	{
		printf("to the left ");
	}

	if (y >= -1.0 && y <= -0.5)
	{
		printf("and down ");
	}
	else if (y > -0.5 && y < 0.0)
	{
		printf("and slightly down ");
	}
	else if (y > 0.0 && y < 0.5)
	{
		printf("and slightly up ");
	}
	else if (y >= 0.5 && y <= 1.0)
	{
		printf("and up");
	}
	printf("\n");

	// Add similar conditions for z axis
}
//
void ft_initialize_viewport(t_scene **scene)
{
	printf("viewport rotation: %f, %f, %f\n", (*scene)->viewport.orientation.x, (*scene)->viewport.orientation.y, (*scene)->viewport.orientation.z);
	(*scene)->viewport.viewport_u = (t_vec){WIDTH, 0, 0};
	(*scene)->viewport.viewport_v = (t_vec){0, -HEIGHT, 0};
	(*scene)->viewport.pixel_delta_u = (t_vec){(*scene)->viewport.viewport_u.x / WIDTH, 0, 0};
	(*scene)->viewport.pixel_delta_v = (t_vec){0, (*scene)->viewport.viewport_v.y / HEIGHT, 0};
	
	// Calculate the bottom left corner of the viewport
	t_vec viewport_bottom_left = {
		(*scene)->viewport.cam_pos.x - ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.x,
		(*scene)->viewport.cam_pos.y - ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.y,
		(*scene)->viewport.cam_pos.z - ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.z
	};
	(*scene)->viewport.bottom_left = viewport_bottom_left;
	
	// Calculate the upper right corner of the viewport
	t_vec viewport_upper_right = {
		(*scene)->viewport.cam_pos.x + ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.x,
		(*scene)->viewport.cam_pos.y + ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.y,
		(*scene)->viewport.cam_pos.z + ((*scene)->viewport.viewport_u.x / 2) * (*scene)->viewport.orientation.z
	};
	(*scene)->viewport.upper_right = viewport_upper_right;
	
	printf("viewport ready\n");
	printf("fov %f\n", (*scene)->viewport.fov);
	printf("focal length %f\n", (*scene)->viewport.focal_length);
	printf("bottom_left %f %f %f\n", (*scene)->viewport.bottom_left.x, (*scene)->viewport.bottom_left.y, (*scene)->viewport.bottom_left.z);
	printf("upper_right %f %f %f\n", (*scene)->viewport.upper_right.x, (*scene)->viewport.upper_right.y, (*scene)->viewport.upper_right.z);
	printf("------------------\n");
	get_viewport_direction(*scene);
}

void ft_get_rotation(t_scene **scene)
{
	double x_rotation = (*scene)->viewport.orientation.x * 90.0;
	double y_rotation = (*scene)->viewport.orientation.y * 90.0;
	(*scene)->viewport.rotation.x = x_rotation * M_PI / 180.0;
	(*scene)->viewport.rotation.y = y_rotation * M_PI / 180.0;
	printf("rotation (in rad) x: %f, y: %f\n", x_rotation * M_PI / 180.0, y_rotation * M_PI / 180.0);
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
		ft_get_rotation(scene);
		(*scene)->viewport.fov = ft_atoidouble(split[3]);
		(*scene)->viewport.focal_length = focal_length((*scene)->viewport.fov);
		(*scene)->viewport.render_distance_cutoff = tan((*scene)->viewport.fov / 2);
		ft_initialize_viewport(scene);
		get_eye_coords(scene);
		printf("render cutoff distance : %f\n", (*scene)->viewport.render_distance_cutoff);
		printf("rotation in rad check: %f, %f\n", (*scene)->viewport.rotation.x, (*scene)->viewport.rotation.y);
	}
	else
		split = NULL;
}

void get_eye_coords(t_scene **scene)
{
	(*scene)->viewport.eye_pos.x = (*scene)->viewport.cam_pos.x + (*scene)->viewport.orientation.x * (*scene)->viewport.focal_length;
	(*scene)->viewport.eye_pos.y = (*scene)->viewport.cam_pos.y + (*scene)->viewport.orientation.y * (*scene)->viewport.focal_length;
	(*scene)->viewport.eye_pos.z = (*scene)->viewport.cam_pos.z + (*scene)->viewport.orientation.z * (*scene)->viewport.focal_length;
}