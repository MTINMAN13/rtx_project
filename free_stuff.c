/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:44:57 by mman              #+#    #+#             */
/*   Updated: 2024/05/23 20:53:48 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Freeing the individual t_vec structs
//Freeing the Viewport t_viewport struct


// void	ft_cleanup_all(t_mlxdata *mlxdata)
// {
// 	mlx_destroy_image(mlxdata->mlx, mlxdata->img);
// 	mlx_destroy_window(mlxdata->mlx, mlxdata->win);
// 	mlx_destroy_display(mlxdata->mlx);
// 	free(mlxdata->mlx);
// 	exit(EXIT_SUCCESS);
// }



//frees all pointers related to MLX (via mlx funcs.)
//also frees the *mlx pointer
//exits the program with EXIT_SUCCESS
void	ft_cleanup_all(t_scene **scene)
{
    t_mlxdata   *mlxdata;

    if (*scene == NULL) {
        return; 
    }
	ft_pntf("Cleaning up all resources\n");
    mlxdata = &(*scene)->mlx; 

    // Destroy MLX components in reverse order (using correct mlx_ptr)
    mlx_destroy_image(mlxdata->mlx, mlxdata->img);  
    mlx_destroy_window(mlxdata->mlx, mlxdata->win);  
    mlx_destroy_display(mlxdata->mlx); 

    free(mlxdata->mlx);  

    free((*scene)->scene_data); 

    free(*scene); 
    *scene = NULL; 
    ft_pntf("Cleaned up all resources yo\n");
}