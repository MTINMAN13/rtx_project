/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:34:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/23 21:14:32 by mman             ###   ########.fr       */
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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

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

typedef struct s_object
{
	char			*raw_data;
	int				type;	//0 = camera, 1 = light, 2 = sphere, 3 = plane, 4 = square, 5 = cylinder, 6 = triangle
	t_vec			coordinates;
	t_color			color;
	double			diameter;
	double			brightness;
	double			height;
	double			ambient_ratio;
	struct s_object	*next;
}			t_object;

typedef struct s_scene
{
	t_viewport	viewport;
	t_mlxdata	mlx;
	t_object	*objects;
	char		*scene_data;
}			t_scene;

#endif