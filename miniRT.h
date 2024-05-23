/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:42:01 by mman              #+#    #+#             */
/*   Updated: 2024/05/23 20:49:20 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "miniRT_structures.h"
# include "libft/includes/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# define WIDTH 1200
# define HEIGHT 800
# define NAME "miniRTX  |  agadkari & mman project"
# ifndef M_PI
#  define M_PI 3.141592653589793238462643383279502884197169399375105820974944
# endif

void	ft_error_check(char *string);
int		ft_mlx_init(t_mlxdata *mlxdata);
void	ft_process_other_keys(int keycode, t_scene **scene);
int		ft_key_hook(int keycode, t_scene *scene);
void	ft_cleanup_all(t_scene **scene);
int     ft_close_window_event(t_scene *scene);
int		ft_mouse_hook(int button, int x, int y, t_mlxdata *mlxdata);
void	setup_event_hooks(t_scene *scene);
void	render(t_scene *scene);

//Calculations:
double	focal_length(int fov);


#endif
