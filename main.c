/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:41:52 by mman              #+#    #+#             */
/*   Updated: 2024/05/17 20:28:11 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	t_mlxdata	mlxdata;

	ft_mlx_init(&mlxdata, argv);
	if (argc)
		ft_pntf("Usage Guide: TBD");
	setup_event_hooks(&mlxdata);
	mlx_loop(mlxdata.mlx);
	return(EXIT_SUCCESS);
}
