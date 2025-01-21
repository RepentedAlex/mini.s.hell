/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:11:52 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:30:54 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of a specific character in a memory block.
 *
 * @param s     Pointer to the memory block to be searched.
 * @param c     Character to be located.
 * @param n     Number of bytes to be searched.
 *
 * @return      Pointer to the first occurrence of the character if found,
 * or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		if (*(temp + i) == (unsigned char)c)
			return (temp + i);
		i++;
	}
	return (NULL);
}
