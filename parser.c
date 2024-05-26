/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:12:31 by mman              #+#    #+#             */
/*   Updated: 2024/05/26 14:17:59 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Function to parse the sphere data
void parse_sphere_data(char* line, t_scene** scene)
{
	// Check if the line starts with 'sp'
	if (ft_strncmp(line, "sp", 2) == 0)
	{
		ft_pntf("beep boop im a sphere, %i", scene);
	}
}

// Function to parse the plane data
void parse_plane_data(char* line, t_scene** scene)
{
	// Check if the line starts with 'pl'
	if (ft_strncmp(line, "pl", 2) == 0)
	{
		ft_pntf("beep boop im a plane, %i", scene);
	}
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
		ft_pntf("beep boop im a cylinder, %i", scene);
		split = ft_split(line, ' ');
	}
	else
		split = NULL;
	ft_pntf("beep boop im a cylinder, %s", split);
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