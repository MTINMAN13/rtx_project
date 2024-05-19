/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:44:57 by mman              #+#    #+#             */
/*   Updated: 2024/05/18 17:47:41 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Freeing the individual t_vec structs
//Freeing the Viewport t_viewport struct


//frees all pointers related to MLX (via mlx funcs.)
//also frees the *mlx pointer
//exits the program with EXIT_SUCCESS
void	ft_cleanup_all(t_mlxdata *mlxdata)
{
	mlx_destroy_image(mlxdata->mlx, mlxdata->img);
	mlx_destroy_window(mlxdata->mlx, mlxdata->win);
	mlx_destroy_display(mlxdata->mlx);
	free(mlxdata->mlx);
	exit(EXIT_SUCCESS);
}

