/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functionss.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:28:45 by mman              #+#    #+#             */
/*   Updated: 2024/07/14 02:18:12 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_close_window_event(t_engine *scene)
{
	printf("Window Closed\n");
	ft_cleanup_all(&scene);
	ft_pntf("Exiting program\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_mlxdata *mlxdata)
{
	if (button == 1 || button == 2)
	{
		ft_pntf("Mouse data:  X-%i, Y-%i", x, y);
		return (1);
	}
	mlx_put_image_to_window(mlxdata->mlx, mlxdata->win, mlxdata->img, 0, 0);
	return (0);
}

