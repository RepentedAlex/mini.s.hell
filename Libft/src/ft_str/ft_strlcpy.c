/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:28:23 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:27:22 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a string from source to destination, up to a given size.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The maximum number of characters to copy.
 * @return The length of the source string.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	i;

	length = 0;
	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[length] != '\0')
		length++;
	return (length);
}
