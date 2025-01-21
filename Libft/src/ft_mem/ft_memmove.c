/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:29:18 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:30:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a block of memory from a source address to a destination address,
 * handling overlapping memory regions correctly.
 *
 * @param dest The pointer to the destination address
 * where the memory will be copied to.
 * @param src The pointer to the source address where
 * the memory will be copied from.
 * @param n The number of bytes to be copied.
 * @return A pointer to the destination address.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dup_src;
	char	*dup_dest;

	if (!src && !dest)
		return (dest);
	dup_src = (char *)src;
	dup_dest = (char *)dest;
	i = 0;
	if (dest > src)
	{
		while (n != 0)
		{
			dup_dest[n - 1] = dup_src[n - 1];
			n--;
		}
	}
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
