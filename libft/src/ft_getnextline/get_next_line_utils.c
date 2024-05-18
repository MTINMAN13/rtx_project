/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:50:16 by mman              #+#    #+#             */
/*   Updated: 2024/05/18 20:54:01 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_line_parsed(char *current_storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!current_storage[i])
		return (NULL);
	while (current_storage[i] && current_storage[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (current_storage[i] && current_storage[i] != '\n')
	{
		line[i] = current_storage[i];
		i++;
	}
	if (current_storage[i] == '\n')
	{
		line[i] = current_storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
