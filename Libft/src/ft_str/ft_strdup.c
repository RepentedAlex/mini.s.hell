/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:21:10 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:04 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief   Duplicates a string.
 *
 * This function duplicates the string `s` by allocating memory for a new string
 * and copying the contents of `s` into it. The duplicated string is terminated
 * with a null character.
 *
 * @param   s   The string to be duplicated.
 * @return  A pointer to the duplicated string,
 * or NULL if memory allocation fails.
 */
char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		length;

	if (!s)
		return (NULL);
	length = (ft_strlen((char *)s) + 1);
	duplicate = (char *)ft_calloc(length, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s, length);
	duplicate[length - 1] = 0;
	return (duplicate);
}
