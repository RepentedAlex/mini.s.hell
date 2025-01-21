/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:17:34 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:26:49 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare two strings up to a specified number of characters.
 *
 * This function compares the first `n` characters of the strings `s1` and `s2`.
 * The comparison is done using unsigned characters, so the result is always
 * the difference between the ASCII values of the characters being compared.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The maximum number of characters to compare.
 * @return An integer greater than, equal to, or less than 0,
 * depending on whether
 * `s1` is greater than, equal to, or less than `s2`.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	if (n == 0)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			return (result);
		}
		i++;
	}
	return (0);
}
