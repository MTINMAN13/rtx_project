/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_viewport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:53:54 by mman              #+#    #+#             */
/*   Updated: 2024/06/16 22:12:01 by mman             ###   ########.fr       */
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
void	ft_initialize_viewport(t_scene **scene)
{
	(*scene)->viewport.upper_right.x = (*scene)->viewport.viewport_middle.x + WIDTH / 2;
	(*scene)->viewport.upper_right.y = (*scene)->viewport.viewport_middle.y + HEIGHT / 2;
	(*scene)->viewport.upper_right.z = (*scene)->viewport.viewport_middle.z;
	(*scene)->viewport.lower_left.x = (*scene)->viewport.viewport_middle.x - WIDTH / 2;
	(*scene)->viewport.lower_left.y = (*scene)->viewport.viewport_middle.y - HEIGHT / 2;
	(*scene)->viewport.lower_left.z = (*scene)->viewport.viewport_middle.z;
	(*scene)->viewport.upper_left.x = (*scene)->viewport.viewport_middle.x - WIDTH / 2;
	(*scene)->viewport.upper_left.y = (*scene)->viewport.viewport_middle.y + HEIGHT / 2;
	(*scene)->viewport.upper_left.z = (*scene)->viewport.viewport_middle.z;
	(*scene)->viewport.lower_right.x = (*scene)->viewport.viewport_middle.x + WIDTH / 2;
	(*scene)->viewport.lower_right.y = (*scene)->viewport.viewport_middle.y - HEIGHT / 2;
	(*scene)->viewport.lower_right.z = (*scene)->viewport.viewport_middle.z;
	(*scene)->viewport.eye_pos.x = (*scene)->viewport.viewport_middle.x;
	(*scene)->viewport.eye_pos.y = (*scene)->viewport.viewport_middle.y;
	(*scene)->viewport.eye_pos.z = (*scene)->viewport.viewport_middle.z - (*scene)->viewport.focal_length;
	printf("viewport ready\n");
	printf("fov %f\n", (*scene)->viewport.fov);
	printf("focal length %f\n", (*scene)->viewport.focal_length);
	printf("---------------VIEWPORT DATA--\n");
	printf("viewport_middle [%f,%f,%f]\n", (*scene)->viewport.viewport_middle.x, (*scene)->viewport.viewport_middle.y, (*scene)->viewport.viewport_middle.z);
	printf("upper_right [%f,%f,%f]\n", (*scene)->viewport.upper_right.x, (*scene)->viewport.upper_right.y, (*scene)->viewport.upper_right.z);	
	printf("lower_left [%f,%f,%f]\n", (*scene)->viewport.lower_left.x, (*scene)->viewport.lower_left.y, (*scene)->viewport.lower_left.z);
	printf("eye_pos [%f,%f,%f]\n", (*scene)->viewport.eye_pos.x, (*scene)->viewport.eye_pos.y, (*scene)->viewport.eye_pos.z);
	printf("------------------\n");
	get_viewport_direction(*scene);
}

void	ft_get_rotation(t_scene **scene)
{
    double x_rotation = (*scene)->viewport.orientation.x * 90.0;
    double y_rotation = (*scene)->viewport.orientation.y * 90.0;
    (*scene)->viewport.rotation.x = x_rotation * M_PI / 180.0;
    (*scene)->viewport.rotation.y = y_rotation * M_PI / 180.0;

    double rotation_matrix_x[3][3] = {
        {1, 0, 0},
        {0, cos(x_rotation), -sin(x_rotation)},
        {0, sin(x_rotation), cos(x_rotation)}
    };

    double rotation_matrix_y[3][3] = {
        {cos(y_rotation), 0, sin(y_rotation)},
        {0, 1, 0},
        {-sin(y_rotation), 0, cos(y_rotation)}
    };

    // Multiply the two matrices together to get the final rotation matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*scene)->viewport.rotation_matrix[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                (*scene)->viewport.rotation_matrix[i][j] += rotation_matrix_x[i][k] * rotation_matrix_y[k][j];
            }
        }
    }

    printf("rotation (in rad) x: %f, y: %f\n", x_rotation * M_PI / 180.0, y_rotation * M_PI / 180.0);
    printf("rotation matrix: \n");
    for (int i = 0; i < 3; i++) {
        printf("%f %f %f\n", (*scene)->viewport.rotation_matrix[i][0], (*scene)->viewport.rotation_matrix[i][1], (*scene)->viewport.rotation_matrix[i][2]);
    }
    printf("------------------\n");
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
		ft_assign_values_to_t_vec(&(*scene)->viewport.viewport_middle, split[1]);
		ft_assign_values_to_t_vec(&(*scene)->viewport.orientation, split[2]);
		ft_get_rotation(scene);
		(*scene)->viewport.fov = ft_atoidouble(split[3]);
		(*scene)->viewport.focal_length = focal_length((*scene)->viewport.fov);
		(*scene)->viewport.render_distance_cutoff = tan((*scene)->viewport.fov / 2);
		ft_initialize_viewport(scene);
		ft_rotate_viewport(scene);
		printf("render cutoff distance : %f\n", (*scene)->viewport.render_distance_cutoff);
	}
	else
		split = NULL;
}

void	ft_rotate_viewport(t_scene **scene)
{
	transform_vertex((*scene)->viewport.viewport_middle, &(*scene)->viewport.upper_right, (*scene)->viewport.rotation_matrix);
	transform_vertex((*scene)->viewport.viewport_middle, &(*scene)->viewport.lower_left, (*scene)->viewport.rotation_matrix);
	transform_vertex((*scene)->viewport.viewport_middle, &(*scene)->viewport.lower_right, (*scene)->viewport.rotation_matrix);
	transform_vertex((*scene)->viewport.viewport_middle, &(*scene)->viewport.upper_left, (*scene)->viewport.rotation_matrix);
	transform_vertex((*scene)->viewport.viewport_middle, &(*scene)->viewport.eye_pos, (*scene)->viewport.rotation_matrix);
	printf("rotation complete\n");
	printf("---------------VIEWPORT DATA--\n");
	printf("viewport_middle [%f,%f,%f]\n", (*scene)->viewport.viewport_middle.x, (*scene)->viewport.viewport_middle.y, (*scene)->viewport.viewport_middle.z);
	printf("upper_right [%f,%f,%f]\n", (*scene)->viewport.upper_right.x, (*scene)->viewport.upper_right.y, (*scene)->viewport.upper_right.z);	
	printf("lower_left [%f,%f,%f]\n", (*scene)->viewport.lower_left.x, (*scene)->viewport.lower_left.y, (*scene)->viewport.lower_left.z);
	printf("eye_pos [%f,%f,%f]\n", (*scene)->viewport.eye_pos.x, (*scene)->viewport.eye_pos.y, (*scene)->viewport.eye_pos.z);
	printf("------------------\n");
}

void get_eye_coords(t_scene **scene)
{
	(*scene)->viewport.eye_pos.x = (*scene)->viewport.viewport_middle.x + (*scene)->viewport.orientation.x * (*scene)->viewport.focal_length;
	(*scene)->viewport.eye_pos.y = (*scene)->viewport.viewport_middle.y + (*scene)->viewport.orientation.y * (*scene)->viewport.focal_length;
	(*scene)->viewport.eye_pos.z = (*scene)->viewport.viewport_middle.z + (*scene)->viewport.orientation.z * (*scene)->viewport.focal_length;
}