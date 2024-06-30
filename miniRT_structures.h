/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:34:58 by mman              #+#    #+#             */
/*   Updated: 2024/06/30 15:16:59 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTURES_H
# define MINIRT_STRUCTURES_H


# include "miniRT.h"
# include "minilibx/mlx.h"

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
}			t_quaternion;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_aabb
{
	t_vec	min; // Minimum corner (x, y, z) -- Left bottom corner
	t_vec	max; // Maximum corner (x, y, z) -- Right top corner
}			t_aabb;

typedef struct s_bvh_node
{
	t_aabb				aabb; // Axis-aligned bounding box
	void				*data; // Pointer to the data stored in the node
	int					isLeaf; // Flag indicating if the node is a leaf node
	int					num_objects; // Number of objects in the node
	struct s_bvh_node	*left; // Pointer to the left child node
	struct s_bvh_node	*right; // Pointer to the right child node
}			t_bvh_node;

typedef	struct s_kvadr
{
	
}		t_kvadr;

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
	char		*addr;			 // This is a pointer to the memory address where the image's pixel data is stored. It is obtained by calling mlx_get_data_addr(). This address allows you to directly manipulate the pixel data of the image.
	int			bits_per_pixel;  //This integer indicates the number of bits used to represent each pixel in the image. Common values are 24 (for 8 bits each of Red, Green, and Blue) or 32 (for 8 bits each of Red, Green, Blue, and Alpha).
	int			line_length;	// This integer represents the number of bytes used to store a single line of pixels in the image. This value is useful for calculating the address of a specific pixel and for iterating over the image data.
	int			endian;			// This integer indicates the endianness of the image data. Endianness refers to the byte order used to store pixel data. It can help you determine how to correctly interpret the color values in the image.
}			t_mlxdata;

typedef struct s_rotation
{
	double	x; //degrees in rad
	double	y; //degrees in rad
}			t_rotation;

//Store Camera / Viewport Values
typedef struct s_viewport
{
	char		*raw_data;
	t_vec		viewport_middle;		//taken in from the camera data
	t_vec		eye_pos;		//calculated later on
	t_vec		orientation;	//taken in from the camera data
	t_vec		normal_unit;	//3d vector that represents the change in coordinate for one unit of direction along the directional axis of the camera (eye_pos through the viewport_middle)
	t_rotation	rotation;	//taken in from the camera data
	double		rotation_matrix[3][3];	//calculated from the rotation values
	double		focal_length;		//calculated as focal_length(FOV)
	double		fov;
	double		render_distance_cutoff;
	t_vec		lower_left;			//x y z coordinates of the upper left corner of the viewport
	t_vec		lower_right;			//x y z coordinates of the point the camera is looking at
	t_vec		upper_right;		//x y z coordinates of the bottom right corner of the viewport -- to simplify some claculations
	t_vec		upper_left;
	t_vec		viewport_u;			//A 3D vector that spans the width of the viewport along the horizontal (x) axis.
	t_vec		viewport_v;			//A 3D vector that spans the height of the viewport along the vertical (y) axis.
	t_vec		pixel_delta_u;		//A 3D vector that represents the change in the x-coordinate for each pixel across the viewport.
	t_vec		pixel_delta_v;		//A 3D vector that represents the change in the y-coordinate for each pixel across the viewport.
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
	t_bvh_node	*bvh_root;
	t_object	*objects;
	t_light		*lights;
	int			total_objects;
	int			total_lights;
	t_aabb		*bounds;
	t_vec		corner[8]; // Array of 8 corner points of the Root AABB
	t_color		ambient_light;
	double		ambient_ratio;
}			t_scene;

typedef struct s_ray
{
	t_vec	origin; // Ray origin -- marks where we cast it from
	t_vec	direction; // Ray direction -- marks where we cast it to - reference for trajectory calculations
	t_vec	normal_unit; // Normalized direction vector (unit vector)
}			t_ray;

#endif
