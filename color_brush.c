/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_brush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:24:41 by mman              #+#    #+#             */
/*   Updated: 2024/06/09 16:57:53 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_process_pixel(t_mlxdata *mlxdata, int x, int y, t_color rgb)
{
    int		color;
    int		pixel_index;

    color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
    pixel_index = (y * mlxdata->line_length)
        + (x * (mlxdata->bits_per_pixel / 8));
    mlxdata->addr[pixel_index] = color >> 16;
    mlxdata->addr[pixel_index + 1] = color >> 8;
    mlxdata->addr[pixel_index + 2] = color;
}

t_color color_from_object(t_object *object)
{
    t_color color;

    color.r = object->color.r;
    color.g = object->color.g;
    color.b = object->color.b;
    return (color);
}