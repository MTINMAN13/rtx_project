/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:56:52 by mman              #+#    #+#             */
/*   Updated: 2024/05/18 17:37:19 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//converts the FOV to radians and returns FOCAL LENGTH as a double
double	focal_length(int fov)
{
	double	fl;
	double	diagonal;

	fl = 0;
	diagonal = sqrt(HEIGHT * HEIGHT + WIDTH * WIDTH);
	fov *= M_PI / 180;
	fl = diagonal / (2 * tan(fov / 2));
	return (fl);
}

