/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:42:01 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 17:18:11 by mman             ###   ########.fr       */
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
# define SAMPLES_PER_PIXEL 8
# define NAME "miniRTX  | mman & agadkari project"
# ifndef M_PI
#  define M_PI 3.141592653589793238462643383279502884197169399375105820974944
# endif

void	ft_error_check(char *string);
int		ft_mlx_init(t_mlxdata *mlxdata);
void	ft_process_other_keys(int keycode, t_scene **scene);
int		ft_key_hook(int keycode, t_scene *scene);
void	ft_cleanup_all(t_scene **scene);
void	ft_free_scene_objects(t_scene **scene);
int		ft_close_window_event(t_scene *scene);
int		ft_mouse_hook(int button, int x, int y, t_mlxdata *mlxdata);
void	setup_event_hooks(t_scene *scene);
void	render(t_scene *scene);

void	ft_initialize_viewport(t_scene **scene);
void	bvh_tree(t_scene *scene);
void	bvh_bounds(t_scene *scene);
void	calculate_aabb(t_object	*object, t_aabb	*aabb);

//Parsing:
int		ft_parse(int fd, t_scene **scene);
void	parse_camera_data(char *line, t_scene **scene);
void	parse_sphere_data(char *line, t_scene **scene);
void	parse_plane_data(char *line, t_scene **scene);
void	parse_cylinder_data(char *line, t_scene **scene);

//Vector Allocation:
void	ft_assign_values_to_t_vec(t_vec *vec, char *str);
void	ft_assign_values_to_t_color(t_color *color, char *str);
void	parse_ambient_light(char *line, t_scene **scene);

//Calculations:
double	focal_length(double fov);
double	ft_fmax(double x, double y);
double	ft_fmin(double x, double y);


#endif
