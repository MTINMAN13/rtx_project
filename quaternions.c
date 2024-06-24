/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:21:11 by mman              #+#    #+#             */
/*   Updated: 2024/06/24 19:17:22 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Creates a quaternion based on the given angle and axis.
 *
 * @param angle The angle in radians.
 * @param axis The axis of rotation.
 * @return The created quaternion.
 */
t_quaternion create_quaternion(float angle, t_vec axis)
{
	vector_oneilizer(&axis);
	float sin_half_angle = sin(angle / 2.0f);
	t_quaternion q = { cos(angle / 2.0f), axis.x * sin_half_angle, axis.y * sin_half_angle, axis.z * sin_half_angle };
	return q;
}

/**
 * Multiplies two quaternions and returns the result.
 *
 * @param q1 The first quaternion.
 * @param q2 The second quaternion.
 * @return The result of multiplying the two quaternions.
 */
t_quaternion multiply_quaternions(t_quaternion q1, t_quaternion q2)
{
	t_quaternion result;
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return result;
}

/**
 * Calculates the inverse of a quaternion.
 *
 * This function takes a quaternion as input and returns its inverse.
 * The inverse of a quaternion is obtained by negating the x, y, and z components.
 * The w component remains the same.
 *
 * @param q The quaternion to calculate the inverse of.
 * @return The inverse of the input quaternion.
 */
t_quaternion inverse_quaternion(t_quaternion q)
{
	t_quaternion result = { q.w, -q.x, -q.y, -q.z };
	return result;
}

/**
 * Rotates a 3D point using a quaternion.
 *
 * @param p The point to be rotated.
 * @param q The quaternion representing the rotation.
 * @return The rotated point.
 */
t_vec rotate_point(t_vec p, t_quaternion q)
{
	t_quaternion p_quat = { 0, p.x, p.y, p.z };
	t_quaternion q_inv = inverse_quaternion(q);
	t_quaternion q_p = multiply_quaternions(q, p_quat);
	t_quaternion q_p_q_inv = multiply_quaternions(q_p, q_inv);
	
	t_vec result = { q_p_q_inv.x, q_p_q_inv.y, q_p_q_inv.z };
	return result;
}

t_vec translate_point(t_vec p, t_vec translation)
{
	t_vec result = { p.x + translation.x, p.y + translation.y, p.z + translation.z };
	return result;
}

t_quaternion combine_rotations(float theta_x, float theta_y)
{
	t_quaternion q_x = create_quaternion(theta_x, (t_vec){1, 0, 0});
	t_quaternion q_y = create_quaternion(theta_y, (t_vec){0, 1, 0});
	t_quaternion q_combined = multiply_quaternions(q_x, q_y);
	return q_combined;
} 

void	rotate_points(t_vec center, t_vec* p1, t_vec* p2, t_vec* p3, t_vec* p4, t_vec* p5, float theta_x, float theta_y)
{
	// Přelož body, aby středový bod byl v počátku
	t_vec translated_p1 = translate_point(*p1, (t_vec){-center.x, -center.y, -center.z});
	t_vec translated_p2 = translate_point(*p2, (t_vec){-center.x, -center.y, -center.z});
	t_vec translated_p3 = translate_point(*p3, (t_vec){-center.x, -center.y, -center.z});
	t_vec translated_p4 = translate_point(*p4, (t_vec){-center.x, -center.y, -center.z});
	t_vec translated_p5 = translate_point(*p5, (t_vec){-center.x, -center.y, -center.z});

	// Vytvoř kombinovaný kvaternion pro rotace kolem os x a y
	t_quaternion q_combined = combine_rotations(theta_x, theta_y);

	// Rotuj přeložené body
	*p1 = rotate_point(translated_p1, q_combined);
	*p2 = rotate_point(translated_p2, q_combined);
	*p3 = rotate_point(translated_p3, q_combined);
	*p4 = rotate_point(translated_p4, q_combined);
	*p5 = rotate_point(translated_p5, q_combined);

	// Přelož body zpět
	*p1 = translate_point(*p1, center);
	*p2 = translate_point(*p2, center);
	*p3 = translate_point(*p3, center);
	*p4 = translate_point(*p4, center);
	*p5 = translate_point(*p5, center);

	printf("Rotated points:\n");
	printf("Point 1: (%f, %f, %f)\n", p1->x, p1->y, p1->z);
	printf("Point 2: (%f, %f, %f)\n", p2->x, p2->y, p2->z);
	printf("Point 3: (%f, %f, %f)\n", p3->x, p3->y, p3->z);
	printf("Point 4: (%f, %f, %f)\n", p4->x, p4->y, p4->z);
	printf("Point 5 (eye): (%f, %f, %f)\n", p5->x, p5->y, p5->z);
}