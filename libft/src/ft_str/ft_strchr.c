/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:36:19 by mman              #+#    #+#             */
/*   Updated: 2024/05/23 22:04:16 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//    The strchr() function returns a pointer to the first occurrence
//    of the character c in the string s.
//    WE return a pointer to the
//    matched character or NULL if the character is not found.  The
//    terminating null byte is considered part of the string, so that
//    if c is specified as '\0', these functions return a pointer to
//    the terminator.

#include <string.h>
#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
