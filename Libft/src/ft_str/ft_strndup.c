/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:15:48 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/28 15:15:50 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*duplicate;
	int		length;

	if (!s)
		return (NULL);
	length = (ft_strlen((char *)s) + 1);
	if ((size_t)length > n)
		length = n;
	duplicate = (char *)ft_calloc(length, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s, length);
	duplicate[length - 1] = 0;
	return (duplicate);
}
