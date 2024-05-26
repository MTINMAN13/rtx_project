/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:41:52 by mman              #+#    #+#             */
/*   Updated: 2024/05/26 19:03:43 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
A 0.2 255,255,255

C -50.0,0,20 0,0,1 70
coordinates, orientation axis*, FOV (0-180)
L -40.0,50.0,0.0 0.6
coordinates - brightness


sp 0.0,0.0,20.6 12.6 10,0,255
coordinates - diameter - color(RGB)


	*3d normalized orientation vector.
	In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
*/

void	render(t_scene *scene)
{
	ft_pntf("beep boop im a render %i", scene);
}

//You need at least these 3 simple geometric objects: plane, sphere, cylinder.

//Sets up Viewport
//Stores the values of objects in the scene (obviously parses the data)
//Exits the program (safely) if something fucks up
int	ft_initialize(t_scene **scene, char *input)
{
	int		fd1;

	ft_error_check(input);
	*scene = malloc(sizeof(t_scene));
	if (*scene == NULL)
		return (EXIT_FAILURE);
	(*scene)->objects = malloc(sizeof(t_object));
	(*scene)->objects->prev = NULL;
	(*scene)->objects->next = NULL;
	if ((*scene)->objects == NULL)
		return (EXIT_FAILURE);
	fd1 = open(input, O_RDONLY);
	ft_parse(fd1, scene);
	if (fd1 == -1)
	{
		perror("Error opening file");
		free(*scene);
		return (EXIT_FAILURE);
	}
	close(fd1);
	ft_mlx_init(&(*scene)->mlx);
	ft_pntf("%i", &(*scene)->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_scene		*scene;

	ft_pntf("argv %s", argv[1]);
	ft_initialize(&scene, "scene.rt");
	if (argc)
		ft_pntf("Usage Guide: TBD");
	setup_event_hooks(scene);
	render(scene);
	if (mlx_loop(scene->mlx.mlx) != 0)
	{
		ft_pntf("Error starting MLX loop\n");
		return (EXIT_FAILURE);
	}
	ft_pntf("exiting");
	return (EXIT_SUCCESS);
}
