/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:06:02 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:11 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strchr() function locates the first occurrence of the character 'c'
 * (converted to an unsigned char) in the string 's'. The search includes the
 * terminating null character.
 *
 * @param s The string to be searched.
 * @param c The character to be located.
 * @return A pointer to the located character,
 * or NULL if the character does not occur in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == 0)
			return ((char *)0);
		i++;
	}
	return ((char *)&s[i]);
}
