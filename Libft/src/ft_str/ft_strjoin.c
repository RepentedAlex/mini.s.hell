/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:58:12 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:27:56 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates two strings.
 *
 * This function concatenates the strings `s1` and `s2` into a newly allocated
 * string. The resulting string is terminated with a null character ('\0').
 *
 * @param s1 The first string to be concatenated.
 * @param s2 The second string to be concatenated.
 * @return A pointer to the newly allocated string,
 * or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat_str;
	int		cat_len;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	cat_len = len_s1 + len_s2;
	cat_str = ft_calloc((cat_len) + 1, sizeof(char));
	if (!cat_str)
		return (NULL);
	ft_strlcpy(cat_str, s1, len_s1 + 1);
	ft_strlcat(cat_str, s2, len_s1 + len_s2);
	return (cat_str);
}
