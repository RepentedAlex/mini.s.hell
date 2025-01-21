/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:29:49 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:26:01 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Trims leading and trailing characters from a string.
 *
 * This function takes a string `s1` and a set of characters `set`
 * and removes any leading or trailing characters
 * from `s1` that are present in `set`. The resulting trimmed string is returned.
 *
 * @param s1 The string to be trimmed.
 * @param set The set of characters to be removed from `s1`.
 * @return The trimmed string, or NULL if `s1` is NULL
 * or if memory allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_string;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	(void)end;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) && end > start)
		end--;
	trimmed_string = ft_calloc(end - start + 2, sizeof(char));
	if (!trimmed_string)
		return (NULL);
	ft_strlcpy(trimmed_string, &s1[start], end - start + 2);
	return (trimmed_string);
}
