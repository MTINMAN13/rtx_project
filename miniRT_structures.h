/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:34:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/18 19:44:48 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTURES_H
# define MINIRT_STRUCTURES_H


# include "miniRT.h"
# include "minilibx/mlx.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_mlxdata
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}			t_mlxdata;

//Store Camera and Viewport Values
typedef struct s_viewport
{
	t_vec	cam_pos;
	t_vec	orientation;
	double	focal_length;		//calculated as focal_length(FOV)
	t_vec	upper_left;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	pixel_delta_u;
	t_vec	pixel_delta_v;
}			t_viewport;

typedef struct s_scene
{
	t_viewport	viewport;
	t_mlxdata	mlx;
	char		*scene_data;
}			t_scene;

#endif
