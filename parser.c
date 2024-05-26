/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:12:31 by mman              #+#    #+#             */
/*   Updated: 2024/05/26 18:00:19 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Function to parse the sphere data
// sphere is passed in in the following format
//
// sp 0.0,0.0,20.6 12.6 10,0,255
void	parse_sphere_data(char *line, t_scene **scene)
{
	char	**split;

	// Check if the line starts with 'sp'
	if (ft_strncmp(line, "sp", 2) == 0)
	{
		split = ft_split(line, ' ');
		(*scene)->objects->raw_data = ft_strdup(line);
		ft_pntf("beep boop im a sphere, %s", split);
		ft_assign_values_to_t_vec(&(*scene)->objects->coordinates, split[1]);
		(*scene)->objects->diameter = ft_atoidouble(split[2]);
		ft_assign_values_to_t_color(&(*scene)->objects->color, split[3]);
		(*scene)->objects->type = 2;
		(*scene)->objects->next = malloc(sizeof(t_object));
		(*scene)->objects = (*scene)->objects->next;
		(*scene)->objects->next = NULL;
		(*scene)->total_objects++;
		free(split);
	}
	else
		split = NULL;
}

// Function to parse the plane data
// plane is passed in in the following format
//
// pl 0.0,0.0,20.6 0.0,0.0,1.0 10,0,255
void parse_plane_data(char* line, t_scene** scene)
{
	char	**split;

}

// Function to parse the cylinder data
void parse_cylinder_data(char* line, t_scene** scene) {
	// Check if the line starts with 'cl'
	if (ft_strncmp(line, "cl", 2) == 0)
	{
		ft_pntf("beep boop im a cylinder, %i", scene);
	}
}

void parse_camera_data(char* line, t_scene** scene)
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
		(*scene)->viewport.focal_length = focal_length(ft_atoi(split[3]));
	}
	else
		split = NULL;
	ft_pntf("beep boop im a suppressor, %s", split);
}

// Function to parse the input file
//If it finds a C, it will ram the data into scene->viewport
//If it finds other shit, it will do it into scene->objects->raw_data
//It then tells us how many objects are there
int ft_parse(int fd, t_scene** scene)
{
	char	*line;

	line = NULL;
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			ft_pntf("beep boop im a parser\n %s", line);

			// Parse the line starting with 'C'
			parse_camera_data(line, scene);
			// Parse the line starting with 'sp'
			parse_sphere_data(line, scene);
			// Parse the line starting with 'pl'
			parse_plane_data(line, scene);
			// Parse the line starting with 'cl'
			parse_cylinder_data(line, scene);
			// Get the next line
			line = get_next_line(fd);
		}
	}
	return (EXIT_SUCCESS);
}
