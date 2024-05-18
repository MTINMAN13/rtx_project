/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:53:54 by mman              #+#    #+#             */
/*   Updated: 2024/05/18 17:54:14 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	initialize_viewport(t_viewport *viewport, double aspect_ratio
	, double fov, int image_width, int image_height)
{
	viewport->focal_length = 1.0 / tan(fov / 2.0);
	viewport->viewport_height = 2.0 * viewport->focal_length;
	viewport->viewport_width = aspect_ratio * viewport->viewport_height;

	viewport->viewport_u = (t_vec){viewport->viewport_width, 0, 0};
	viewport->viewport_v = (t_vec){0, -viewport->viewport_height, 0};

	viewport->pixel_delta_u = (t_vec){viewport->viewport_u.x / image_width, 0, 0};
	viewport->pixel_delta_v = (t_vec){0, viewport->viewport_v.y / image_height, 0};

	viewport->upper_left = (t_vec){-viewport->viewport_width / 2, viewport->viewport_height / 2, -viewport->focal_length};
}
