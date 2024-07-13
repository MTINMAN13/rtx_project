/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:42:01 by mman              #+#    #+#             */
/*   Updated: 2024/07/01 02:16:32 by mman             ###   ########.fr       */
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
# define SAMPLES_PER_PIXEL 1
# define RENDER_DISTANCE 10000
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
void	get_eye_coords(t_scene **scene);
void	bvh_tree(t_scene *scene);
void	bvh_bounds(t_scene *scene);
void	calculate_aabb(t_object	*object, t_aabb	*aabb);
t_color bvh_intersect(t_scene *scene, t_ray *ray);
int	    aabb_intersect(t_aabb aabb, t_ray *ray);
void	ft_rotate_viewport(t_scene **scene);


//
void	raycaster(t_scene *scene);
void    ray(t_scene *scene, int x, int y);

//Parsing:
int		ft_parse(int fd, t_scene **scene);
int	    parse_camera_data(char *line, t_scene **scene);
void	parse_sphere_data(char *line, t_scene **scene);
void	calculate_plane_bounds(t_vec plane_normal, t_vec point, t_object *plane);
void	parse_plane_data(char *line, t_scene **scene);
void	parse_cylinder_data(char *line, t_scene **scene);

//Vector Allocation:
void	ft_assign_values_to_t_vec(t_vec *vec, char *str);
void	ft_assign_values_to_t_color(t_color *color, char *str);
void	parse_ambient_light(char *line, t_scene **scene);
void	ft_vectorize(t_vec *vec, double x, double y, double z);

//Vector Matrix Multiplication;
void	multiply_matrix_vector(t_vec *result, const double matrix[3][3], t_vec *vector);
void	transform_vertex(t_vec center, t_vec *vertex, const double rotation_matrix[3][3]);
void	vector_oneilizer(t_vec *v);

//quaternions:
t_quaternion    create_quaternion(float angle, t_vec axis);
t_quaternion    multiply_quaternions(t_quaternion q1, t_quaternion q2);
t_quaternion    inverse_quaternion(t_quaternion q);
t_vec           rotate_point(t_vec p, t_quaternion q);
t_vec           translate_point(t_vec p, t_vec translation);
t_quaternion    combine_rotations(float theta_x, float theta_y);
void            rotate_points(t_vec center, t_vec* p1, t_vec* p2, t_vec* p3, t_vec* p4, t_vec* p5, float theta_x, float theta_y);



//Calculations:
double	focal_length(double fov);
double	ft_fmax(double x, double y);
double	ft_fmin(double x, double y);
double	degrees_to_radians(double degrees);
t_vec	vector_subtract(t_vec v1, t_vec v2);
t_vec	vector_divide(t_vec v, double scalar);
t_vec	change_per_unit_distance(t_vec p1, t_vec p2);

//Coloring:
void	ft_process_pixel(t_mlxdata *mlxdata, int x, int y, t_color rgb);
t_color color_from_object(t_object *object);


void swap_objects(t_object *a, t_object *b);
double get_coordinate(t_vec vec, int axis);
int partition(t_object *object_list, int pivot, int axis);
void sort_object_list(t_object **object_list, int axis);
void split_object_list(t_object *object_list, t_object **left_list, t_object **right_list);
int ft_longest_axis(t_aabb bbox);
void    build_bvh_tree(t_scene *scene, t_bvh_node **bvh_root, t_object *object_list, t_aabb bounds);
void bvh_tree(t_scene *scene);
t_aabb encompassing_bbox(t_aabb bbox1, t_aabb bbox2);
t_aabb calculate_list_bbox(t_object *object_list);
void free_bvh_tree(t_scene *scene);
int count_aabbs_in_bvh(t_bvh_node *node);
int count_objects(t_object *object_list);


int sphere_intersection(t_ray *ray, t_object *object, t_color *color);


// ray_caster.c
int ray_intersects_aabb(t_ray *ray, t_aabb *aabb);
int object_intersects(t_ray *ray, t_object *object, t_color *color);
int plane_intersection(t_ray *ray, t_object *object, t_color *color);
int square_intersection(t_ray *ray, t_object *object, t_color *color);
int cylinder_intersection(t_ray *ray, t_object *object, t_color *color);


int is_color_default(t_color color);
t_color create_color(float r, float g, float b);
t_color traverse_bvh(t_bvh_node *node, t_ray *ray);

// Functions already in the header:
t_vec vector_subtract(t_vec v1, t_vec v2);
t_vec vector_add(t_vec v1, t_vec v2);
t_vec vector_divide(t_vec v, double scalar);
double vec_dot(t_vec v1, t_vec v2);
t_vec vec_cross(t_vec v1, t_vec v2);
t_color color_from_object(t_object *object);


#endif
