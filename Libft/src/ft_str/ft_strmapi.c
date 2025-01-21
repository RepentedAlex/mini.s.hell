/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:37:24 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:27:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies a function to each character of a string and creates a new string
 * with the results.
 *
 * @param s The input string.
 * @param f The function to apply to each character.
 * @return The new string created by applying the function to each character,
 *         or NULL if the input string is NULL or if memory allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;
	size_t			len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
