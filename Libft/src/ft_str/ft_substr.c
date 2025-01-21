/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:15:33 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:25:49 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a substring from a given string.
 *
 * @param s The string from which to extract the substring.
 * @param start The starting index of the substring in the original string.
 * @param len The maximum length of the substring.
 * @return The newly allocated substring,
 * or NULL if the allocation fails or if `s` is NULL.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_original;

	if (!s)
		return (NULL);
	substr = NULL;
	len_original = ft_strlen(s);
	if (start > len_original)
		return (ft_calloc(1, sizeof(char)));
	if (len >= ft_strlen((s + start)))
		substr = ft_calloc(len_original - start + 1, sizeof(char));
	else
		substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (s + start), len + 1);
	return (substr);
}
