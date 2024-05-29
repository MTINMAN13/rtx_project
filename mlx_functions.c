/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:19 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 17:42:43 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error_check(char *string)
{
	ft_pntf("PLEASE DELIMIT THE INSTRUCTIONS BY A SINGLE SPACE AND A NEWLINE\n");
	ft_pntf("String checked passed: %s", string);
}

int	ft_mlx_init(t_mlxdata *mlxdata)
{
	mlxdata->mlx = mlx_init();
	mlxdata->win = mlx_new_window(mlxdata->mlx, WIDTH, HEIGHT, NAME);
	mlxdata->img = mlx_new_image(mlxdata->mlx, WIDTH, HEIGHT);
	mlxdata->addr = mlx_get_data_addr(mlxdata->img, &(mlxdata->bits_per_pixel),
			&(mlxdata->line_length), &(mlxdata->endian));
	return (0);
}

void	ft_process_other_keys(int keycode, t_scene **scene)
{
	if (keycode == 65307) {
		ft_pntf("Escape key pressed\n");
		ft_close_window_event(*scene); // Corrected cleanup function call
	}
}

int	ft_key_hook(int keycode, t_scene *scene)  // Changed to single pointer
{
	ft_process_other_keys(keycode, &scene); // Pass address of scene
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0); // Corrected mlxdata access
	return (0);
}

void	setup_event_hooks(t_scene *scene)
{
	mlx_key_hook(scene->mlx.win, ft_key_hook, scene);
	mlx_hook(scene->mlx.win, 17, 0, ft_close_window_event, scene);
	mlx_mouse_hook(scene->mlx.win, ft_mouse_hook, &scene->mlx);
	ft_pntf("Event hooks set up\n");
}