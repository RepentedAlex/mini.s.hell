/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnapp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:03:50 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/22 13:03:52 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Takes two string and append n characters in the s2 to the s1 in
/// a freeable string.
/// @param s1 The string which we will append s2 to.
/// @param s2 The string that will be appended to s1.
/// @param n The number of character to append.
/// @return A freeable string if successfull, NULL otherwise
char	*ft_strnapp(const char *s1, const char *s2, size_t n)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strncat(res, s2, n);
	return (res);
}
