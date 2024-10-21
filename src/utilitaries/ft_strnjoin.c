/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:52 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/15 12:17:55 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_strnjoin(char *src, char *dst, size_t n)
{
	size_t	i;
	size_t	j;
	int		len_src;
	int		len_dst;
	char	*ret;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (len_src < (int)n)
		len_src = (int)n;
	ret = (char *)malloc(sizeof(char) * (len_src + len_dst + 1));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (dst[++j])
		ret[j] = dst[j];
	while (++i < n && src[i])
		ret[j + i] = src[i];
	ret[j + i] = '\0';
	free(dst);
	dst = ret;
	return (ret);
}
