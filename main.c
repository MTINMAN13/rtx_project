/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:41:52 by mman              #+#    #+#             */
/*   Updated: 2024/07/17 19:38:04 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_initialize(t_engine **scene, char *input)
{
	int		fd1;

	ft_pntf("💎 ------------- INITIALIZATION  ------------- 💎");
	ft_error_check(input);
	*scene = malloc(sizeof(t_engine));
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
	ft_pntf("💎 ------------- INITIALIZATION COMPLETE ------------- 💎");
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_engine		*program;

	ft_pntf("argv[0]: %s", argv[0]);
	ft_initialize(&program, "scene.rt");
	if (argc)
		ft_pntf("Usage Guide: TBD");
	setup_event_hooks(program);
	render(program);
	mlx_loop(program->mlx.mlx);
	ft_pntf("exiting");
	return (EXIT_SUCCESS);
}
