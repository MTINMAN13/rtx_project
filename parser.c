/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:02:34 by mman              #+#    #+#             */
/*   Updated: 2024/07/14 22:20:37 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Function to create a new object node
t_object *create_new_object(void)
{
    t_object *new_object;

    new_object = malloc(sizeof(t_object));
    if (!new_object)
        return NULL; // Handle allocation failure
    new_object->raw_data = NULL;
    new_object->next = NULL;
    new_object->prev = NULL;
    return new_object;
}

// Function to add a new object to the scene's object list
void add_object_to_scene(t_engine **scene, t_object *new_object)
{
    if ((*scene)->objects == NULL)
    {
        (*scene)->objects = new_object;
    }
    else
    {
        t_object *current = (*scene)->objects;
        while (current->next != NULL)
            current = current->next;
        current->next = new_object;
        new_object->prev = current;
    }
    (*scene)->total_objects++;
}

// Function to parse the plane data
void parse_plane_data(char *line, t_engine **scene)
{
    if (ft_strncmp(line, "pl", 2) == 0)
    {
        char **split = ft_split(line, ' ');
        t_object *new_object = create_new_object();
        new_object->raw_data = ft_strdup(line);
        ft_assign_values_to_t_vec(&new_object->coordinates, split[1]);
        ft_assign_values_to_t_vec(&new_object->normal, split[2]);
        ft_assign_values_to_t_color(&new_object->color, split[3]);
        new_object->type = 3;
        calculate_plane_bounds(new_object->normal, new_object->coordinates, new_object);
        add_object_to_scene(scene, new_object);
        free(split);
    }
}

// Function to parse the sphere data
void parse_sphere_data(char *line, t_engine **scene)
{
    if (ft_strncmp(line, "sp", 2) == 0)
    {
        char **split = ft_split(line, ' ');
        t_object *new_object = create_new_object();
        new_object->raw_data = ft_strdup(line);
        ft_assign_values_to_t_vec(&new_object->coordinates, split[1]);
        new_object->diameter = ft_atoidouble(split[2]);
        ft_assign_values_to_t_color(&new_object->color, split[3]);
        new_object->type = 2;
        calculate_aabb(new_object, &new_object->aabb);
        add_object_to_scene(scene, new_object);
        free(split);
    }
}

// Function to parse the cylinder data
void parse_cylinder_data(char *line, t_engine **scene)
{
    if (ft_strncmp(line, "cl", 2) == 0)
    {
        char **split = ft_split(line, ' ');
        t_object *new_object = create_new_object();
        new_object->raw_data = ft_strdup(line);
        ft_assign_values_to_t_vec(&new_object->coordinates, split[1]);
        ft_assign_values_to_t_vec(&new_object->normal, split[2]);
        new_object->diameter = ft_atoidouble(split[3]);
        new_object->height = ft_atoidouble(split[4]);
        ft_assign_values_to_t_color(&new_object->color, split[5]);
        new_object->type = 4;
        calculate_aabb(new_object, &new_object->aabb);
        add_object_to_scene(scene, new_object);
        free(split);
    }
}

// Function to parse the input file
int ft_parse(int fd, t_engine **scene)
{
    char *line = NULL;
    int i = 0;

	(*scene)->objects = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        ft_pntf("beep boop im a parser\n %s", line);
        i += parse_camera_data(line, scene);
        parse_sphere_data(line, scene);
        parse_plane_data(line, scene);
        parse_cylinder_data(line, scene);
        parse_ambient_light(line, scene);
        free(line);
    }
    if (i!=1)
    {
        printf("Found SUS amount of CAMERA DATA!");
        exit(EXIT_FAILURE);
    }
    ft_pntf("⭐ found %i objects", (*scene)->total_objects);

    // Print out the raw data from all the objects
    t_object *current_object = (*scene)->objects;
    while (current_object != NULL)
    {
        ft_pntf("x Raw data: %s", current_object->raw_data);
        current_object = current_object->next;
    }

    return (EXIT_SUCCESS);
}
