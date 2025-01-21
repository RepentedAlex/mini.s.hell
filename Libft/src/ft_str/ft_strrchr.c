/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:19:08 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:26:10 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the last occurrence of a character in a string.
 *
 * @param s The string to search in.
 * @param c The character to search for.
 * @return A pointer to the last occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (s[i] != (unsigned char)c)
	{
		if (i == 0 && s[i] != c)
			return ((char *)0);
		i--;
	}
	return ((char *)&s[i]);
}
