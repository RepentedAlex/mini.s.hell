/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:08:24 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:26:22 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of the substring 'little'
 * in the string 'big',
 * but only searches within the first 'n' characters of 'big'.
 *
 * @param big The string to search within.
 * @param little The substring to search for.
 * @param n The maximum number of characters to search within 'big'.
 * @return A pointer to the first occurrence of 'little' within 'big',
 * or NULL if 'little' is not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	if (!ft_strlen((char *)little))
		return ((char *)big);
	while (n > 0 && *big)
	{
		if (*big == little[0] && \
		!ft_strncmp(big, little, ft_strlen((char *)little)) \
		&& ft_strlen((char *)little) <= n)
			return ((char *)big);
		big++;
		n--;
	}
	return (NULL);
}
