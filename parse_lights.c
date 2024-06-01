/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:51:20 by mman              #+#    #+#             */
/*   Updated: 2024/05/29 18:39:24 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//parses the ambient light data
//example format;
//
//A 0.2 255,255,255
void	parse_ambient_light(char *line, t_scene **scene)
{
	char	**split;

	if (ft_strncmp(line, "A", 1) == 0)
	{
		split = ft_split(line, ' ');
		(*scene)->ambient_ratio = ft_atoidouble(&line[2]);
		ft_assign_values_to_t_color(&(*scene)->ambient_light, split[2]);
		free(split);
		ft_pntf("------------ Ambient Light Parsed");
	}
	else
		split = NULL;
}