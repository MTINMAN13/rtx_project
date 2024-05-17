/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:19 by mman              #+#    #+#             */
/*   Updated: 2024/05/17 20:28:57 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error_check(char *string)
{
	ft_pntf("String checked passed: %s", string);
}

int	ft_mlx_init(t_mlxdata *mlxdata, char *argv[])
{
	ft_error_check(argv[1]);
	mlxdata->mlx = mlx_init();
	mlxdata->win = mlx_new_window(mlxdata->mlx, WIDTH, HEIGHT, NAME);
	mlxdata->img = mlx_new_image(mlxdata->mlx, WIDTH, HEIGHT);
	mlxdata->addr = mlx_get_data_addr(mlxdata->img, &(mlxdata->bits_per_pixel),
			&(mlxdata->line_length), &(mlxdata->endian));
	return (0);
}

void	ft_process_other_keys(int keycode, t_mlxdata *mlxdata)
{
	if (keycode == 65307)
		ft_close_window_event(mlxdata);
}

int	ft_key_hook(int keycode, t_mlxdata *mlxdata)
{
	ft_process_other_keys(keycode, mlxdata);
	mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->img, 0, 0);
	return (0);
}

void	ft_cleanup_all(t_mlxdata *mlxdata)
{
	mlx_destroy_image(mlxdata->mlx, mlxdata->img);
	mlx_destroy_window(mlxdata->mlx, mlxdata->win);
	mlx_destroy_display(mlxdata->mlx);
	free(mlxdata->mlx);
	exit(EXIT_SUCCESS);
}
