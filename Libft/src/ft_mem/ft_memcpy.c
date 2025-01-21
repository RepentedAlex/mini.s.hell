/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:16:59 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:30:24 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a block of memory from a source address to a destination address.
 *
 * @param dest The pointer to the destination address
 * where the memory will be copied to.
 * @param src The pointer to the source address where
 * the memory will be copied from.
 * @param n The number of bytes to be copied.
 * @return A pointer to the destination address.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dup_src;
	char	*dup_dest;

	if (!src && !dest)
		return (dest);
	dup_src = (char *)src;
	dup_dest = (char *)dest;
	i = 0;
	while (i < n)
	{
		dup_dest[i] = dup_src[i];
		i++;
	}
	return (dest);
}
