/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:34:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/27 18:35:53 by mman             ###   ########.fr       */
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

typedef struct s_aabb
{
	t_vec	min; // Minimum corner (x, y, z)
	t_vec	max; // Maximum corner (x, y, z)
	void	*data;    // Pointer to object or child nodes
    int		isLeaf;   // Flag to indicate leaf node (1) or internal node (0)
}			t_aabb;

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
	char	*raw_data;
	t_vec	cam_pos;		//taken in from the camera data
	t_vec	orientation;	//taken in from the camera data
	double	focal_length;		//calculated as focal_length(FOV)
	t_vec	upper_left;			//x y z coordinates of the upper left corner of the viewport
	t_vec	viewport_u;			//A 3D vector that spans the width of the viewport along the horizontal (x) axis.
	t_vec	viewport_v;			//A 3D vector that spans the height of the viewport along the vertical (y) axis.
	t_vec	pixel_delta_u;		//A 3D vector that represents the change in the x-coordinate for each pixel across the viewport.
	t_vec	pixel_delta_v;		//A 3D vector that represents the change in the y-coordinate for each pixel across the viewport.
}			t_viewport;

typedef struct s_object
{
	char			*raw_data;
	int				type;	//0 = camera, 1 = light, 2 = sphere, 3 = plane, 4 = square, 5 = cylinder, 6 = triangle
	t_vec			coordinates;
	t_vec			normal;
	t_color			color;
	t_aabb			bounds;
	double			diameter;
	double			brightness;
	double			height;
	double			ambient_ratio;
	struct s_object	*next;
	struct s_object	*prev;
}			t_object;

typedef struct s_light
{
	char			*raw_data;
	t_vec			coordinates;
	t_vec			normal;
	t_color			color;
	double			diameter;
	double			brightness;
	double			height;
	double			ambient_ratio;
	struct s_object	*next;
	struct s_object	*prev;
}			t_light;

typedef struct s_scene
{
	t_viewport	viewport;
	t_mlxdata	mlx;
	t_object	*objects;
	t_light		*lights;
	int			total_objects;
	int			total_lights;
	t_aabb		*bounds;
	t_color		ambient_light;
	double		ambient_ratio;
}			t_scene;

#endif
