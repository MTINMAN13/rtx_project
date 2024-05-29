/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:12:31 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 17:40:28 by mman             ###   ########.fr       */
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

	if (ft_strncmp(line, "sp", 2) == 0)
	{
		ft_pntf("found a sphere");
		split = ft_split(line, ' ');
		ft_pntf("beep boop im a sphere, %s", split[1]);
		ft_assign_values_to_t_vec(&(*scene)->objects->coordinates, split[1]);
		(*scene)->objects->diameter = ft_atoidouble(split[2]);
		ft_assign_values_to_t_color(&(*scene)->objects->color, split[3]);
		(*scene)->objects->type = 2;
		calculate_aabb((*scene)->objects, &(*scene)->objects->bounds);
		(*scene)->objects->next = malloc(sizeof(t_object));
		(*scene)->objects->next->prev = (*scene)->objects;
		(*scene)->objects = (*scene)->objects->next;
		(*scene)->objects->next = NULL;
		(*scene)->total_objects++;
		free(split);
		ft_pntf("jobs done");
	}
	else
		split = NULL;
}

// Function to parse the plane data
// plane is passed in in the following format
//
// pl 0.0,0.0,20.6 0.0,0.0,1.0 10,0,255
void	parse_plane_data(char *line, t_scene **scene)
{
	char	**split;

	if (ft_strncmp(line, "pl", 2) == 0)
	{
		split = ft_split(line, ' ');
		(*scene)->objects->raw_data = ft_strdup(line);
		ft_pntf("beep boop im a plane, %s", split);
		ft_assign_values_to_t_vec(&(*scene)->objects->coordinates, split[1]);
		ft_assign_values_to_t_vec(&(*scene)->objects->normal, split[2]);
		ft_assign_values_to_t_color(&(*scene)->objects->color, split[3]);
		(*scene)->objects->type = 3;
		calculate_aabb((*scene)->objects, &(*scene)->objects->bounds);
		(*scene)->objects->next = malloc(sizeof(t_object));
		(*scene)->objects->next->prev = (*scene)->objects;
		(*scene)->objects = (*scene)->objects->next;
		(*scene)->objects->next = NULL;
		(*scene)->total_objects++;
		free(split);
	}
	else
		split = NULL;
}

// Function to parse the cylinder data
// cylinder is passed in in the following format
//
// cl 0.0,0.0,20.6 0.0,0.0,1.0 12.6 10,0,255
void	parse_cylinder_data(char *line, t_scene **scene)
{
	char	**split;

	if (ft_strncmp(line, "cl", 2) == 0)
	{
		split = ft_split(line, ' ');
		(*scene)->objects->raw_data = ft_strdup(line);
		ft_pntf("beep boop im a cylinder, %s", split);
		ft_assign_values_to_t_vec(&(*scene)->objects->coordinates, split[1]);
		ft_assign_values_to_t_vec(&(*scene)->objects->normal, split[2]);
		(*scene)->objects->diameter = ft_atoidouble(split[3]);
		(*scene)->objects->height = ft_atoidouble(split[4]);
		ft_assign_values_to_t_color(&(*scene)->objects->color, split[5]);
		(*scene)->objects->type = 4;
		calculate_aabb((*scene)->objects, &(*scene)->objects->bounds);
		(*scene)->objects->next = malloc(sizeof(t_object));
		(*scene)->objects->next->prev = (*scene)->objects;
		(*scene)->objects = (*scene)->objects->next;
		(*scene)->objects->next = NULL;
		(*scene)->total_objects++;
		free(split);
	}
	else
		split = NULL;
}

// Function to parse the input file
//If it finds a C, it will ram the data into scene->viewport
//If it finds other shit, it will do it into scene->objects->raw_data
//It then tells us how many objects are there
int	ft_parse(int fd, t_scene **scene)
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
			parse_ambient_light(line, scene);
			// Get the next line
			line = get_next_line(fd);
		}
		ft_pntf("found %i objects", (*scene)->total_objects);
		free(line);
	}
	return (EXIT_SUCCESS);
}
