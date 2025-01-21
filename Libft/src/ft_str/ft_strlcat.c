/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:47:18 by apetitco          #+#    #+#             */
/*   Updated: 2024/04/23 17:27:32 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates the string pointed to by `src` to the end of the string
 * pointed to by `dst`. It will append at most `size - strlen(dst) - 1`
 * characters from `src`, and then adds a null-terminating character.
 *
 * @param dst   The destination string.
 * @param src   The source string.
 * @param size  The total size of the destination buffer.
 * @return      The total length of the string that would have been created
 *              if enough space had been available (excluding the null
 *              terminator), or the total length of `dst` plus the length of
 *              `src` if the resulting string would have been longer than
 *              `size`.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	if (size == 0)
		return (ft_strlen((char *)src));
	src_len = ft_strlen((char *)src);
	dst_len = ft_strlen(dst);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && dst_len + i < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}
